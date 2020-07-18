#ifndef FILESYSTEM_H
#define FILESYSTEM_H
class FileSystem
{
public:
	static void TraverseFilesUsingDFS(const std::string& folder_path, std::map<std::string, int>& tileMap);
	static std::vector<std::string> split(std::string str, char breakOn);
};
#endif;

