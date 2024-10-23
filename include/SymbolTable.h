#include <string>
#include "data.h"
#include <unordered_map>
#include <iostream>
using namespace std;

class SymbolTable
{
public:
    SymbolTable();
    void startSubroutine();
    void define(string _name, string _type, kind::kind _kind);
    void define(string _name);
    int varCount(kind::kind _kind);
    kind::kind kindOf(string _name);
    string kindOfString(string _name);
    string typeOf(string _name);
    int indexOf(string name);
    void setkind(kind::kind kind);
    void settype(string type);
    void setflag(bool b);
    bool getflag();
    string classname;

private:
    // hash table copied from https://github.com/mfl28/JackCompiler/blob/master/include/SymbolTable.h
    struct IdentifierEntry
    {
        kind::kind kind;
        std::string type;
        int index;
    };
    bool validflag = false;
    kind::kind currentKind;
    string currentType;
    std::unordered_map<std::string, IdentifierEntry> classScopeTable;
    std::unordered_map<kind::kind, int> classScopeVarCount;

    std::unordered_map<std::string, IdentifierEntry> subroutineScopeTable;
    std::unordered_map<kind::kind, int> subroutineScopeVarCount;
};