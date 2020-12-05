using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using Azure.Storage.Blobs;
using System.IO;
using Azure.Storage.Blobs.Models;
using Microsoft.Extensions.Configuration;

namespace EcgEngine.Services
{

    public class BlobStorageFileManager : IBlobStorageFileManager
    {
        //TODO : Don't hardcode this!!
        public string ConnectionString { get; private set; } = "";

        public BlobStorageFileManager(IConfiguration configuration)
        {
            ConnectionString = configuration["ContainerConnectionString"];
        }

        //TODO : Change this for filestream version
        public async Task<PackageUploadResult> UploadPackageAsync(string packageName, Stream fileStream)
        {
            string connectionString = ConnectionString;

            BlobContainerClient container = new BlobContainerClient(connectionString, "packagecontainer");
            await container.CreateIfNotExistsAsync();

            string blobName = packageName + ".zip";

            BlobClient blob = container.GetBlobClient(blobName);

            if (await blob.ExistsAsync())
            {
                return new PackageUploadResult
                {
                    IsSuccess = false,
                    ErrorMessage = $"Package name, {packageName} is already taken.",
                };
            }

            await blob.UploadAsync(fileStream);

            return new PackageUploadResult
            {
                IsSuccess = true,
                ErrorMessage = "",
            };
        }
    }
}
