# File Compression Tool

A lossless data compression utility implemented in C++ using the **Huffman Coding algorithm**. This project demonstrates the practical application of data structures and algorithms including binary trees, min-heaps, prefix codes, and greedy algorithms.

## Features

- **Lossless Compression**: Compresses text files without any data loss
- **Huffman Coding Algorithm**: Uses frequency-based encoding for optimal compression
- **Min-Heap Implementation**: Efficient priority queue using STL for building the Huffman tree
- **Binary Tree Structure**: Custom tree implementation for encoding/decoding
- **Prefix Codes**: Ensures unique decodability of compressed data
- **Greedy Algorithm**: Optimal character encoding based on frequency analysis

## Algorithm Overview

The Huffman Coding algorithm works as follows:

1. **Frequency Analysis**: Count the frequency of each character in the input file
2. **Min-Heap Construction**: Create a min-heap with nodes for each character
3. **Tree Building**: Repeatedly extract two minimum frequency nodes and create a parent node
4. **Code Generation**: Traverse the tree to assign binary codes (0 for left, 1 for right)
5. **Encoding**: Replace characters with their Huffman codes
6. **Compression**: Write the encoded binary data to file along with the frequency map

## Project Structure

```
huffman-compression/
│
├── HuffmanNode.h           # Node structure and comparator for min-heap
├── HuffmanCompression.h    # Class declaration
├── HuffmanCompression.cpp  # Implementation of compression/decompression
├── main.cpp                # Main program with user interface
├── Makefile                # Build configuration
├── README.md               # This file
└── sample.txt              # Sample input file for testing
```

## Data Structures Used

- **Binary Tree**: Custom implementation for the Huffman tree
- **Min-Heap**: STL `priority_queue` with custom comparator
- **Hash Map**: `unordered_map` for storing character frequencies and codes

## Requirements

- C++ compiler with C++11 support (g++, clang++)
- Make (optional, for using Makefile)

## Compilation

### Using Makefile:
```bash
make
```

### Manual compilation:
```bash
g++ -std=c++11 -Wall -Wextra -o huffman_compressor main.cpp HuffmanCompression.cpp
```

## Usage

### Running the program:
```bash
./huffman_compressor
```

### Menu Options:

1. **Compress File**
   - Enter the input file name (e.g., `sample.txt`)
   - Enter the output compressed file name (e.g., `sample.huf`)
   - The program displays compression statistics and Huffman codes

2. **Decompress File**
   - Enter the compressed file name (e.g., `sample.huf`)
   - Enter the output decompressed file name (e.g., `output.txt`)
   - The program restores the original file

3. **Exit**

### Example:

```bash
========================================
   File Compression Tool (Huffman)
========================================
1. Compress File
2. Decompress File
3. Exit
========================================
Enter your choice: 1

Enter input file name: sample.txt
Enter output file name (compressed): sample.huf
File compressed successfully!
Original size: 1024 bytes
Compressed size: 587 bytes
Compression ratio: 42.68%

Huffman Codes:
a : 010
b : 1110
c : 1111
...
```

## How It Works

### Compression Process:

1. Read input file and analyze character frequencies
2. Build Huffman tree using min-heap
3. Generate unique binary codes for each character
4. Encode the file using generated codes
5. Write frequency map and encoded data to compressed file

### Decompression Process:

1. Read frequency map from compressed file
2. Rebuild the Huffman tree
3. Decode the binary data using the tree
4. Write the original text to output file

## Time Complexity

- **Building Frequency Map**: O(n) where n is the number of characters
- **Building Huffman Tree**: O(k log k) where k is the number of unique characters
- **Encoding**: O(n)
- **Decoding**: O(n)

## Space Complexity

- O(k) for storing the Huffman tree and codes, where k is the number of unique characters

## Advantages

- Lossless compression (original data can be perfectly reconstructed)
- Optimal prefix-free codes
- No dictionary required (frequency map stored with compressed data)
- Efficient for files with non-uniform character distribution

## Limitations

- Not effective for files with uniform character distribution
- Small files may have larger compressed size due to metadata overhead
- Only works with text files in current implementation

## Future Enhancements

- Support for binary files
- Adaptive Huffman coding for streaming data
- Parallel processing for large files
- GUI interface
- Compression statistics visualization

## Technical Concepts Demonstrated

- **Greedy Algorithms**: Optimal solution through locally optimal choices
- **Binary Trees**: Hierarchical data structure for code representation
- **Min-Heaps**: Priority queue implementation
- **Prefix Codes**: Variable-length encoding without ambiguity
- **File I/O**: Binary file operations in C++
- **Memory Management**: Dynamic memory allocation and deallocation

## License

This project is open source and available for educational purposes.

## Author

Created as a demonstration of data structures and algorithms in C++.

## References

- Huffman, D. A. (1952). "A Method for the Construction of Minimum-Redundancy Codes"
- Introduction to Algorithms (CLRS)
- Data Structures and Algorithm Analysis in C++ (Mark Allen Weiss)