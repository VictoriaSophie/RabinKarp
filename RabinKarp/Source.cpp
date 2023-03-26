/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <cassert>
#include <iostream>
#include <list>
#include <string>

#include "RabinKarp.h"

using namespace std;

// checking if actual match and not hash collision
bool check(const string& pattern, const string& text, int i)
{
    int j;
    int patLen = pattern.size();
    
    for (j = 0; j < patLen; j++)
    {
        if (text[i + j] != pattern[j]) // if no match, return false
            return false;
    }

    if (j == patLen)
        return true;
}

void rabinKarp(const string& pattern, const string& text, int q) // source: adapted from Algorithms by Robert Sedgewick, Fourth Edition, page 777
{
    // initialising variables
    int skip = 256;
    int patLen = pattern.size();
    int textLen = text.size();
    int patHash = 0;
    int textHash = 0;  
    int i, j;
    int h = 1;

    for (i = 0; i < patLen - 1; i++)
        h = (h * skip) % q;

    // calculating hashs
    for (i = 0; i < patLen; i++)
    {
        patHash = (skip * patHash + pattern[i]) % q;
        textHash = (skip * textHash + text[i]) % q;
    }

    // going through the pattern, checks if hash values match
    for (i = 0; i <= textLen - patLen; i++)
    {
        if (patHash == textHash && check(pattern, text, i)) // if the hash numbers are the same of pattern and text + check bool returns true
        {
            cout << "Found '" << pattern << "' at position " << i << ":\n"; // print result
            show_context(text, i);
        }

        // changes textHash to next part of text
        if (i < textLen - patLen)
        {
            textHash = (skip * (textHash - text[i] * h) + text[i + patLen]) % q;

            if (textHash < 0) // if hash of text is negative
                textHash = (textHash + q);
        }
    }
}

int main(int argc, char* argv[])
{
    // setting text and pattern
    string text = "aaa aa aa aaab aaa";
    string pattern = "aaab";

    int q = 101; // any prime number can be used to change hash result

    // calling rabinKarp search method
    rabinKarp(pattern, text, q);

    return 0;
}