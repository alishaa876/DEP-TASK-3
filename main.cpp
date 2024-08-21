#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to compress a file using Run-Length Encoding (RLE)
void compressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    char currentChar;
    char previousChar = '\0';
    int count = 0;

    while (inFile.get(currentChar)) {
        if (currentChar == previousChar) {
            count++;
        }
        else {
            if (count > 0) {
                outFile.put(previousChar);
                outFile.put(count);
            }
            previousChar = currentChar;
            count = 1;
        }
    }

    if (count > 0) {
        outFile.put(previousChar);
        outFile.put(count);
    }

    inFile.close();
    outFile.close();
    cout << "File compressed successfully!" << endl;
}

// Function to decompress a file compressed with Run-Length Encoding (RLE)
void decompressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    char currentChar;
    char count;

    while (inFile.get(currentChar)) {
        if (inFile.get(count)) {
            for (int i = 0; i < static_cast<unsigned char>(count); i++) {
                outFile.put(currentChar);
            }
        }
    }

    inFile.close();
    outFile.close();
    cout << "File decompressed successfully!" << endl;
}

int main() {
    string inputFile, outputFile;
    int choice;

    cout << "Run-Length Encoding (RLE) Compression/Decompression Tool" << endl;
    cout << "1. Compress a file" << endl;
    cout << "2. Decompress a file" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the name of the file to compress: ";
        cin >> inputFile;
        cout << "Enter the name of the output compressed file: ";
        cin >> outputFile;
        compressFile(inputFile, outputFile);
    }
    else if (choice == 2) {
        cout << "Enter the name of the file to decompress: ";
        cin >> inputFile;
        cout << "Enter the name of the output decompressed file: ";
        cin >> outputFile;
        decompressFile(inputFile, outputFile);
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}