using Aspose.Zip;
using Aspose.Zip.Saving;
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

            using (FileStream zipFile = File.Open(packageName + ".zip", FileMode.Create))
            {
                var directory = new DirectoryInfo(packageDirectory);
                var saveFile = directory
                    .GetFiles().FirstOrDefault(x => x.Extension == ".json");

                using (var archive = new Archive(new ArchiveEntrySettings()))
                {
                    archive.CreateEntry(saveFile.Name, saveFile);

                    foreach (var dir in directory.GetDirectories())
                    {
                        archive.CreateEntries(dir);
                    }
                    
                    archive.Save(zipFile, new ArchiveSaveOptions
                    {
                        Encoding = Encoding.UTF8,
                    });
                }
            }
        }
    }
}
