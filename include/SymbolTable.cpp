#include "SymbolTable.h"
SymbolTable::SymbolTable()
{
}

void SymbolTable::startSubroutine()
{
    subroutineScopeTable.clear();
    subroutineScopeVarCount.clear();
}
void SymbolTable::define(string _name, string _type, kind::kind _kind)
{
    if (_kind == kind::STATIC || _kind == kind::FIELD)
    {
        IdentifierEntry entry;
        entry.kind = _kind;
        entry.type = _type;
        auto iter = classScopeVarCount.find(_kind);
        int num;
        if (iter == classScopeVarCount.end())
        {
            classScopeVarCount[_kind] = 0;
            entry.index = 0;
        }
        else
        {
            classScopeVarCount[_kind]++;
            num = classScopeVarCount[_kind];
            entry.index = num;
        }
        classScopeTable[_name] = entry;
    }
    else if (_kind == kind::ARG || _kind == kind::VAR)
    {
        IdentifierEntry entry;
        entry.kind = _kind;
        entry.type = _type;
        auto iter = subroutineScopeVarCount.find(_kind);
        int num;
        if (iter == subroutineScopeVarCount.end())
        {
            subroutineScopeVarCount[_kind] = 0;
            entry.index = 0;
        }
        else
        {
            subroutineScopeVarCount[_kind]++;
            int num = subroutineScopeVarCount[_kind];
            entry.index = num;
        }
        classScopeTable[_name] = entry;
    }
}
void SymbolTable::define(string _name)
{
    IdentifierEntry entry;
    int num;
    entry.kind = currentKind;
    entry.type = currentType;
    if (entry.kind == kind::STATIC || entry.kind == kind::FIELD)
    {
        auto iter = classScopeVarCount.find(entry.kind);
        if (iter == classScopeVarCount.end())
        {
            classScopeVarCount[entry.kind] = 0;
            entry.index = 0;
        }
        else
        {
            classScopeVarCount[entry.kind]++;
            num = classScopeVarCount[entry.kind];
            entry.index = num;
        }
        classScopeTable[_name] = entry;
        cout << "symbolTable.cpp define() > name: " << _name << " currentKind: " << classScopeTable[_name].kind << " currentType: " << classScopeTable[_name].type << "\n";
    }
    else if (entry.kind == kind::ARG || entry.kind == kind::VAR)
    {
        auto iter = subroutineScopeVarCount.find(entry.kind);
        if (iter == subroutineScopeVarCount.end())
        {
            subroutineScopeVarCount[entry.kind] = 0;
            entry.index = 0;
        }
        else
        {
            subroutineScopeVarCount[entry.kind]++;
            int num = subroutineScopeVarCount[entry.kind];
            entry.index = num;
        }
        subroutineScopeTable[_name] = entry;
        cout << "symbolTable.cpp define() > name: " << _name << " currentKind: " << subroutineScopeTable[_name].kind << " currentType: " << subroutineScopeTable[_name].type << "\n";
    }
}
int SymbolTable::varCount(kind::kind _kind)
{
    if (_kind == kind::ARG || _kind == kind::VAR)
    {
        auto iter = subroutineScopeVarCount.find(_kind);
        if (iter == subroutineScopeVarCount.end())
        {
            return -1;
        }
        else
            return subroutineScopeVarCount[_kind];
    }
    else if (_kind == kind::STATIC || _kind == kind::FIELD)
    {
        auto iter = classScopeVarCount.find(_kind);
        if (iter == classScopeVarCount.end())
        {
            return -1;
        }
        else
            return classScopeVarCount[_kind];
    }
    return -1;
}
kind::kind SymbolTable::kindOf(string _name)
{
    if (subroutineScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].kind;
    }
    if (classScopeTable.count(_name) > 0)
    {
        return classScopeTable[_name].kind;
    }
    return kind::NONE;
}
string SymbolTable::kindOfString(string _name)
{
    kind::kind _kind = kindOf(_name);
    switch (_kind)
    {
    case kind::ARG:
        return "ARG";
        break;
    case kind::VAR:
        return "VAR";
        break;
    case kind::STATIC:
        return "STATIC";
        break;
    case kind::FIELD:
        return "FIELD";
        break;
    default:
        return "NONE";
    }
}
string SymbolTable::typeOf(string _name)
{
    if (subroutineScopeTable.count(_name) > 0)
    {
        return subroutineScopeTable[_name].type;
    }
    if (classScopeTable.count(_name) > 0)
    {
        return classScopeTable[_name].type;
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
        return classScopeTable[_name].index;
    }
    return -1;
}
void SymbolTable::setkind(kind::kind kind)
{
    currentKind = kind;
}
void SymbolTable::settype(string type)
{
    currentType = type;
}
void SymbolTable::setflag(bool b)
{
    validflag = b;
}
bool SymbolTable::getflag()
{
    return validflag;
}