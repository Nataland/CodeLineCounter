#include <iostream>
#include <sstream>

/**
    CodeLineCounter.cpp
    Purpose: count the number of lines / comments / block comments / etc.

    @author Yumeng Natalie Zhang
    @date 2018-10-11
*/

using namespace std;

const char* t = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

inline static string& ltrim(string& s) {
    s.erase(0, s.find_first_of(t));
    return s;
}

inline static string& rtrim(string& s) {
    s.erase(s.find_last_of(t) + 1);
    return s;
}

inline static string& trim(string& s) {
    return ltrim(rtrim(s));
}

inline static string ltrim_copy(string s) {
    return ltrim(s);
}

inline static string rtrim_copy(string s) {
    return rtrim(s);
}

inline static string trim_copy(string s) {
    return trim(s);
}

// the defaults
string beginBlockComment = "/*";
string endBlockComment = "*/";
string beginSingleLineComment = "//";

string toLower(string s) {
    string lo = s;
    for (int i = 0; i < s.size(); ++i) {
        lo[i] = tolower(s[i]);
    }
    return lo;
}

int main(int argc , char *argv[]) {
    if (argc == 1) {
        // read file from standard input, default language has // and /* */

        int numLines, numCommentLines, numSingleLineComments;
        int numCommentLinesWithinBlockComments, numBlockComments, numTODOs;

        string fileSource;
        while (getline(cin, fileSource)) {
            numLines++;

            auto whereSingleComment = fileSource.find(beginSingleLineComment);
            auto whereBlockComment = fileSource.find(beginBlockComment);

            if (whereSingleComment != string::npos) {
                numCommentLines++;

                string sub = fileSource.substr(whereSingleComment + beginSingleLineComment.size());
                string word;
                stringstream ss{sub};

                while (ss >> word) {
                    if ("todo" == (trim_copy(toLower(word)))) {
                        numTODOs++;
                    }
                }

            }
        }
    } else {
        // read files in argv
    }
}