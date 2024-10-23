#include <string>
#include "data.h"
#include <fstream>

using namespace std;
class VMWriter
{
public:
    VMWriter(string file);
    void writePush(segment::segment seg, int index);
    void writePop(segment::segment seg, int index);
    void writeArithmetic(command::command cmd);
    void writeLabel(string label);
    void writeGoto(string label);
    void writeIf(string label);
    void writeCall(string name, int nArgs);
    void writeFunction(string name, int nLocals);
    void writeReturn();
    void close();

private:
    ofstream ofile;
};