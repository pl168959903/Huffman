#include "Huffman_Compression.h"
#include "graphviz.h"
#include <stdlib.h>
#include <stdbool.h>



static _HuffmanTree *CreateNode( int weight, uint8_t data ) {
    _HuffmanTree *node = malloc( sizeof( _HuffmanTree ) );
    node->weight       = weight;
    node->data         = data;

    node->left = node->right = node->parent = node->next = node->last = NULL;

    return node;
}

static _HuffmanTree *CreateList( uint8_t data[], int dataSize ) {
    _HuffmanTree *head = NULL;
    for ( int i = 0; i < dataSize; i++ ) {
        _HuffmanTree *curr = head;
        if ( head == NULL )
            head = CreateNode( 1, data[ i ] );
        else {
            while ( true ) {
                // Finded same node Data
                if ( curr->data == data[ i ] ) {
                    curr->weight += 1;
                    break;
                }
                else {
                    // Create new node to end of list.
                    if ( curr->next == NULL ) {
                        curr->next       = CreateNode( 1, data[ i ] );
                        curr->next->last = curr;
                        break;
                    }
                    // next node.
                    else
                        curr = curr->next;
                }
            }
        }
    }
    return head;
}

_HuffmanTree *FindListNode( _HuffmanTree *tree, int n ) {
    _HuffmanTree *curr = tree;
    while ( n-- ) {
        if ( curr == NULL ) { return NULL; }
        else
            curr = curr->next;
    }
    return curr;
}

_HuffmanTree *NodeSwap( _HuffmanTree *head, _HuffmanTree *node ) {

    _HuffmanTree *n___ = node->last;
    _HuffmanTree *_n__ = node;        // switch 1
    _HuffmanTree *__n_ = node->next;  // switch 2
    _HuffmanTree *___n = node->next->next;

    if ( __n_ == NULL ) { return head; }

    if ( n___ != NULL )
        n___->next = __n_;
    else
        head = __n_;
    __n_->last = n___;
    __n_->next = _n__;
    _n__->last = __n_;
    _n__->next = ___n;
    if ( ___n != NULL ) ___n->last = _n__;

    return head;
}

int GetListLength( _HuffmanTree *tree ) {
    int           treeLength = 0;
    _HuffmanTree *curr       = tree;
    while ( curr != NULL ) {
        treeLength++;
        curr = curr->next;
    }
    return treeLength;
}

_HuffmanTree *BubbleSort( _HuffmanTree *tree, int listLength, bool reverse ) {
    for ( int i = 0; i < listLength - 1; i++ ) {
        _HuffmanTree *node = tree;
        for ( int j = 0; j < listLength - i - 1; j++ ) {
            if ( ( reverse == true ) ? ( node->weight > node->next->weight ) : ( node->weight < node->next->weight ) )
                tree = NodeSwap( tree, node );
            else
                node = node->next;
        }
    }
    return tree;
}

_HuffmanTree *Min2CreateRootNode( _HuffmanTree *tree ) {
    _HuffmanTree *left     = tree;
    _HuffmanTree *right    = tree->next;
    _HuffmanTree *listHead = right->next;
    _HuffmanTree *newNode  = CreateNode( left->weight + right->weight, 0 );

    newNode->left  = tree;
    newNode->right = tree->next;
    newNode->next  = right->next;
    newNode->last  = left->last;

    left->next = left->last = NULL;
    right->next = right->last = NULL;

    left->parent  = newNode;
    right->parent = newNode;

    if ( listHead != NULL ) { listHead->last = newNode; }

    tree = newNode;
    return tree;
}

_HuffmanTree *CreateTree( _HuffmanTree *tree ) {

    for ( int len = GetListLength( tree ); len > 1; len-- ) {
        tree = BubbleSort( tree, len, true );
        CreateDotFile( tree, "dot.dot" );
        tree = Min2CreateRootNode( tree );
        CreateDotFile( tree, "dot.dot" );
    }
    return tree;
}

void InsertHashTable( _HuffmanTree *node, _HuffmanTree **hash, int hashLength ) {
    int index = ( node->data % hashLength );
    while ( hash[ index ] != NULL ) index = ( index == hashLength - 1 ) ? 0 : index + 1;
    hash[ index ] = node;
}

_HuffmanTree **CreateHashTable( _HuffmanTree *list ) {
    int len = GetListLength( list );
    list    = BubbleSort( list, len, false );

    char aa[ 10 ] = { 0 };

    _HuffmanTree **HuffmanHash = malloc( sizeof( _HuffmanTree * ) * len );
    for ( int i = 0; i < len; i++ ) HuffmanHash[ i ] = NULL;
    _HuffmanTree *curr = list;
    while ( curr != NULL ) {
        InsertHashTable( curr, HuffmanHash, len );
        curr = curr->next;
    }

    return HuffmanHash;
}

_VarLengthCode FindLeafNode( _HuffmanTree *tree, uint8_t data, uint64_t zipData, int zipBit ) {
    _HuffmanTree         *curr = tree;
    static _VarLengthCode hfzip;
    if ( curr->data == data ) {
        hfzip.dataBit   = zipData;
        hfzip.bitLength = zipBit;
    }
    else {
        if ( tree->right != NULL ) FindLeafNode( tree->right, data, zipData << 1 | 0x1, zipBit + 1 );
        if ( tree->left != NULL ) FindLeafNode( tree->left, data, zipData << 1, zipBit + 1 );
    }
    return hfzip;
}

int hf_getZip( uint8_t data[], int dataSize, _HuffmanTree *tree, uint8_t output[] ) {
    uint8_t  dataBitStack   = 0x0;
    uint8_t  dataBitStack_c = 0;
    uint32_t output_c       = 0;
    uint32_t bit_c          = 0;
    for ( int i = 0; i < dataSize; i++ ) {
        _VarLengthCode fd = FindLeafNode( tree, data[ i ], 0, 0 );
        while ( fd.bitLength-- ) {
            output[ output_c ] |= ( ( ( fd.dataBit >> fd.bitLength ) & 0x1 ) << dataBitStack_c );

            if ( ++dataBitStack_c >= 8 ) {
                dataBitStack_c = 0;
                output_c += 1;
            }
            bit_c += 1;
        }
    }
    return bit_c;
}

void hf_reZip( uint8_t data[], int dataSize, _HuffmanTree *tree ) {
    uint8_t       dataBitStack   = 0;
    int           dataBitStack_c = 0;
    uint32_t      input_c        = 0;
    _HuffmanTree *curr           = tree;

    for ( int i = 0; i < dataSize; i++ ) {
        if ( dataBitStack_c <= 0 ) {
            dataBitStack_c = 8;
            dataBitStack   = data[ input_c ];
            input_c += 1;
        }

        uint8_t t = dataBitStack & 0x1;
        if ( t == 0x1 ) { curr = curr->right; }
        else { curr = curr->left; }
        dataBitStack >>= 1;
        dataBitStack_c -= 1;

        if ( curr->left == NULL && curr->right == NULL ) {
            printf( "%c", curr->data );
            curr = tree;
        }
    }
}

int findTreeDepth( _HuffmanTree *tree, int dep ) {
    static int retval = 0;
    if ( tree->left == NULL || tree->right == NULL ) {
        if ( dep > retval ) retval = dep;
    }
    else {
        findTreeDepth( tree->right, dep + 1 );
        findTreeDepth( tree->left, dep + 1 );
    }
    return retval;
}

int main( int argc, char *argv[] ) {

    // char test[] =
    //     "The full text of Shakespeare's plays and sonnets side-by-side with translations into modern English. No fear Shakespeare is available online and in book form at barnesandnoble.com.\n";
    char test[] = "Hello worl\"{}|?.<\%>@#$/^&*\n\r\\d.\n";

    _HuffmanTree *hf = CreateList( test, sizeof( test ) );
    CreateDotFile( hf, "dot.dot" );
    // _HuffmanTree **hashTable = CreateHashTable(hf);
    hf = CreateTree( hf );
    CreateDotFile( hf, "dot.dot" );

    int a = findTreeDepth( hf, 0 );

    uint8_t zip[ 1000 ] = { 0 };

    int c = hf_getZip( test, sizeof( test ), hf, zip );
    hf_reZip( zip, c, hf );
    system( "pause" );
    return 0;
}
