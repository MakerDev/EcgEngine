using EcgEngine.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace EcgEnginePackageServer.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class BlobStorageController : ControllerBase
    {
        private readonly IBlobStorageFileManager _blobStorageFileManager;

        public BlobStorageController(IBlobStorageFileManager blobStorageFileManager)
        {
            _blobStorageFileManager = blobStorageFileManager;
        }

        [HttpPost("upload/{packageName}")]
        public async Task<ActionResult<PackageUploadResult>> UploadPackageToContainerAsync(string packageName, IFormFile file)
        {
            using (var stream = file.OpenReadStream())
            {                
                var result = await _blobStorageFileManager.UploadPackageAsync(packageName, stream);

                return Ok(result);
            }
        }
    }
}
