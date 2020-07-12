#include "pch.h"
#include "FileSystem.h"


void FileSystem::TraverseFilesUsingDFS(const std::string& folder_path, std::map<std::string, int>& tileMap) {
    _finddata_t file_info;
    std::string any_file_pattern = folder_path + "\\*";
    intptr_t handle = _findfirst(any_file_pattern.c_str(), &file_info);
    //If folder_path exsist, using any_file_pattern will find at least two files "." and "..",
    //of which "." means current dir and ".." means parent dir
    if (handle == -1) {
        std::cout << "folder path not exist: " << folder_path << std::endl;
        exit(-1);
    }
    //iteratively check each file or sub_directory in current folder
    int i = 0;
    do {
        std::string file_name = file_info.name; //from char array to string
        //check whtether it is a sub direcotry or a file
        if (file_info.attrib & _A_SUBDIR) {
            if (file_name != "." && file_name != "..") {
                std::string sub_folder_path = folder_path + "\\" + file_name;
                TraverseFilesUsingDFS(sub_folder_path, tileMap);
                std::cout << "a sub_folder path: " << sub_folder_path << std::endl;
            }
        }
        else
        {
            i++;
            tileMap.insert(std::pair<std::string, int>(file_name, i));
            //cout << "file name: " << file_name << endl;
        }

    } while (_findnext(handle, &file_info) == 0);
    //
    _findclose(handle);
}
