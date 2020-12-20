using System;
using System.Threading.Tasks;
using System.IO;
using System.Net.Http;
using System.Text.Json;

namespace EcgEngine.Services
{
    public class BlobStorageFileManager : IBlobStorageFileManager
    {
        private HttpClient _httpClient = new HttpClient();
        private JsonSerializerOptions _defuaultJsonOptions = new JsonSerializerOptions
        {
            PropertyNameCaseInsensitive = true,
        };
        
        private const string API_ENDPOINT = "https://ecgenginepackageserver.azurewebsites.net/";

        public BlobStorageFileManager()
        {
            _httpClient.BaseAddress = new Uri(API_ENDPOINT + "api/blobstorage/");
            _httpClient.DefaultRequestHeaders.Accept.Clear();
            _httpClient.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));
        }

        public async Task<PackageUploadResult> UploadPackageAsync(string packageName, string path)
        {
            string filename = packageName + ".zip";
            string filePath = Path.Combine(path, filename);

            if (!File.Exists(filePath))
            {
                return new PackageUploadResult
                {
                    IsSuccess = false,
                    ErrorMessage = $"{filePath} doesn't exists.",
                };
            }

            var content = new MultipartFormDataContent();
            var fileContent = new ByteArrayContent(File.ReadAllBytes(filePath));

            content.Add(fileContent, "file", filename);

            HttpResponseMessage response = await _httpClient.PostAsync($"upload/{packageName}/false", content);

            if (response.IsSuccessStatusCode)
            {
                string responseString = await response.Content.ReadAsStringAsync();
                var result = JsonSerializer.Deserialize<PackageUploadResult>(responseString, _defuaultJsonOptions);

                return result;
            }

            return new PackageUploadResult
            {
                IsSuccess = false,
                ErrorMessage = "Server Error",
            };
        }
    }
}
