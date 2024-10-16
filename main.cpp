#include "include/CompilationEngine.h"

int main()
{
    string str1, str2;
    cin >> str1 >> str2;
    CompilationEngine compEngine(str1, str2);
    compEngine.compileClass();
    return 0;
}