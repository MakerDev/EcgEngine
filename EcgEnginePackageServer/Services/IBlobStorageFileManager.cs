using System.IO;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public interface IBlobStorageFileManager
    {
        Task<PackageUploadResult> UploadPackageAsync(string packageName, Stream fileStream);
    }
}