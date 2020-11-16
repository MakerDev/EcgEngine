using EcgEngine.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public class GameManager
    {
        private readonly IAsyncJsonSavefileManager _jsonSavefileManager;

        public GameData GameData { get; private set; } = new GameData();

        public List<GameObject> GameObjects
        {
            get
            {
                return GameData.GameObjects;
            }
        }

        public GameManager(IAsyncJsonSavefileManager jsonSavefileManager)
        {
            _jsonSavefileManager = jsonSavefileManager;
        }

        public async Task LoadSaveFile(string fullpath)
        {
            //TODO : Improve this by aggregating all svae-file related information to seperate class
            var gameData = await _jsonSavefileManager.LoadAsync<GameData>(fullpath, false);

            GameData = gameData;
        }

        public async Task SaveAsync()
        {
            var fullpath = Path.Combine(GameData.SavefilePath, GameData.SavefileName);
            await _jsonSavefileManager.SaveAsync(GameData, fullpath, false);
        }

        public GameObject CreateGameObject(string name = null)
        {
            var gameObject = new GameObject();
            gameObject.Id = GameObjects.Count;

            gameObject.Name = name ?? $"gameobject{gameObject.Id}";

            GameObjects.Add(gameObject);

            return gameObject;
        }
    }
}
