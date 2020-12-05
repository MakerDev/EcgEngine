using EcgEngine.Models;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public interface IGameManager
    {
        GameData GameData { get; }
        List<GameObject> GameObjects { get; }

        GameObject CreateGameObject(string name = null);
        Task LoadSaveFile(string fullpath);
        Task SaveAsync();
    }
}