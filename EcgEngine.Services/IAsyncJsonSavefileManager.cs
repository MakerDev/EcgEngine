using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public interface IAsyncJsonSavefileManager
    {
        Task<bool> DeleteIfExistsAsync(string filename, bool appendExtenstion = true);
        Task<T> LoadAsync<T>(string filename, bool appendExtenstion = true) where T : class;
        Task SaveAsync<T>(T instance, string filename, bool appendExtenstion = true) where T : class;
    }
}