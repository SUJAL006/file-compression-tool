#include <iostream>
#include <string>
#include "HuffmanCompression.h"

void displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "   File Compression Tool (Huffman)\n";
    std::cout << "========================================\n";
    std::cout << "1. Compress File\n";
    std::cout << "2. Decompress File\n";
    std::cout << "3. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice: ";
}

int main() {
    HuffmanCompression compressor;
    int choice;
    std::string inputFile, outputFile;
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                std::cout << "\nEnter input file name: ";
                std::getline(std::cin, inputFile);
                std::cout << "Enter output file name (compressed): ";
                std::getline(std::cin, outputFile);
                
                if (compressor.compressFile(inputFile, outputFile)) {
                    compressor.displayCodes();
                }
                break;
                
            case 2:
                std::cout << "\nEnter compressed file name: ";
                std::getline(std::cin, inputFile);
                std::cout << "Enter output file name (decompressed): ";
                std::getline(std::cin, outputFile);
                
                compressor.decompressFile(inputFile, outputFile);
                break;
                
            case 3:
                std::cout << "\nExiting program. Goodbye!\n";
                return 0;
                
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}