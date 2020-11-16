using EcgEngine.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace EcgEngine.Services
{
    public class GameData
    {
        public string SavefilePath { get; set; } = Directory.GetCurrentDirectory();
        public string SavefileName { get; set; } = @"ecgsave1.json";

        //TODO : Make multiple layer avaliable
        public Layer DefaultLayer { get; set; } = new Layer();

        public List<GameObject> GameObjects { get; set; } = new List<GameObject>();
    }
}
