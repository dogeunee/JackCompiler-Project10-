#include "data.h"
#include <fstream>
#include <cctype>
#include <map>
#include <iostream>
using namespace std;

class JackTokenizer
{
public:
    JackTokenizer();
    JackTokenizer(string filename);
    void initFilename(string s);
    ~JackTokenizer();
    bool hasMoreTokens();
    void advance();
    void advance2();
    void advanceString();
    void handelComment();
    void advanceComment1();
    void advanceComment2();
    TokenType tokenType();
    string keyWord();
    char symbol();
    string identifier();
    int intVal();
    string stringVal();
    bool keywordMapHas(string);
    bool symbolSetHas(char c);
    bool whiteSetHas(char c);
    bool opSetHas(char c);
    void printToken();

private:
    ifstream ifile;
    TokenType tType;
    char c;
    string token = "";
    std::map<string, KeyWord> keywordMap;
    std::set<char> symbolSet;
    std::set<char> whiteSet;
    std::set<char> opSet;
};