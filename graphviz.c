#include "graphviz.h"
/**
 * @brief 轉換成4Byte的資料形式，額外處理ASCII不顯示字元。
 *
 * @param input 輸入資料，大小為1個Byte的ASCII字元。
 * @param output 輸出資料，輸出為4個Byte，不顯示字元以Unicode顯示，非數字字母字元添加跳脫字元前綴。
 */
static void Byte2UintData( uint8_t input, char *output ) {
    if ( input >= 0x00 && input < 0x20 || input == 0x7f )  // ASCII 0x00 ~ 0x1F convert to Unicode type.
        *( uint32_t * )output = 0x008090e2 + ( input << 16 );
    else if (
        ( input >= 0x30 && input < 0x3A ) ||  // '0' ~ '9'.
        ( input >= 0x41 && input < 0x5B ) ||  // 'A' ~ 'Z'.
        ( input >= 0x61 && input < 0x7B ) )   // 'a' ~ 'z' normal output.
        *( uint32_t * )output = 0x00000000 | input;
    else if ( input == 0x25 )  // '%' to "\%%".
        *( uint32_t * )output = 0x0025255C;
    else if(input < 0x7F)  // add Escape character '\'.
        *( uint32_t * )output = 0x0000005C | ( input << 8 );
    else // other than ASCII code table.
        *( uint32_t * )output = 0x0;
}


/**
 * @brief 根據類型繪畫節點
 * 
 * @param fw 輸出檔案指標
 * @param node 節點
 * @param traveralBitData 走訪資料
 * @param traveralBitDataLength 資料長度
 */
static void WriteNodeDot( FILE *fw, _HuffmanTree *node, uint32_t traveralBitData, uint8_t traveralBitDataLength ) {
    if ( node == NULL ) return;

    char buf[ 200 ];
    char ListType[] = "color=orange,fontcolor=white";
    char LeafType[] = "color=yellow,fontcolor=black";
    char RootType[] = "color=blue,fontcolor=white";

    bool isListNode = ( node->last != NULL || node->next != NULL ) ? true : false;
    bool isLeafNode = ( node->left == NULL && node->right == NULL ) ? true : false;

    //----------------------------Create node------------------------------------
    // Node attributes.
    char *typePtr;
    if ( isListNode ) { typePtr = ListType; }
    else if ( isLeafNode ) { typePtr = LeafType; }
    else { typePtr = RootType; }

    // Weigth string.
    char label_Weight[ 23 ];
    snprintf( label_Weight, sizeof( label_Weight ), "Weight = %d\\n", node->weight );

    // Data string.
    char label_Data[ 21 ];
    char label_UTF8[ 4 ];
    Byte2UintData( node->data, label_UTF8 );
    snprintf( label_Data, sizeof( label_Data ), "Data = %s (0x%02X)\\n", label_UTF8, node->data );

    // Huffman code string.
    int  i;
    char label_HuffmanCode[ 48 ] = "Huffman Code = ";
    for ( i = 0; i < traveralBitDataLength; i++ ) label_HuffmanCode[ i + 15 ] = ( traveralBitData & ( 0x1 << i ) ) ? '1' : '0';
    label_HuffmanCode[ i + 15 ] = '\0';

    // Output string.
    fprintf( fw, "_0x%X[label=\"<f0>|<f1>_0x%X\\n%s%s%s|<f2>\", %s];\n", node, node, label_Weight, ( isLeafNode ) ? label_Data : "", ( !isListNode && isLeafNode ) ? label_HuffmanCode : "", typePtr );
}

enum lineHeadPortType { left = 0, right, parent, last, next };

/**
 * @brief 根據類型繪畫連接線
 * 
 * @param fw 輸出檔案指標
 * @param node1 連接節點1
 * @param node2 連接節點2
 * @param headPortType 節點1線出口位置
 */
static void WriteNodeLine( FILE *fw, _HuffmanTree *node1, _HuffmanTree *node2, enum lineHeadPortType headPortType ) {
    switch ( headPortType ) {
    case left:
        fprintf( fw, "_0x%X:f0:sw->_0x%X:f1:n[label=\"0\"];\n", node1, node2 );
        break;
    case right:
        fprintf( fw, "_0x%X:f2:se->_0x%X:f1:n[label=\"1\"];\n", node1, node2 );
        break;
    case parent:
        break;
    case last:
        if ( node2 != NULL && node2->next != node1 )  //
            fprintf( fw, "_0x%X:f1:n->_0x%X:f1:s[label=\"%s\",dir=%s];\n", node1, node2, "last", "forward" );
        break;
    case next:
        fprintf(
            fw,  //
            "_0x%X:f1:s->_0x%X:f1:n[label=\"%s\",dir=%s];\n",
            node1,
            node2,
            ( node2->last == node1 ) ? "next | previous" : "next",
            ( node2->last == node1 ) ? "both" : "forward" );
        break;
    }
}

/**
 * @brief 遞迴二元樹並繪畫
 * 
 * @param fw 輸出檔案指標
 * @param curr 現在節點
 * @param traveralBitData 走訪資料
 * @param traveralBitDataLength 走訪資料長度
 */
static void TreeTraversal( FILE *fw, _HuffmanTree *curr, uint32_t traveralBitData, uint8_t traveralBitDataLength ) {
    if ( curr != NULL )
        WriteNodeDot( fw, curr, traveralBitData, traveralBitDataLength );
    else
        return;

    if ( curr->left != NULL ) {
        WriteNodeLine( fw, curr, curr->left, left );
        TreeTraversal( fw, curr->left, traveralBitData << 1, traveralBitDataLength + 1 );
    }
    if ( curr->right != NULL ) {
        WriteNodeLine( fw, curr, curr->right, right );
        TreeTraversal( fw, curr->right, ( traveralBitData << 1 ) | 0x1, traveralBitDataLength + 1 );
    }
    if ( curr->last != NULL ) { WriteNodeLine( fw, curr, curr->last, last ); }
    if ( curr->next != NULL ) {
        WriteNodeLine( fw, curr, curr->next, next );
        TreeTraversal( fw, curr->next, 0, 0 );
    }
}

/**
 * @brief 建立Dot二元樹可視化檔案
 * 
 * @param tree 二元樹Root節點
 * @param filename 檔案名稱
 */
void CreateDotFile( _HuffmanTree *tree, char *filename ) {

    FILE *fw;
    if ( NULL == ( fw = fopen( filename, "w" ) ) ) {
        printf( "open file error" );
        return;
    }
    fprintf( fw, "digraph{\nnode[shape=Mrecord,style=filled,color=black,fontcolor=white];\n" );
    TreeTraversal( fw, tree, 0, 0 );
    fprintf( fw, "}" );
    fclose( fw );
}
