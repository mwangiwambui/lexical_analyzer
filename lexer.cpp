#include <iterator>
#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

using namespace std;

int main() {

    string str; 
    cout << "Enter a piece of text to be processed in the lexical analyzer: ";
    getline(cin, str);

    // define list of patterns
    map<string, string> patterns{
        { "[0-9]+" ,   "int" },
        { "[_a-zA-Z]+" ,   "id" },
        { "\\*|\\+|\\-|\\=",  "operator" },
        { "[)}({]" , "braces" },
        {"[,.:]", "punctuation symbol;"}
    };

    // storage for results
    map< size_t, pair<string, string> > matches;

    for (auto way = patterns.begin(); way != patterns.end(); ++way)
    {
        regex r(way->first);
        auto words_begin = sregex_iterator(str.begin(), str.end(), r);
        auto words_end = sregex_iterator();

        for (auto it = words_begin; it != words_end; ++it)
            matches[it->position()] = make_pair(it->str(), way->second);
    }

    for (auto match = matches.begin(); match != matches.end(); ++match)
        cout << match->second.first << " " << match->second.second << endl;
}