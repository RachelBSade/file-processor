# String File Processor

This repository contains a set of C programs for **string manipulation, file processing, and text decoding**.  
It was developed as part of an academic assignment in advanced C programming.

## Features
- **Split Function**: Extracts all words from a string that start with a given letter and stores them in a dynamically allocated array.
- **File Creation & Analysis**:
  - Create a text file from user input.
  - Find the most common letter in the file (case-insensitive, returns uppercase).
- **Decode Function**: Decrypts a given string using a position-based ASCII shifting method.

## Topics Covered
- Dynamic memory allocation
- String manipulation
- File I/O in C
- Character frequency analysis
- Simple cryptography and decoding
- Clean memory management

## How to Compile & Run
```bash
gcc file-processor.c -o processor
./processor
