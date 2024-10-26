#include <string>
#include <fstream>
#include "JackTokenizer.h"
#include "SymbolTable.h"
#include "VMWriter.h"
using namespace std;
class CompilationEngine
{
public:
    CompilationEngine(string _ifile, string _ofile);
    void compileClass();
    void complieClassVarDec();
    void compileSubroutine();
    void compileParameterList();
    void compileVarDec();
    void compileStatements();
    void compileDo();
    void compileLet();
    void compileWhile();
    void compileReturn();
    void compileIf();
    void compileExpression();
    void compileTerm();
    int compileExpressionList();
    void eat(string str, TokenType::TokenType tokenType);
    segment::segment kindToSeg(kind::kind kind);
    string labelGen();

private:
    ifstream ifile;
    ofstream ofile;
    JackTokenizer tokenizer;
    SymbolTable symbolTable;
    VMWriter vmWriter;
    int labelint = 0;
};