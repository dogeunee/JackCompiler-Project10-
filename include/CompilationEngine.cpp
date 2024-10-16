#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(string _ifile, string _ofile)
{
    tokenizer.initFilename(_ifile);
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
                cout << "wrong\n";
            }
            else
            {
                ofile << "\t<keyword> " << tokenizer.keyWord() << " </keyword>\n";
                tokenizer.advance();
            }
            break;
        case SYMBOL:
            if (str != string(1, tokenizer.symbol()))
            {
                cout << "wrong!\n";
            }
            else
            {
                ofile << "\t<symbol> " << tokenizer.symbol() << " </symbol>\n";
                tokenizer.advance();
            }
            break;
        case IDENTIFIER:
            ofile << "\t<identifier> " << tokenizer.identifier() << " </identifier>\n";
            tokenizer.advance();
            break;
        case INT_CONST:
            ofile << "\t<integerConstant> " << tokenizer.intVal() << " </integerConstant>\n";
            tokenizer.advance();
            break;
        case STRING_CONST:
            ofile << "\t<stringConstant> " << tokenizer.stringVal() << " </stringConstant>\n";
            tokenizer.advance();
            break;
        }
    }
    else
        cout << "wrong!\n";
}

void CompilationEngine::compileClass()
{
    ofile << "<class>\n";
    eat("class", KEYWORD);
    // identifier

    ofile << "</class>\n";
}
void CompilationEngine::complieClassVarDec()
{
}
void CompilationEngine::compileSubroutine()
{
}
void CompilationEngine::compileParameterList()
{
}
void CompilationEngine::compileVarDec()
{
}
void CompilationEngine::compileStatements()
{
}
void CompilationEngine::compileDo()
{
}
void CompilationEngine::compileLet()
{
    cout << "<letStatement>\n";
    eat("", IDENTIFIER);
    eat("=", SYMBOL);
    compileExpression();
    eat(";", SYMBOL);
    cout << "</letStatement>\n";
}
void CompilationEngine::compileWhile()
{
    ofile << "<whileStatement>\n";
    eat("while", KEYWORD);
    eat("(", SYMBOL);
    compileExpression();
    eat(")", SYMBOL);
    eat("{", SYMBOL);
    compileStatements();
    eat("}", SYMBOL);
    eat(";", SYMBOL);
    ofile << "</whileStatement>\n";
}
void CompilationEngine::compileReturn()
{
}
void CompilationEngine::compileIf()
{
}
void CompilationEngine::compileExpression()
{
}
void CompilationEngine::compileTerm()
{
}
void CompilationEngine::compileExpressionList()
{
}