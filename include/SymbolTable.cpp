#include "SymbolTable.h"
SymbolTable::SymbolTable()
{
}

void SymbolTable::startSubroutine()
{
    subroutineScopeTable.clear();
}
void SymbolTable::define(string _name, string _type, kind _kind)
{
    if (_kind == STATIC || _kind == FIELD)
    {
        classScopeVarCount[_kind]++;
        int num = classScopeVarCount[_kind];
        IdentifierEntry entry;
        entry.index = num;
        entry.kind = _kind;
        entry.type = _type;
        classScopeTable[_name] = entry;
    }
    else if (_kind == ARG || _kind == VAR)
    {
        subroutineScopeVarCount[_kind]++;
        int num = subroutineScopeVarCount[_kind];
        IdentifierEntry entry;
        entry.index = num;
        entry.kind = _kind;
        entry.type = _type;
        classScopeTable[_name] = entry;
    }
}
int SymbolTable::varCount(kind _kind)
{
    if (_kind == STATIC || _kind == FIELD)
    {
        return classScopeVarCount[_kind];
    }
    else if (_kind == ARG || _kind == VAR)
    {
        return subroutineScopeVarCount[_kind];
    }
    return -1;
}
kind SymbolTable::kindOf(string _name)
{
    if (subroutineScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].kind;
    }
    if (classScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].kind;
    }
    return NONE;
}
string SymbolTable::typeOf(string _name)
{
    if (subroutineScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].type;
    }
    if (classScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].type;
    }
    return "null";
}
int SymbolTable::indexOf(string _name)
{
    if (subroutineScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].index;
    }
    if (classScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].index;
    }
    return -1;
}