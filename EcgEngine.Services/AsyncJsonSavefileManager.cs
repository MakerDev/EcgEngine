using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public class AsyncJsonSavefileManager : IAsyncJsonSavefileManager
    {
        public static string SavefileFolder { get; private set; }
            = Path.Combine(Environment.CurrentDirectory, "savefiles");

        private JsonSerializerSettings _jsonSettings = new JsonSerializerSettings
        {
            TypeNameHandling = TypeNameHandling.All,
            NullValueHandling = NullValueHandling.Ignore,
        };

        public AsyncJsonSavefileManager()
        {
            if (!Directory.Exists(SavefileFolder))
                Directory.CreateDirectory(SavefileFolder);
        }

        public Task<bool> DeleteIfExistsAsync(string filename, bool appendExtenstion = true)
        {
            string path = Path.Combine(SavefileFolder, filename);

            if (appendExtenstion)
                path += ".json";

            if (File.Exists(path))
            {
                File.Delete(path);
                return Task.FromResult(true);
            }

            return Task.FromResult(false);
        }

        public Task<T> LoadAsync<T>(string filename, bool appendExtenstion = true) where T : class
        {
            string path = Path.Combine(SavefileFolder, filename);

            if (appendExtenstion)
                path += ".json";

            if (!File.Exists(path))
                return Task.FromResult<T>(null);

            string jsonString = File.ReadAllText(path);
            T instance = JsonConvert.DeserializeObject<T>(jsonString, _jsonSettings);

            return Task.FromResult(instance);
        }

        public Task SaveAsync<T>(T instance, string filename, bool appendExtenstion = true) where T : class
        {
            string path = Path.Combine(SavefileFolder, filename);

            if (appendExtenstion)
                path += ".json";

            string jsonString = JsonConvert.SerializeObject(instance, Formatting.Indented, _jsonSettings);
            File.WriteAllText(path, jsonString);

            return Task.CompletedTask;
        }
    }
}
