<h1 align="center">Charsort</h1>

## Program Description

Using the terminal will Add characters to doubly link list from existing file and sorts them with no duplicates, or whitespaces in alphabetical order in Standard output or output to new text file

Usage: codesolve [-o output_file_name] input_file_name

 -o outputs sorted doubly linked list with no duplicates to new file

## How to Run

Firstly clone the files from this git repository

from terminal navigate to the folder with the .c and makefile and type
```python
>make
```
Now that .c file is compiled and the executable has been created

you can run the executable with the following command:
codesolve [-o output_file_name] input_file_name

ps. "-o outfilename" is optional if you want to output the inputted file sorted to a new file. 
If you just want it to output to terminal just type the file that you want to sort "codesolve input_file_name"

## Recommended
Have the .txt file in the same directory/folder as the files

## What I Learned?
Learned how to create a doubly linked list from scratch, getting more familiar with C and pointers, as well as some basic sorting algorithms

## Time complexity
This Program uses bubble sort which is the slowest algorithm and runs at time complexity of O(n^2) 