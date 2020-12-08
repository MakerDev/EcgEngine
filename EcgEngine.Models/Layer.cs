using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace EcgEngine.Models
{
    public class Layer
    {
        public string Name { get; set; }
        /// <summary>
        /// Layer width and heigth
        /// </summary>
        public EcgPoint Size { get; set; } = new EcgPoint();
        /// <summary>
        /// Scale factor for map
        /// </summary>
        public float ScaleFactor { get; set; } = 1.0F;
        /// <summary>
        /// Background tmx model name
        /// </summary>
        public string ModelName { get; set; }
        /// <summary>
        /// Gameobjects that belong to this layer.
        /// </summary>
        public List<GameObject> GameObjects { get; set; }
    }
}
