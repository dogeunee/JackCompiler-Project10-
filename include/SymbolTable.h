#include <string>
#include "data.h"
#include <unordered_map>
using namespace std;

class SymbolTable
{
public:
    SymbolTable();
    void startSubroutine();
    void define(string _name, string _type, kind _kind);
    int varCount(kind _kind);
    kind kindOf(string _name);
    string typeOf(string _name);
    int indexOf(string name);

private:
    // hash table copied from https://github.com/mfl28/JackCompiler/blob/master/include/SymbolTable.h
    struct IdentifierEntry
    {
        kind kind;
        std::string type;
        int index;
    };

    std::unordered_map<std::string, IdentifierEntry> classScopeTable;
    std::unordered_map<kind, int> classScopeVarCount;

    std::unordered_map<std::string, IdentifierEntry> subroutineScopeTable;
    std::unordered_map<kind, int> subroutineScopeVarCount;
};