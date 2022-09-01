#ifndef __HUFFMAN_COMPRESSION_H
#define __HUFFMAN_COMPRESSION_H

#include <stdint.h>


typedef struct _HuffmanTree_t {

    int     weight;
    uint8_t data;

    // Node
    struct _HuffmanTree_t *left;
    struct _HuffmanTree_t *right;
    struct _HuffmanTree_t *parent;

    // Node list
    struct _HuffmanTree_t *next;
    struct _HuffmanTree_t *last;
} _HuffmanTree;

typedef struct {
    uint8_t  data;
    uint64_t dataBit;
    uint8_t  bitLength;
} _VarLengthCode;

#endif // __HUFFMAN_COMPRESSION_H
