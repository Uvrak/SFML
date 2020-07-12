#include "pch.h"
#include "Application.h"

using namespace std;
#include "FileSystem.h"

int main() 
{
    Application app;
    app.run();
    std::map<std::string, int> tileMap;
    FileSystem::TraverseFilesUsingDFS("D:\\Tiles", tileMap);
    for (auto i = tileMap.begin(); i != tileMap.end(); i++)
        std::cout << i->first << endl;
    return 0;
    
}