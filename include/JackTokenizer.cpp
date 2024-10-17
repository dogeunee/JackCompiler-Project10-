#include "JackTokenizer.h"
JackTokenizer::JackTokenizer()
{
    keywordMap.insert({"class", CLASS});
    keywordMap.insert({"constructor", CONSTRUCTOR});
    keywordMap.insert({"function", FUNCTION});
    keywordMap.insert({"method", METHOD});
    keywordMap.insert({"field", FIELD});
    keywordMap.insert({"static", STATIC});
    keywordMap.insert({"var", VAR});
    keywordMap.insert({"int", INT});
    keywordMap.insert({"char", CHAR});
    keywordMap.insert({"boolean", BOOLEAN});
    keywordMap.insert({"void", VOID});
    keywordMap.insert({"true", TRUE});
    keywordMap.insert({"false", FALSE});
    keywordMap.insert({"null", _NULL});
    keywordMap.insert({"this", THIS});
    keywordMap.insert({"let", LET});
    keywordMap.insert({"do", DO});
    keywordMap.insert({"if", IF});
    keywordMap.insert({"else", ELSE});
    keywordMap.insert({"while", WHILE});
    keywordMap.insert({"return", RETURN});
    symbolSet.insert('{');
    symbolSet.insert('}');
    symbolSet.insert('(');
    symbolSet.insert(')');
    symbolSet.insert('[');
    symbolSet.insert(']');
    symbolSet.insert('.');
    symbolSet.insert(',');
    symbolSet.insert(';');
    symbolSet.insert('+');
    symbolSet.insert('-');
    symbolSet.insert('*');
    symbolSet.insert('/');
    symbolSet.insert('&');
    symbolSet.insert('|');
    symbolSet.insert('<');
    symbolSet.insert('>');
    symbolSet.insert('=');
    symbolSet.insert('~');
    whiteSet.insert(' ');
    whiteSet.insert('\n');
    whiteSet.insert('\t');
}
JackTokenizer::JackTokenizer(string filename)
{
    ifile.open(filename);
    ifile.get(c);
    keywordMap.insert({"class", CLASS});
    keywordMap.insert({"constructor", CONSTRUCTOR});
    keywordMap.insert({"function", FUNCTION});
    keywordMap.insert({"method", METHOD});
    keywordMap.insert({"field", FIELD});
    keywordMap.insert({"static", STATIC});
    keywordMap.insert({"var", VAR});
    keywordMap.insert({"int", INT});
    keywordMap.insert({"char", CHAR});
    keywordMap.insert({"boolean", BOOLEAN});
    keywordMap.insert({"void", VOID});
    keywordMap.insert({"true", TRUE});
    keywordMap.insert({"false", FALSE});
    keywordMap.insert({"null", _NULL});
    keywordMap.insert({"this", THIS});
    keywordMap.insert({"let", LET});
    keywordMap.insert({"do", DO});
    keywordMap.insert({"if", IF});
    keywordMap.insert({"else", ELSE});
    keywordMap.insert({"while", WHILE});
    keywordMap.insert({"return", RETURN});
    symbolSet.insert('{');
    symbolSet.insert('}');
    symbolSet.insert('(');
    symbolSet.insert(')');
    symbolSet.insert('[');
    symbolSet.insert(']');
    symbolSet.insert('.');
    symbolSet.insert(',');
    symbolSet.insert(';');
    symbolSet.insert('+');
    symbolSet.insert('-');
    symbolSet.insert('*');
    symbolSet.insert('/');
    symbolSet.insert('&');
    symbolSet.insert('|');
    symbolSet.insert('<');
    symbolSet.insert('>');
    symbolSet.insert('=');
    symbolSet.insert('~');
    whiteSet.insert(' ');
    whiteSet.insert('\n');
    whiteSet.insert('\t');
}
void JackTokenizer::initFilename(string s)
{
    ifile.open(s);
    ifile.get(c);
}
JackTokenizer::~JackTokenizer()
{
    ifile.close();
}
bool JackTokenizer::hasMoreTokens()
{
    return !ifile.eof();
}

void JackTokenizer::advance()
{
    token = "";

    if (c == '/')
    {
        handelComment();
    }
    else
    {
        if (symbolSetHas(c))
        {
            tType = SYMBOL;
            token = c;
            ifile.get(c);
            while (whiteSetHas(c) && hasMoreTokens())
                ifile.get(c);
        }
        else if (isdigit(c))
        {
            tType = INT_CONST;
            advance2();
        }
        else if (c == '"')
        {
            tType = STRING_CONST;
            ifile.get(c);
            advanceString();
        }
        else
        {
            advance2();
            if (keywordMapHas(token))
            {
                tType = KEYWORD;
            }
            else
            {
                tType = IDENTIFIER;
            }
        }
    }
    if (token.length() == 0)
    {
        advance();
    }
    else
    {
        cout << token << "\n";
    }
}

void JackTokenizer::advance2()
{
    while (true)
    {
        token.push_back(c);
        ifile.get(c);
        if (whiteSetHas(c) || symbolSetHas(c))
            break;
    };
    while (whiteSetHas(c))
        ifile.get(c); // skip through space, \n, \t
}
void JackTokenizer::advanceString()
{
    while (true)
    {
        token.push_back(c);
        ifile.get(c);
        if (c == '"')
        {
            ifile.get(c);
            break;
        }
    };
    while (whiteSetHas(c))
        ifile.get(c); // skip through space, \n, \t
}

void JackTokenizer::handelComment()
{ // think when sum /length /and lare next to each other
    ifile.get(c);
    if (c == '/' || c == '*')
    {
        if (c == '/')
        {
            advanceComment1();
        }
        else if (c == '*')
        {
            advanceComment2();
        }
        if (c == '/')
            handelComment();
    }
    else
    {
        ifile.seekg(-8, std::ios::cur);
        ifile.get(c);
        tType = SYMBOL;
        token = c;
        ifile.get(c);
        while (whiteSetHas(c) && hasMoreTokens())
            ifile.get(c);
    }
}

void JackTokenizer::advanceComment1()
{
    while (true)
    {
        ifile.get(c);
        if (c == '\n')
        {
            ifile.get(c);
            break;
        }
    };
    while (whiteSetHas(c))
        ifile.get(c); // skip through space, \n, \t
}

void JackTokenizer::advanceComment2()
{
    while (true)
    {
        ifile.get(c);
        if (c == '*')
        {
            ifile.get(c);
            if (c == '/')
            {
                ifile.get(c);
                break;
            }
        }
    };
    while (whiteSetHas(c))
        ifile.get(c); // skip through space, \n, \t
}

TokenType JackTokenizer::tokenType()
{
    return tType;
}
string JackTokenizer::keyWord()
{
    return token;
}
char JackTokenizer::symbol()
{
    return token[0];
}
string JackTokenizer::identifier()
{
    return token;
}
int JackTokenizer::intVal()
{
    return stoi(token);
}
string JackTokenizer::stringVal()
{
    return token;
}

bool JackTokenizer::keywordMapHas(string s)
{
    return keywordMap.find(s) != keywordMap.end();
}
bool JackTokenizer::symbolSetHas(char c)
{
    return symbolSet.find(c) != symbolSet.end();
}
bool JackTokenizer::whiteSetHas(char c)
{
    return whiteSet.find(c) != whiteSet.end();
}

void JackTokenizer::printToken()
{
    switch (tType)
    {
    case KEYWORD:
        cout << "<keyword> " << token << " </keyword>\n";
        break;
    case SYMBOL:
        cout << "<symbol> " << token << " </symbol>\n";
        break;
    case IDENTIFIER:
        cout << "<identifier> " << token << " </identifier>\n";
        break;
    case INT_CONST:
        cout << "<integerConstant> " << token << " </integerConstant>\n";
        break;
    case STRING_CONST:
        cout << "<stringConstant> " << token << " </stringConstant>\n";
        break;
    default:
        break;
    }
}