#include "JackTokenizer.h"
JackTokenizer::JackTokenizer()
{
    keywordMap.insert({"class", KeyWord::KeyWord::CLASS});
    keywordMap.insert({"constructor", KeyWord::KeyWord::CONSTRUCTOR});
    keywordMap.insert({"function", KeyWord::KeyWord::FUNCTION});
    keywordMap.insert({"method", KeyWord::KeyWord::METHOD});
    keywordMap.insert({"field", KeyWord::KeyWord::FIELD});
    keywordMap.insert({"static", KeyWord::KeyWord::STATIC});
    keywordMap.insert({"var", KeyWord::KeyWord::VAR});
    keywordMap.insert({"int", KeyWord::KeyWord::INT});
    keywordMap.insert({"char", KeyWord::KeyWord::CHAR});
    keywordMap.insert({"boolean", KeyWord::KeyWord::BOOLEAN});
    keywordMap.insert({"void", KeyWord::KeyWord::VOID});
    keywordMap.insert({"true", KeyWord::KeyWord::TRUE});
    keywordMap.insert({"false", KeyWord::KeyWord::FALSE});
    keywordMap.insert({"null", KeyWord::KeyWord::_NULL});
    keywordMap.insert({"this", KeyWord::KeyWord::THIS});
    keywordMap.insert({"let", KeyWord::KeyWord::LET});
    keywordMap.insert({"do", KeyWord::KeyWord::DO});
    keywordMap.insert({"if", KeyWord::KeyWord::IF});
    keywordMap.insert({"else", KeyWord::KeyWord::ELSE});
    keywordMap.insert({"while", KeyWord::KeyWord::WHILE});
    keywordMap.insert({"return", KeyWord::KeyWord::RETURN});
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
    opSet.insert('+');
    opSet.insert('-');
    opSet.insert('*');
    opSet.insert('/');
    opSet.insert('&');
    opSet.insert('|');
    opSet.insert('<');
    opSet.insert('>');
    opSet.insert('=');
}
JackTokenizer::JackTokenizer(string filename)
{
    ifile.open(filename);
    ifile.get(c);
    keywordMap.insert({"class", KeyWord::KeyWord::CLASS});
    keywordMap.insert({"constructor", KeyWord::KeyWord::CONSTRUCTOR});
    keywordMap.insert({"function", KeyWord::KeyWord::FUNCTION});
    keywordMap.insert({"method", KeyWord::KeyWord::METHOD});
    keywordMap.insert({"field", KeyWord::KeyWord::FIELD});
    keywordMap.insert({"static", KeyWord::KeyWord::STATIC});
    keywordMap.insert({"var", KeyWord::KeyWord::VAR});
    keywordMap.insert({"int", KeyWord::KeyWord::INT});
    keywordMap.insert({"char", KeyWord::KeyWord::CHAR});
    keywordMap.insert({"boolean", KeyWord::KeyWord::BOOLEAN});
    keywordMap.insert({"void", KeyWord::KeyWord::VOID});
    keywordMap.insert({"true", KeyWord::KeyWord::TRUE});
    keywordMap.insert({"false", KeyWord::KeyWord::FALSE});
    keywordMap.insert({"null", KeyWord::KeyWord::_NULL});
    keywordMap.insert({"this", KeyWord::KeyWord::THIS});
    keywordMap.insert({"let", KeyWord::KeyWord::LET});
    keywordMap.insert({"do", KeyWord::KeyWord::DO});
    keywordMap.insert({"if", KeyWord::KeyWord::IF});
    keywordMap.insert({"else", KeyWord::KeyWord::ELSE});
    keywordMap.insert({"while", KeyWord::KeyWord::WHILE});
    keywordMap.insert({"return", KeyWord::KeyWord::RETURN});
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
    opSet.insert('+');
    opSet.insert('-');
    opSet.insert('*');
    opSet.insert('/');
    opSet.insert('&');
    opSet.insert('|');
    opSet.insert('<');
    opSet.insert('>');
    opSet.insert('=');
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
            tType = TokenType::TokenType::SYMBOL;
            token = c;
            ifile.get(c);
            while (whiteSetHas(c) && hasMoreTokens())
                ifile.get(c);
        }
        else if (isdigit(c))
        {
            tType = TokenType::TokenType::INT_CONST;
            advance2();
        }
        else if (c == '"')
        {
            tType = TokenType::TokenType::STRING_CONST;
            ifile.get(c);
            advanceString();
        }
        else
        {
            advance2();
            if (keywordMapHas(token))
            {
                tType = TokenType::TokenType::KEYWORD;
            }
            else
            {
                tType = TokenType::TokenType::IDENTIFIER;
            }
        }
    }
    if (token.length() == 0)
    {
        advance();
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
        tType = TokenType::TokenType::SYMBOL;
        token = '/';
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

TokenType::TokenType JackTokenizer::tokenType()
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
bool JackTokenizer::opSetHas(char c)
{
    return opSet.find(c) != opSet.end();
}

void JackTokenizer::printToken()
{
    switch (tType)
    {
    case TokenType::TokenType::KEYWORD:
        cout << "<keyword> " << token << " </keyword>\n";
        break;
    case TokenType::TokenType::SYMBOL:
        cout << "<symbol> " << token << " </symbol>\n";
        break;
    case TokenType::TokenType::IDENTIFIER:
        cout << "<identifier> " << token << " </identifier>\n";
        break;
    case TokenType::TokenType::INT_CONST:
        cout << "<integerConstant> " << token << " </integerConstant>\n";
        break;
    case TokenType::TokenType::STRING_CONST:
        cout << "<stringConstant> " << token << " </stringConstant>\n";
        break;
    default:
        break;
    }
}