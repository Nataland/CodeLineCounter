#include <iostream>
#include <sstream>
#include <fstream>

/**
    CodeLineCounter.cpp
    Purpose: count the number of lines / comments / block comments / etc, with ability to process multiple files.

    @author Yumeng Zhang
    @date 2018-10-11
    @example    g++ std=c++14 CodeLineCounter.cpp
                ./a.out file1.cpp file2.cpp file3.cpp
*/

using namespace std;

const char *t = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

inline static string &ltrim(string &s) {
    s.erase(0, s.find_first_of(t));
    return s;
}

inline static string &rtrim(string &s) {
    s.erase(s.find_last_of(t) + 1);
    return s;
}

inline static string &trim(string &s) {
    return ltrim(rtrim(s));
}

inline static string trim_copy(string s) {
    return trim(s);
}

string toLower(string s) {
    string lo = s;
    for (int i = 0; i < s.size(); ++i) {
        lo[i] = tolower(s[i]);
    }
    return lo;
}

/*
 * readFile(stream, lang) reads stream one line at a time and supports three languages: c/c++ and python.
 * c/c++:   block comments are denoted with with beginBlockComment and endBlockComment
            and single comments are denoted with //
 * python:  no sign for block comments specifically, all comments are denoted with #,
 *          so consecutive lines of single comments are counted as a block comment
 */

void readFile(istream &stream, string lang = "default") {
    string beginBlockComment = "/*";
    string endBlockComment = "*/";
    string beginSingleLineComment = "//";

    if (lang == "py") {
        beginSingleLineComment = "#";   // no need for a sign for block comments
    }

    int numLines = 0;
    int numCommentLines = 0;
    int numCommentLinesWithinBlockComments = 0;
    int numBlockComments = 0;
    int numTODOs = 0;

    string fileSource;
    bool inBlockComment = false;
    bool isPyLineInBlock = false;       // for py files only
    int numPyLinesInThisBlock = 0;

    while (getline(stream, fileSource)) {
        numLines++;

        auto whereSingleComment = fileSource.find(beginSingleLineComment);
        auto whereBlockComment = fileSource.find(beginBlockComment);
        auto blockCommentEnds = fileSource.find(endBlockComment);

        if (whereSingleComment != string::npos && !inBlockComment) {
            numCommentLines++;
            string sub = fileSource.substr(whereSingleComment + beginSingleLineComment.size());
            string word;
            stringstream ss{sub};

            while (ss >> word) {
                if ("todo" == (trim_copy(toLower(word)))) {
                    numTODOs++;
                }
            }

            if (lang == "py") {
                if (!isPyLineInBlock) {
                    isPyLineInBlock = true;
                }
                numPyLinesInThisBlock++;
            }
        } else if (whereSingleComment == string::npos && lang == "py") {
            if (isPyLineInBlock && numPyLinesInThisBlock > 1) {
                numBlockComments++;
                numCommentLinesWithinBlockComments += numPyLinesInThisBlock;
                isPyLineInBlock = false;
            }
        }

        if (lang != "py") {
            // for default languages, count the number of blocks based on the block start and end symbol
            if (whereBlockComment != string::npos) {
                inBlockComment = true;
                numBlockComments++;
            }

            if (inBlockComment) {
                numCommentLinesWithinBlockComments++;
            }

            if (blockCommentEnds != string::npos) {
                inBlockComment = false;
            }
        }
    }

    cout << "Total # of lines: " << numLines << endl;
    cout << "Total # of comment lines: " << numCommentLines << endl;
    cout << "Total # of single line comments: " << numCommentLines - numCommentLinesWithinBlockComments << endl;
    cout << "Total # of comment lines within block comments: " << numCommentLinesWithinBlockComments << endl;
    cout << "Total # of block line comments: " << numBlockComments << endl;
    cout << "Total # of TODO’s: " << numTODOs << endl;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        readFile(cin);
    } else {
        for (int i = 1; i < argc; ++i) {
            char *name = argv[i];
            string fileName{name};
            cout << "File:L " << fileName << endl;
            ifstream fs{fileName};

            // find the extension of file (e.g. py, cpp, c, h, cc or java)
            size_t found = fileName.find_last_of(".");
            string ext = fileName.substr(found + 1);
            cout << "extension: " << ext << endl;


            if (ext == "cpp" || ext == "cc" || ext == "h" || ext == "c" || ext == "java") {
                ext = "default";
            } else if (ext == "py") {
                ext = "py";
            } else {
                cerr << "Unsupported format" << endl;
                return 1;
            }

            readFile(fs, ext);

            if (i != argc - 1) {
                cout << endl;   // produce an empty line between the results of two consecutive files
            }
        }
    }
}