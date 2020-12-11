using Ionic.Zip;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public class PackageManager : IPackageManager
    {
        private readonly IBlobStorageFileManager _blobStorageFileManager;
        private readonly IGameManager _gameManager;

        public PackageManager(IBlobStorageFileManager blobStorageFileManager, IGameManager gameManager)
        {
            _blobStorageFileManager = blobStorageFileManager;
            _gameManager = gameManager;
        }

        public async Task<PackageUploadResult> UploadPackageAsync(string packageName, string packageDirectoryPath)
        {
            return await _blobStorageFileManager.UploadPackageAsync(packageName, packageDirectoryPath);
        }

        public void CreatePackage(string packageName, string packageDirectory)
        {
            _gameManager.GameData.PackageName = packageName;

            var zipFilePath = Path.Combine(packageDirectory, packageName) + ".zip";

            var directory = new DirectoryInfo(packageDirectory);
            var saveFile = directory
                .GetFiles().FirstOrDefault(x => x.Name == "ecgsave1.json");

            using (var zip = new ZipFile(Encoding.UTF8))
            {
                zip.CompressionLevel = Ionic.Zlib.CompressionLevel.Default;
                zip.AddFile(saveFile.FullName, "");

                foreach (var subDir in directory.GetDirectories())
                {
                    zip.AddDirectory(subDir.FullName, subDir.Name);
                }

                zip.Save(zipFilePath);
            }

        }
    }
}
