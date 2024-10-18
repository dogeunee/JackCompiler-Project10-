#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(string _ifile, string _ofile)
{
    tokenizer.initFilename(_ifile);
    tokenizer.advance();
    ofile.open(_ofile);
}
void CompilationEngine::eat(string str, TokenType in_ttype)
{
    TokenType ttype = tokenizer.tokenType();
    if (in_ttype == ttype)
    {
        switch (ttype)
        {
        case KEYWORD:
            if (str != tokenizer.keyWord())
            {
                cout << "wrong keyword\n";
            }
            else
            {
                // ofile
                cout << "\t<keyword> " << tokenizer.keyWord() << " </keyword>\n";
            }
            break;
        case SYMBOL:
            if (str != string(1, tokenizer.symbol()))
            {
                cout << "wrong symbol\n"
                     << str << " , " << string(1, tokenizer.symbol());
            }
            else
            {
                // ofile
                cout << "\t<symbol> " << tokenizer.symbol() << " </symbol>\n";
            }
            break;
        case IDENTIFIER:
            // ofile
            cout << "\t<identifier> " << tokenizer.identifier() << " </identifier>\n";
            break;
        case INT_CONST:
            // ofile
            cout << "\t<integerConstant> " << tokenizer.intVal() << " </integerConstant>\n";
            break;
        case STRING_CONST:
            // ofile
            cout << "\t<stringConstant> " << tokenizer.stringVal() << " </stringConstant>\n";
            break;
        }
        if (tokenizer.hasMoreTokens())
            tokenizer.advance();
    }
    else
        cout << "wrong TYPE\n";
}

void CompilationEngine::compileClass()
{
    // ofile
    cout << "<class>\n";
    eat("class", KEYWORD);
    eat("", IDENTIFIER);
    eat("{", SYMBOL);
    while (tokenizer.keyWord() == "static" || tokenizer.keyWord() == "field")
    {
        complieClassVarDec();
    }
    while (tokenizer.keyWord() == "constructor" || tokenizer.keyWord() == "function" || tokenizer.keyWord() == "method")
    {
        compileSubroutine();
    }
    eat("}", SYMBOL);
    // ofile
    cout << "</class>\n";
}
void CompilationEngine::complieClassVarDec()
{
    // ofile
    cout << "<classVarDec>\n";
    if (tokenizer.keyWord() == "static")
    {
        eat("static", KEYWORD);
    }
    else if (tokenizer.keyWord() == "field")
    {
        eat("field", KEYWORD);
    }

    // type
    if (tokenizer.keyWord() == "int")
    {
        eat("int", KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        eat("field", KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        eat("boolean", KEYWORD);
    }
    else
    {
        eat("", IDENTIFIER);
    }

    // varname
    eat("", IDENTIFIER);
    while (tokenizer.symbol() == ',')
    {
        eat(",", SYMBOL);
        eat("", IDENTIFIER);
    }
    eat(";", SYMBOL);
    // ofile
    cout << "</classVarDec>\n";
}

void CompilationEngine::compileSubroutine()
{
    // ofile
    cout << "<subroutineDec>\n";
    if (tokenizer.keyWord() == "constructor")
    {
        eat("constructor", KEYWORD);
    }
    else if (tokenizer.keyWord() == "function")
    {
        eat("function", KEYWORD);
    }
    else if (tokenizer.keyWord() == "method")
    {
        eat("method", KEYWORD);
    }
    // void or type

    if (tokenizer.keyWord() == "void")
    {
        eat("void", KEYWORD);
    }
    else if (tokenizer.keyWord() == "int")
    {
        eat("int", KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        eat("field", KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        eat("boolean", KEYWORD);
    }
    else
    {
        eat("", IDENTIFIER);
    }
    // subroutineName
    eat("", IDENTIFIER);
    eat("(", SYMBOL);
    compileParameterList();
    eat(")", SYMBOL);
    // subroutine body

    // ofile
    cout << "<subroutineBody>\n";
    eat("{", SYMBOL);
    while (tokenizer.keyWord() == "var")
    {
        compileVarDec();
    }
    compileStatements();
    eat("}", SYMBOL);
    // ofile
    cout << "</subroutineBody>\n";
    // ofile
    cout << "</subroutineDec>\n";
}
void CompilationEngine::compileParameterList()
{
    // ofile
    cout << "<parameterList>\n";
    if (tokenizer.symbol() != ')')
    {
        if (tokenizer.keyWord() == "int")
        {
            eat("int", KEYWORD);
        }
        else if (tokenizer.keyWord() == "char")
        {
            eat("field", KEYWORD);
        }
        else if (tokenizer.keyWord() == "boolean")
        {
            eat("boolean", KEYWORD);
        }
        else
        {
            eat("", IDENTIFIER);
        }
        eat("", IDENTIFIER);

        while (tokenizer.symbol() == ',')
        {
            eat(",", SYMBOL);
            if (tokenizer.keyWord() == "int")
            {
                eat("int", KEYWORD);
            }
            else if (tokenizer.keyWord() == "char")
            {
                eat("field", KEYWORD);
            }
            else if (tokenizer.keyWord() == "boolean")
            {
                eat("boolean", KEYWORD);
            }
            else
            {
                eat("", IDENTIFIER);
            }
            eat("", IDENTIFIER);
        }
        eat(";", SYMBOL);
    }
    // ofile
    cout << "</parameterList>\n";
}
void CompilationEngine::compileVarDec()
{
    // ofile
    cout << "<varDec>\n";
    eat("var", KEYWORD);
    if (tokenizer.keyWord() == "int")
    {
        eat("int", KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        eat("field", KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        eat("boolean", KEYWORD);
    }
    else
    {
        eat("", IDENTIFIER);
    }
    eat("", IDENTIFIER);
    while (tokenizer.symbol() == ',')
    {
        eat(",", SYMBOL);
        eat("", IDENTIFIER);
    }
    eat(";", SYMBOL);
    // ofile
    cout << "</varDec>\n";
}
void CompilationEngine::compileStatements()
{
    // ofile
    cout << "<statements>\n";
    string start = tokenizer.keyWord();
    while (start == "let" || start == "if" || start == "while" || start == "do" || start == "return")
    {
        if (start == "let")
        {
            compileLet();
        }
        else if (start == "if")
        {
            compileIf();
        }
        else if (start == "while")
        {
            compileWhile();
        }
        else if (start == "do")
        {
            compileDo();
        }
        else if (start == "return")
        {
            compileReturn();
        }
        start = tokenizer.keyWord();
    }
    // ofile
    cout << "</statements>\n";
}

void CompilationEngine::compileDo()
{
    cout << "<doStatement>\n";
    eat("do", KEYWORD);
    // subroutineCall
    eat("", IDENTIFIER);
    if (tokenizer.symbol() == '(')
    {
        eat("(", SYMBOL);
        compileExpressionList();
        eat(")", SYMBOL);
    }
    else if (tokenizer.symbol() == '.')
    {
        eat(".", SYMBOL);
        eat("", IDENTIFIER);
        eat("(", SYMBOL);
        compileExpressionList();
        eat(")", SYMBOL);
    }
    eat(";", SYMBOL);
    cout << "</doStatement>\n";
}
void CompilationEngine::compileLet()
{
    cout << "<letStatement>\n";
    eat("let", KEYWORD);
    eat("", IDENTIFIER);
    if (tokenizer.symbol() == '[')
    {
        eat("[", SYMBOL);
        eat("", IDENTIFIER);
        eat("]", SYMBOL);
    }
    eat("=", SYMBOL);
    // compileExpression();
    eat("", IDENTIFIER);
    eat(";", SYMBOL);
    cout << "</letStatement>\n";
}
void CompilationEngine::compileWhile()
{
    // ofile
    cout << "<whileStatement>\n";
    eat("while", KEYWORD);
    eat("(", SYMBOL);
    eat("", IDENTIFIER);
    eat(")", SYMBOL);
    eat("{", SYMBOL);
    compileStatements();
    eat("}", SYMBOL);
    eat(";", SYMBOL);
    // ofile
    cout << "</whileStatement>\n";
}
void CompilationEngine::compileReturn()
{
    // ofile
    cout << "<returnStatement>\n";
    eat("return", KEYWORD);
    if (!(tokenizer.symbol() == ';'))
    {
        eat("", IDENTIFIER);
    }
    eat(";", SYMBOL);
    // ofile
    cout << "</returnStatement>\n";
}
void CompilationEngine::compileIf()
{
    // ofile
    cout << "<ifStatement>\n";
    eat("if", KEYWORD);
    eat("(", SYMBOL);
    eat("", IDENTIFIER);
    eat(")", SYMBOL);
    eat("{", SYMBOL);
    compileStatements();
    eat("}", SYMBOL);
    if (tokenizer.keyWord() == "else")
    {
        eat("else", KEYWORD);
        eat("{", SYMBOL);
        compileStatements();
        eat("}", SYMBOL);
    }
    // ofile
    cout << "</ifStatement>\n";
}
void CompilationEngine::compileExpression()
{
    eat("", IDENTIFIER);
}
void CompilationEngine::compileTerm()
{
}
void CompilationEngine::compileExpressionList()
{
    if (tokenizer.symbol() != ')')
    {
        compileExpression();
        while (tokenizer.symbol() == ',')
        {
            eat(",", SYMBOL);
            compileExpression();
        }
    }
}