using EcgEngine.Models.VisualScript;
using System;

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
        public string SpriteName { get; private set; }
        public string SpritePath { get; private set; }

        public void SelectSpritePath()
        {

        }

        public ScriptComponent ScriptComponent { get; set; }

        
    }
}
