using Prism.Regions;

namespace EcgEngine.Core.Interfaces
{
    public interface IActionEditorViewModel : INavigationAware
    {
        public Models.VisualScript.Action GetAction();
    }
}
