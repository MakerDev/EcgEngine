using EcgEngine.Models;
using Prism.Commands;
using System;

namespace EcgEngine.Core
{
    public interface IApplicationCommands
    {
        CompositeCommand AddNewGameObjectCommand { get; }
        Func<GameObject> GetCurrentGameObject { get; set; }
    }
}