#ifndef HUFFMAN_COMPRESSION_H
#define HUFFMAN_COMPRESSION_H

#include <string>
#include <unordered_map>
#include "HuffmanNode.h"

class HuffmanCompression {
private:
    HuffmanNode* root;
    std::unordered_map<char, std::string> huffmanCodes;
    std::unordered_map<char, unsigned> frequencyMap;

    // Build frequency map from input text
    void buildFrequencyMap(const std::string& text);
    
    // Build Huffman Tree using Min-Heap
    HuffmanNode* buildHuffmanTree();
    
    // Generate Huffman codes by traversing the tree
    void generateCodes(HuffmanNode* root, std::string str);
    
    // Encode text using generated Huffman codes
    std::string encode(const std::string& text);
    
    // Decode binary string using Huffman tree
    std::string decode(HuffmanNode* root, const std::string& encodedStr);
    
    // Free memory allocated for tree
    void destroyTree(HuffmanNode* node);

public:
    HuffmanCompression();
    ~HuffmanCompression();
    
    // Main compression function
    bool compressFile(const std::string& inputFile, const std::string& outputFile);
    
    // Main decompression function
    bool decompressFile(const std::string& inputFile, const std::string& outputFile);
    
    // Display Huffman codes
    void displayCodes();
    
    // Calculate compression ratio
    double getCompressionRatio(size_t originalSize, size_t compressedSize);
};

#endif