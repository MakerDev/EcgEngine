using Prism.Commands;

namespace EcgEngine.Core
{
    public interface IApplicationCommands
    {
        CompositeCommand AddNewGameObjectCommand { get; }
    }
}