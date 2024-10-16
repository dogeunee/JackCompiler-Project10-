#include <string>
#include <fstream>
#include "JackTokenizer.h"
using namespace std;
class CompilationEngine{
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
    void compileExpressionList();
    void eat(string str,TokenType in_ttype);
    private:
    ifstream ifile;
    ofstream ofile;
    JackTokenizer tokenizer;
};