#pragma once
#include <string>

class FileHelper
{
public:
	static std::string CombinePath(const std::string& p1, const std::string& p2);
	static std::string GetPackageRelativePath(const std::string& filename);
	static void RemoveDirectoryInPath(std::string* origianal, const std::string& directoryToRemove);
};

