#include "include/CompilationEngine.h"
#include <filesystem>
#include <iostream>
string changeToXML(string str1)
{
    std::filesystem::path filePath(str1);
    filePath.replace_extension(".xml");
    string fileName = filePath.filename().string();
    string newPath = "test/" + fileName;
    return newPath;
}
int main(int argc, char *argv[])
{
    string str1 = argv[1];
    CompilationEngine compEngine(str1, changeToXML(str1));
    compEngine.compileClass();
    return 0;
}
/*{
    JackTokenizer jack;
    jack.initFilename("test/Main.jack");
    while (jack.hasMoreTokens())
    {
        jack.advance();
    }
}*/