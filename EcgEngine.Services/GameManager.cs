using EcgEngine.Models;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Services
{
    public class GameManager
    {
        private readonly IAsyncJsonSavefileManager _jsonSavefileManager;

        public string SavefilePath { get; private set; } = @"./";
        public string SavefileName { get; private set; } = @"ecgsave1.json";
                
        //TODO : Make multiple layer avaliable
        public Layer DefaultLayer { get; private set; }

        public List<GameObject> GameObjects { get; private set; } = new List<GameObject>();

        public GameManager(IAsyncJsonSavefileManager jsonSavefileManager)
        {
            _jsonSavefileManager = jsonSavefileManager;
        }

        public async Task LoadSaveFile(string fullpath)
        {
            //TODO : Improve this by aggregating all svae-file related information to seperate class
            var gameManager = await _jsonSavefileManager.LoadAsync<GameManager>(fullpath, false);
            SavefileName = gameManager.SavefileName;
            SavefilePath = gameManager.SavefilePath;
            DefaultLayer = gameManager.DefaultLayer;
            GameObjects = gameManager.GameObjects;
        }

        public async Task SaveAsync()
        {
            await _jsonSavefileManager.SaveAsync(this, SavefilePath + SavefileName);
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
