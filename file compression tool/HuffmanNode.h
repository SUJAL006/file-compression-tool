#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

// Node structure for Huffman Tree
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode *left, *right;

    HuffmanNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparator for Min-Heap (priority queue)
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

#endif