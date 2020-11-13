using EcgEngine.Models;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Services
{
    public class GameManager
    {
        public string SavefilePath { get; private set; } = @"./";
        public string SavefileName { get; private set; } = @"ecgsave1.json";
                
        //TODO : Make multiple layer avaliable
        public Layer DefaultLayer { get; private set; }

        public List<GameObject> GameObjects { get; private set; } = new List<GameObject>();

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
