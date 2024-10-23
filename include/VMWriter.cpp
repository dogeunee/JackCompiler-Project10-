#include "VMWriter.h"

VMWriter::VMWriter(string file)
{
    ofile.open(file);
}
void VMWriter::writePush(segment::segment seg, int index)
{
    ofile << "push " << segReturn(seg) << " " << index << "\n";
}
void VMWriter::writePop(segment::segment seg, int index)
{
    ofile << "pop " << segReturn(seg) << " " << index << "\n";
}
void VMWriter::writeArithmetic(command::command cmd)
{
    ofile << commandReturn(cmd) << "\n";
}
void VMWriter::writeLabel(string label)
{
    ofile << "label " << label << "\n";
}
void VMWriter::writeGoto(string label)
{
    ofile << "goto " << label << "\n";
}
void VMWriter::writeIf(string label)
{
    ofile << "if-goto " << label << "\n";
}
void VMWriter::writeCall(string name, int nArgs)
{
    ofile << "call " << name << " " << nArgs << "\n";
}
void VMWriter::writeFunction(string name, int nLocals)
{
    ofile << "function " << name << " " << nLocals << "\n";
}
void VMWriter::writeReturn()
{
    ofile << "return";
}
void VMWriter::close()
{
    ofile.close();
}
string segReturn(segment::segment seg)
{
    switch (seg)
    {
    case segment::CONST:
        return "constant";
        break;
    case segment::ARG:
        return "argument";
        break;
    case segment::LOCAL:
        return "local";
        break;
    case segment::STATIC:
        return "static";
        break;
    case segment::THIS:
        return "this";
        break;
    case segment::THAT:
        return "this";
        break;
    case segment::POINTER:
        return "pointer";
        break;
    case segment::TEMP:
        return "temp";
        break;
    }
    return "not a segement";
}
string commandReturn(command::command cmd)
{
    switch (cmd)
    {
    case command::ADD:
        return "add";
        break;
    case command::SUB:
        return "sub";
        break;
    case command::NEG:
        return "neg";
        break;
    case command::EQ:
        return "eq";
        break;
    case command::GT:
        return "gt";
        break;
    case command::LT:
        return "lt";
        break;
    case command::AND:
        return "and";
        break;
    case command::OR:
        return "or";
        break;
    case command::NOT:
        return "not";
        break;
    }
}