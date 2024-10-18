#include "include/CompilationEngine.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

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
    fs::path p(str1);
    vector<fs::path> FileList;
    if (fs::is_regular_file(p))
    {
        CompilationEngine compEngine(str1, changeToXML(str1));
        compEngine.compileClass();
    }
    else if (fs::is_directory(p))
    {
        for (const auto &entry : fs::directory_iterator(p))
        {
            if (fs::is_regular_file(entry))
            {
                fs::path filePath = entry.path();
                if (filePath.extension() == ".jack")
                {
                    FileList.push_back(filePath);
                }
            }
        }
        for (fs::path file : FileList)
        {
            CompilationEngine compEngine(file.string(), changeToXML(file.string()));
            compEngine.compileClass();
        }
    }

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