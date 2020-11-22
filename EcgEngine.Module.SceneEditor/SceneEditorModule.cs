using EcgEngine.Module.SceneEditor.ViewModels;
using EcgEngine.Module.SceneEditor.Views;
using Prism.Ioc;
using Prism.Modularity;

namespace EcgEngine.Module.SceneEditor
{
    public class SceneEditorModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {

        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<SceneEditorPanel, SceneEditorPanelViewModel>();
        }
    }
}