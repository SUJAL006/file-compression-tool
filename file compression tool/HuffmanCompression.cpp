#include "HuffmanCompression.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <bitset>

HuffmanCompression::HuffmanCompression() : root(nullptr) {}

HuffmanCompression::~HuffmanCompression() {
    destroyTree(root);
}

void HuffmanCompression::buildFrequencyMap(const std::string& text) {
    frequencyMap.clear();
    for (char ch : text) {
        frequencyMap[ch]++;
    }
}

HuffmanNode* HuffmanCompression::buildHuffmanTree() {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
    
    // Create leaf node for each character and add to min-heap
    for (auto pair : frequencyMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Build tree using greedy algorithm
    while (minHeap.size() != 1) {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();
        
        HuffmanNode *right = minHeap.top();
        minHeap.pop();
        
        // Create internal node with combined frequency
        HuffmanNode *top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        
        minHeap.push(top);
    }
    
    return minHeap.top();
}

void HuffmanCompression::generateCodes(HuffmanNode* root, std::string str) {
    if (!root) return;
    
    // Leaf node contains character
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = str;
    }
    
    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}

std::string HuffmanCompression::encode(const std::string& text) {
    std::string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCodes[ch];
    }
    return encodedStr;
}

std::string HuffmanCompression::decode(HuffmanNode* root, const std::string& encodedStr) {
    std::string decodedStr = "";
    HuffmanNode* current = root;
    
    for (char bit : encodedStr) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;
        
        // Reached leaf node
        if (!current->left && !current->right) {
            decodedStr += current->data;
            current = root;
        }
    }
    
    return decodedStr;
}

bool HuffmanCompression::compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return false;
    }
    
    // Read entire file
    std::string text((std::istreambuf_iterator<char>(inFile)),
                     std::istreambuf_iterator<char>());
    inFile.close();
    
    if (text.empty()) {
        std::cerr << "Error: Input file is empty!" << std::endl;
        return false;
    }
    
    // Build frequency map
    buildFrequencyMap(text);
    
    // Build Huffman Tree
    root = buildHuffmanTree();
    
    // Generate codes
    huffmanCodes.clear();
    generateCodes(root, "");
    
    // Encode text
    std::string encodedStr = encode(text);
    
    // Write to file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file!" << std::endl;
        return false;
    }
    
    // Write frequency map size
    size_t mapSize = frequencyMap.size();
    outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
    
    // Write frequency map
    for (auto pair : frequencyMap) {
        outFile.write(&pair.first, sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(unsigned));
    }
    
    // Write encoded string length
    size_t encodedLength = encodedStr.length();
    outFile.write(reinterpret_cast<const char*>(&encodedLength), sizeof(encodedLength));
    
    // Convert binary string to bytes and write
    for (size_t i = 0; i < encodedStr.length(); i += 8) {
        std::string byteStr = encodedStr.substr(i, 8);
        while (byteStr.length() < 8) byteStr += '0'; // Padding
        
        std::bitset<8> byte(byteStr);
        unsigned char byteVal = static_cast<unsigned char>(byte.to_ulong());
        outFile.write(reinterpret_cast<const char*>(&byteVal), sizeof(byteVal));
    }
    
    outFile.close();
    
    std::cout << "File compressed successfully!" << std::endl;
    std::cout << "Original size: " << text.length() << " bytes" << std::endl;
    std::cout << "Compressed size: " << (encodedStr.length() + 7) / 8 << " bytes" << std::endl;
    std::cout << "Compression ratio: " << getCompressionRatio(text.length(), (encodedStr.length() + 7) / 8) << "%" << std::endl;
    
    return true;
}

bool HuffmanCompression::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open compressed file!" << std::endl;
        return false;
    }
    
    // Read frequency map size
    size_t mapSize;
    inFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
    
    // Read frequency map
    frequencyMap.clear();
    for (size_t i = 0; i < mapSize; i++) {
        char ch;
        unsigned freq;
        inFile.read(&ch, sizeof(char));
        inFile.read(reinterpret_cast<char*>(&freq), sizeof(unsigned));
        frequencyMap[ch] = freq;
    }
    
    // Rebuild Huffman tree
    root = buildHuffmanTree();
    
    // Read encoded string length
    size_t encodedLength;
    inFile.read(reinterpret_cast<char*>(&encodedLength), sizeof(encodedLength));
    
    // Read bytes and convert to binary string
    std::string encodedStr = "";
    unsigned char byte;
    while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        std::bitset<8> bits(byte);
        encodedStr += bits.to_string();
    }
    
    // Trim to actual length
    encodedStr = encodedStr.substr(0, encodedLength);
    
    inFile.close();
    
    // Decode
    std::string decodedText = decode(root, encodedStr);
    
    // Write to output file
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file!" << std::endl;
        return false;
    }
    
    outFile << decodedText;
    outFile.close();
    
    std::cout << "File decompressed successfully!" << std::endl;
    
    return true;
}

void HuffmanCompression::displayCodes() {
    std::cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCodes) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

double HuffmanCompression::getCompressionRatio(size_t originalSize, size_t compressedSize) {
    return (1.0 - (double)compressedSize / originalSize) * 100.0;
}

void HuffmanCompression::destroyTree(HuffmanNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}