using Prism.Commands;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Core
{ 

    public class ApplicationCommands : IApplicationCommands
    {
        public CompositeCommand AddNewGameObjectCommand { get; } = new CompositeCommand();
    }
}
