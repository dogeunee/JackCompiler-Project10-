#include "include/CompilationEngine.h"

int main()
/*{
    JackTokenizer jack;
    jack.initFilename("test/Main.jack");
    while (jack.hasMoreTokens())
    {
        jack.advance();
    }
}*/
{
    string str1, str2;
    cin >> str1 >> str2;
    CompilationEngine compEngine(str1, str2);
    compEngine.compileClass();
    return 0;
}