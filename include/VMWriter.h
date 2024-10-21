#include <string>
#include "data.h"
using namespace std;
class VMWriter
{
public:
    VMWriter();
    void writePush(segment seg, int index);
    void writePop(segment seg, int index);
    void writeArithmetic(command cmd);
    void writeLabel(string label);
    void writeGoto(string label);
    void writeIf(string label);
    void writeCall(string name, int nArgs);
    void writeFunction(string name, int nLocals);
    void writeReturn();
    void close();
};