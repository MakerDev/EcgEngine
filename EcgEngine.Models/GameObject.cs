using EcgEngine.Models.VisualScript;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace EcgEngine.Models
{
    /// <summary>
    /// Don't 'new' this class directly.
    /// </summary>
    public class GameObject
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public bool IsPlayer { get; set; }
        public EcgPoint Position { get; set; } = new EcgPoint();
        public string SpriteName { get; set; }
        public string SpritePath { get; set; }
        public float ScaleFactor { get; set; } = 2.0F;

        public List<ScriptComponent> ScriptComponents { get; set; } = new List<ScriptComponent>();
    }
}
