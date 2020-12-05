using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public interface IPackageManager
    {
        void CreatePackage(string packageName, string packageDirectory);
        Task<PackageUploadResult> UploadPackageAsync(string packageName, string packageDirectoryPath);
    }
}