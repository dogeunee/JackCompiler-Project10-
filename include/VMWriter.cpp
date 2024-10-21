#include "VMWriter.h"

VMWriter::VMWriter()
{
}
void VMWriter::writePush(segment seg, int index)
{
}
void VMWriter::writePop(segment seg, int index)
{
}
void VMWriter::writeArithmetic(command cmd)
{
}
void VMWriter::writeLabel(string label)
{
}
void VMWriter::writeGoto(string label)
{
}
void VMWriter::writeIf(string label)
{
}
void VMWriter::writeCall(string name, int nArgs)
{
}
void VMWriter::writeFunction(string name, int nLocals)
{
}
void VMWriter::writeReturn()
{
}
void VMWriter::close()
{
}