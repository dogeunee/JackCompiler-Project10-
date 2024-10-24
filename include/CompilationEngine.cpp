#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(string _ifile, string _ofile) : tokenizer(_ifile), vmWriter(_ofile)
{
    tokenizer.advance();
}
void CompilationEngine::eat(string str, TokenType::TokenType in_ttype)
{
    TokenType::TokenType ttype = tokenizer.tokenType();
    string symbol = string(1, tokenizer.symbol());
    if (in_ttype == ttype)
    {
        switch (ttype)
        {
        case TokenType::TokenType::KEYWORD:
            if (str != tokenizer.keyWord())
            {
                std::cout << "wrong keyword\n";
            }
            else
            {
                // //ofile
                // ofile << "<keyword> " << tokenizer.keyWord() << " </keyword>\n";
            }
            break;
        case TokenType::TokenType::SYMBOL:
            if (str != symbol)
            {
                std::cout << "wrong symbol\n"
                          << str << " , " << symbol;
            }
            else
            {
                // //ofile
                if (symbol == "<")
                {
                    // ofile << "<symbol> " << "&lt;" << " </symbol>\n";
                }
                else if (symbol == ">")
                {
                    // ofile << "<symbol> " << "&gt;" << " </symbol>\n";
                }
                else if (symbol == "\"")
                {
                    // ofile << "<symbol> " << "&quot;" << " </symbol>\n";
                }
                else if (symbol == "&")
                {
                    // ofile << "<symbol> " << "&amp;" << " </symbol>\n";
                }
                else
                {
                    // ofile << "<symbol> " << tokenizer.symbol() << " </symbol>\n";
                }
            }
            break;
        case TokenType::TokenType::INT_CONST:
            // //ofile
            // ofile << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>\n";
            break;
        case TokenType::TokenType::STRING_CONST:
            // //ofile
            // ofile << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>\n";
            break;
        case TokenType::TokenType::IDENTIFIER:
            // //ofile
            if (symbolTable.getflag())
            {
                symbolTable.define(tokenizer.identifier());

                /*ofile << "<identifier> " << tokenizer.identifier()
                      << " </identifier> -defintion- kind: " << symbolTable.kindOfString(tokenizer.identifier())
                      << " type: " << symbolTable.typeOf(tokenizer.identifier())
                      << " index: " << symbolTable.indexOf(tokenizer.identifier()) << "\n";*/
            }
            else
            {
                kind::kind _kind = symbolTable.kindOf(tokenizer.identifier());
                if (_kind != kind::NONE)
                {
                    /*ofile << "<identifier> " << tokenizer.identifier()
                          << " </identifier> -used- kind: " << symbolTable.kindOfString(tokenizer.identifier())
                          << " type: " << symbolTable.typeOf(tokenizer.identifier())
                          << " index: " << symbolTable.indexOf(tokenizer.identifier()) << "\n";*/
                }
                else
                {
                    /*ofile << "<identifier> " << tokenizer.identifier()
                          << " </identifier> kind: " << "subroutine or class" << "\n";*/
                }
            }
        }

        if (tokenizer.hasMoreTokens())
        {
            tokenizer.advance();
        }
    }
    else
    {
        std::cout << "wrong TYPE\n";
    }
}

void CompilationEngine::compileClass()
{
    // //ofile
    // ofile << "<class>\n";
    eat("class", TokenType::TokenType::KEYWORD);

    symbolTable.classname = tokenizer.identifier();
    eat("", TokenType::TokenType::IDENTIFIER);
    eat("{", TokenType::TokenType::SYMBOL);
    while (tokenizer.keyWord() == "static" || tokenizer.keyWord() == "field")
    {
        complieClassVarDec();
    }
    while (tokenizer.keyWord() == "constructor" || tokenizer.keyWord() == "function" || tokenizer.keyWord() == "method")
    {
        compileSubroutine();
    }
    eat("}", TokenType::TokenType::SYMBOL);
    // //ofile
    // ofile << "</class>\n";
}
void CompilationEngine::complieClassVarDec()
{
    // //ofile
    // ofile << "<classVarDec>\n";
    if (tokenizer.keyWord() == "static")
    {
        symbolTable.setkind(kind::STATIC);
        eat("static", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "field")
    {
        symbolTable.setkind(kind::FIELD);
        eat("field", TokenType::TokenType::KEYWORD);
    }

    // type
    if (tokenizer.keyWord() == "int")
    {
        symbolTable.settype("int");
        eat("int", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        symbolTable.settype("int");
        eat("char", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        symbolTable.settype("bool");
        eat("boolean", TokenType::TokenType::KEYWORD);
    }
    else
    {

        symbolTable.settype("class");
        eat("", TokenType::TokenType::IDENTIFIER);
    }

    // varname
    symbolTable.setflag(true);
    eat("", TokenType::TokenType::IDENTIFIER);
    while (tokenizer.symbol() == ',')
    {
        eat(",", TokenType::TokenType::SYMBOL);
        eat("", TokenType::TokenType::IDENTIFIER);
    }
    symbolTable.setflag(false);
    eat(";", TokenType::TokenType::SYMBOL);
    // //ofile
    // ofile << "</classVarDec>\n";
}

void CompilationEngine::compileSubroutine()
{
    // //ofile
    symbolTable.startSubroutine();
    // ofile << "<subroutineDec>\n";
    if (tokenizer.keyWord() == "constructor")
    {
        eat("constructor", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "function")
    {
        eat("function", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "method")
    {
        eat("method", TokenType::TokenType::KEYWORD);
        symbolTable.define("this", symbolTable.classname, kind::ARG);
    }
    // void or type
    if (tokenizer.keyWord() == "void")
    {
        eat("void", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "int")
    {
        eat("int", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        eat("char", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        eat("boolean", TokenType::TokenType::KEYWORD);
    }
    else
    {
        eat("", TokenType::TokenType::IDENTIFIER);
    }
    // subroutineName
    string subroutineName = tokenizer.identifier();
    eat("", TokenType::TokenType::IDENTIFIER);
    eat("(", TokenType::TokenType::SYMBOL);
    symbolTable.setkind(kind::ARG);
    compileParameterList();
    eat(")", TokenType::TokenType::SYMBOL);
    // subroutine body

    // //ofile
    // ofile << "<subroutineBody>\n";
    eat("{", TokenType::TokenType::SYMBOL);
    while (tokenizer.keyWord() == "var")
    {
        symbolTable.setkind(kind::VAR);
        compileVarDec();
    }
    vmWriter.writeFunction(symbolTable.classname + "." + subroutineName, symbolTable.varCount(kind::kind::VAR));

    compileStatements();
    eat("}", TokenType::TokenType::SYMBOL);
    // //ofile
    // ofile << "</subroutineBody>\n";
    // //ofile
    // ofile << "</subroutineDec>\n";
}
void CompilationEngine::compileParameterList()
{
    // //ofile
    // setkind is ARG
    // ofile << "<parameterList>\n";
    if (tokenizer.symbol() != ')')
    {
        if (tokenizer.keyWord() == "int")
        {
            symbolTable.settype("int");
            eat("int", TokenType::TokenType::KEYWORD);
        }
        else if (tokenizer.keyWord() == "char")
        {
            symbolTable.settype("char");
            eat("char", TokenType::TokenType::KEYWORD);
        }
        else if (tokenizer.keyWord() == "boolean")
        {
            symbolTable.settype("bool");
            eat("boolean", TokenType::TokenType::KEYWORD);
        }
        else
        {

            symbolTable.settype("class");
            eat("", TokenType::TokenType::IDENTIFIER);
        }
        symbolTable.setflag(true);
        eat("", TokenType::TokenType::IDENTIFIER);
        symbolTable.setflag(false);

        while (tokenizer.symbol() == ',')
        {
            eat(",", TokenType::TokenType::SYMBOL);
            if (tokenizer.keyWord() == "int")
            {
                symbolTable.settype("int");
                eat("int", TokenType::TokenType::KEYWORD);
            }
            else if (tokenizer.keyWord() == "char")
            {
                symbolTable.settype("char");
                eat("char", TokenType::TokenType::KEYWORD);
            }
            else if (tokenizer.keyWord() == "boolean")
            {
                symbolTable.settype("bool");
                eat("boolean", TokenType::TokenType::KEYWORD);
            }
            else
            {

                symbolTable.settype("class");
                eat("", TokenType::TokenType::IDENTIFIER);
            }
            symbolTable.setflag(true);
            eat("", TokenType::TokenType::IDENTIFIER);
            symbolTable.setflag(false);
        }
    }
    // //ofile
    // ofile << "</parameterList>\n";
}
void CompilationEngine::compileVarDec()
{
    // setkind to VAR
    eat("var", TokenType::TokenType::KEYWORD);
    if (tokenizer.keyWord() == "int")
    {
        symbolTable.settype("int");
        eat("int", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "char")
    {
        symbolTable.settype("char");
        eat("char", TokenType::TokenType::KEYWORD);
    }
    else if (tokenizer.keyWord() == "boolean")
    {
        symbolTable.settype("bool");
        eat("boolean", TokenType::TokenType::KEYWORD);
    }
    else
    {

        symbolTable.settype(tokenizer.identifier());
        eat("", TokenType::TokenType::IDENTIFIER);
    }
    symbolTable.setflag(true);
    eat("", TokenType::TokenType::IDENTIFIER);
    symbolTable.setflag(false);
    while (tokenizer.symbol() == ',')
    {
        eat(",", TokenType::TokenType::SYMBOL);
        symbolTable.setflag(true);
        eat("", TokenType::TokenType::IDENTIFIER);
        symbolTable.setflag(false);
    }
    eat(";", TokenType::TokenType::SYMBOL);
    // //ofile
    // ofile << "</varDec>\n";
}
void CompilationEngine::compileStatements()
{
    // //ofile
    // ofile << "<statements>\n";
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
    // //ofile
    // ofile << "</statements>\n";
}

void CompilationEngine::compileDo()
{
    // ofile << "<doStatement>\n";
    eat("do", TokenType::TokenType::KEYWORD);
    // subroutineCall

    // option: deal existing identifiers
    string first = tokenizer.identifier();
    string firsttype = symbolTable.typeOf(first);
    eat("", TokenType::TokenType::IDENTIFIER);
    if (tokenizer.symbol() == '(')
    {
        eat("(", TokenType::TokenType::SYMBOL);
        int nargs = compileExpressionList();
        eat(")", TokenType::TokenType::SYMBOL);
        vmWriter.writeCall(symbolTable.classname + "." + first, nargs);
    }
    else if (tokenizer.symbol() == '.')
    {
        eat(".", TokenType::TokenType::SYMBOL);
        string second = tokenizer.identifier();
        eat("", TokenType::TokenType::IDENTIFIER);
        eat("(", TokenType::TokenType::SYMBOL);
        int nargs = compileExpressionList();
        eat(")", TokenType::TokenType::SYMBOL);
        if (firsttype != "null")
        { // object
            vmWriter.writeCall(firsttype + "." + second, nargs);
        }
        else
        {
            vmWriter.writeCall(first + "." + second, nargs);
        }
    }
    eat(";", TokenType::TokenType::SYMBOL);
    // ofile << "</doStatement>\n";
}

void CompilationEngine::compileLet()
{
    // ofile << "<letStatement>\n";

    eat("let", TokenType::TokenType::KEYWORD);
    eat("", TokenType::TokenType::IDENTIFIER);
    if (tokenizer.symbol() == '[')
    {
        eat("[", TokenType::TokenType::SYMBOL);
        compileExpression();
        eat("]", TokenType::TokenType::SYMBOL);
    }
    eat("=", TokenType::TokenType::SYMBOL);
    compileExpression();
    eat(";", TokenType::TokenType::SYMBOL);
    // ofile << "</letStatement>\n";
}
void CompilationEngine::compileWhile()
{
    // //ofile
    // ofile << "<whileStatement>\n";
    eat("while", TokenType::TokenType::KEYWORD);
    eat("(", TokenType::TokenType::SYMBOL);
    compileExpression();
    eat(")", TokenType::TokenType::SYMBOL);
    eat("{", TokenType::TokenType::SYMBOL);
    compileStatements();
    eat("}", TokenType::TokenType::SYMBOL);
    // //ofile
    // ofile << "</whileStatement>\n";
}
void CompilationEngine::compileReturn()
{
    // //ofile
    // ofile << "<returnStatement>\n";
    eat("return", TokenType::TokenType::KEYWORD);
    if (!(tokenizer.symbol() == ';'))
    {
        compileExpression();
    }
    eat(";", TokenType::TokenType::SYMBOL);
    vmWriter.writeReturn();
    // //ofile
    // ofile << "</returnStatement>\n";
}
void CompilationEngine::compileIf()
{
    // //ofile
    // ofile << "<ifStatement>\n";
    eat("if", TokenType::TokenType::KEYWORD);
    eat("(", TokenType::TokenType::SYMBOL);
    compileExpression();
    eat(")", TokenType::TokenType::SYMBOL);
    eat("{", TokenType::TokenType::SYMBOL);
    compileStatements();
    eat("}", TokenType::TokenType::SYMBOL);
    if (tokenizer.keyWord() == "else")
    {
        eat("else", TokenType::TokenType::KEYWORD);
        eat("{", TokenType::TokenType::SYMBOL);
        compileStatements();
        eat("}", TokenType::TokenType::SYMBOL);
    }
    // //ofile
    // ofile << "</ifStatement>\n";
}
void CompilationEngine::compileExpression()
{
    // ofile << "<expression>\n";
    compileTerm();
    while (tokenizer.opSetHas(tokenizer.symbol()))
    {
        char symbol = tokenizer.symbol();
        eat(string(1, symbol), TokenType::TokenType::SYMBOL);
        compileTerm();
        switch (symbol)
        {
        case '+':
            vmWriter.writeArithmetic(command::command::ADD);
            break;
        case '-':
            vmWriter.writeArithmetic(command::command::SUB);
            break;
        case '*':
            vmWriter.writeArithmetic(command::command::MULT);
            break;
        case '/':
            vmWriter.writeArithmetic(command::command::DIV);
            break;
        case '&':
            vmWriter.writeArithmetic(command::command::AND);
            break;
        case '|':
            vmWriter.writeArithmetic(command::command::OR);
            break;
        case '<':
            vmWriter.writeArithmetic(command::command::LT);
            break;
        case '>':
            vmWriter.writeArithmetic(command::command::GT);
            break;
        case '=':
            vmWriter.writeArithmetic(command::command::EQ);
            break;
        }
    }
    // ofile << "</expression>\n";
}
void CompilationEngine::compileTerm()
{
    // ofile << "<term>\n";
    TokenType::TokenType tType = tokenizer.tokenType();
    switch (tType)
    {
    case TokenType::TokenType::KEYWORD:
        if (tokenizer.keyWord() == "true" || tokenizer.keyWord() == "false" || tokenizer.keyWord() == "null" || tokenizer.keyWord() == "this")
        {
            if (tokenizer.keyWord() == "true")
            {
                vmWriter.writePush(segment::CONST, -1);
            }
            else if (tokenizer.keyWord() == "false")
            {
                vmWriter.writePush(segment::CONST, 0);
            }
            else if (tokenizer.keyWord() == "null")
            {
                vmWriter.writePush(segment::CONST, 0);
            }
            else if (tokenizer.keyWord() == "this")
            {
                vmWriter.writePush(segment::POINTER, 0);
            }
        }
        eat(tokenizer.keyWord(), TokenType::TokenType::KEYWORD);
        break;
    case TokenType::TokenType::INT_CONST:
        vmWriter.writePush(segment::CONST, tokenizer.intVal());
        eat(to_string(tokenizer.intVal()), TokenType::TokenType::INT_CONST);
        break;
    case TokenType::TokenType::STRING_CONST:
        // string?
        eat(tokenizer.stringVal(), TokenType::TokenType::STRING_CONST);
        break;
    case TokenType::TokenType::SYMBOL:
        if (tokenizer.symbol() == '(')
        {
            eat("(", TokenType::TokenType::SYMBOL);
            compileExpression();
            eat(")", TokenType::TokenType::SYMBOL);
        }
        else if (tokenizer.symbol() == '-')
        {
            eat("-", TokenType::TokenType::SYMBOL);
            compileTerm();
            vmWriter.writeArithmetic(command::command::NEG);
        }
        else if (tokenizer.symbol() == '~')
        {
            eat("~", TokenType::TokenType::SYMBOL);
            compileTerm();
            vmWriter.writeArithmetic(command::command::NOT);
        }
        break;
    default:
        string first = tokenizer.identifier();
        string firsttype = symbolTable.typeOf(first);
        eat("", TokenType::TokenType::IDENTIFIER);
        if (tokenizer.symbol() == '[')
        {
            eat("[", TokenType::TokenType::SYMBOL);
            compileExpression();
            eat("]", TokenType::TokenType::SYMBOL);
        }
        // subroutine call
        else if (tokenizer.symbol() == '(')
        { // method
            eat("(", TokenType::TokenType::SYMBOL);
            int nargs = compileExpressionList();
            eat(")", TokenType::TokenType::SYMBOL);
            vmWriter.writeCall(symbolTable.classname + "." + first, nargs);
        }
        else if (tokenizer.symbol() == '.')
        {
            eat(".", TokenType::TokenType::SYMBOL);
            string second = tokenizer.identifier();
            eat("", TokenType::TokenType::IDENTIFIER);
            eat("(", TokenType::TokenType::SYMBOL);
            int nargs = compileExpressionList();
            eat(")", TokenType::TokenType::SYMBOL);
            if (firsttype != "null")
            { // object
                vmWriter.writeCall(firsttype + "." + second, nargs);
            }
            else
            {
                vmWriter.writeCall(first + "." + second, nargs);
            }
        }
        else
        {
            // normal variable!
        }
        break;
    }
}

int CompilationEngine::compileExpressionList()
{
    int num = 0;
    if (tokenizer.symbol() != ')')
    {
        num++;
        compileExpression();
        while (tokenizer.symbol() == ',')
        {
            num++;
            eat(",", TokenType::TokenType::SYMBOL);
            compileExpression();
        }
    }
    return num;
}