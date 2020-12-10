using EcgEngine.Models;
using Prism.Commands;
using System;

namespace EcgEngine.Core
{

    public class ApplicationCommands : IApplicationCommands
    {
        public CompositeCommand AddNewGameObjectCommand { get; } = new CompositeCommand();

        public Func<GameObject> GetCurrentGameObject { get; set; }
    }
}
