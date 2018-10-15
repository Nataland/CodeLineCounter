# CodeLineCounter

### What does this do
1) When a file is checked in, scan the file to count the total number of lines.
2) Scan the file to identify comments and count the total lines of comments in the file.
3) After identifying the lines of comments, scan to segregate the total number of single line
comments and the total number of multi-line comments.
4) Any line of code that has a trailing comment should be counted both as lines of code
and also a comment line.
5) Finally, from all the comments in the file, identify and count the total number of TODOs.
6) Please note, that the file that is being checked in could be any valid program file. Files
checked in without an extension can be ignored. You can also ignore file names that
start with a ‘.’.

### Usage
```
g++ std=c++14 CodeLineCounter.cpp
./a.out file1.cpp file2.cpp file3.cpp
```
Alternatively, this program takes input from std::cin and the default language is c/c++/java. However, inputting file names is recommended since you can pass in many files in one call.
