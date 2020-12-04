#include "FileHelper.h"
#include "EngineManager.h"

std::string FileHelper::CombinePath(const std::string& p1, const std::string& p2)
{
	if (p1.compare("") == 0)
	{
		return p2;
	}

	return p1 + "/" + p2;
}

std::string FileHelper::GetPackageRelativePath(const std::string& filename) noexcept
{
	const auto& packageName = EngineManager::GetInstance()->GetPackageName();

	return CombinePath(packageName, filename);
}
