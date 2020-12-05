#include "FileHelper.h"
#include "EngineManager.h"

using namespace std;

std::string FileHelper::CombinePath(const std::string& p1, const std::string& p2)
{
	if (p1.compare("") == 0)
	{
		return p2;
	}

	return p1 + "/" + p2;
}

std::string FileHelper::GetPackageRelativePath(const std::string& filename)
{
	const auto& packageName = EngineManager::GetInstance()->GetPackageName();

	return CombinePath(packageName, filename);
}

void FileHelper::RemoveDirectoryInPath(std::string* origianal, const std::string& directoryToRemove)
{
	size_t startPos = origianal->find(directoryToRemove);
	
	if (startPos == string::npos)
	{
		return;
	}

	origianal->replace(startPos, directoryToRemove.length(), "");
}
