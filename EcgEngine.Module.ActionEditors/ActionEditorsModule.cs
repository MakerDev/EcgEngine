using EcgEngine.Core.Interfaces;
using EcgEngine.Module.PropertyEditor.Views.ActionEditorViews;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Mvvm;
using System.Linq;

namespace EcgEngine.Module.ActionEditors
{
    public class ActionEditorsModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {

        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            var types = typeof(MoveXEditor).Assembly
                .GetTypes();

            var actionEditorViews = types
                .Where(t => t.GetInterfaces()
                             .FirstOrDefault(i => i.Name == nameof(IActionEditorView)) != null)
                .ToList();
            var actionEditorViewModels = types
                .Where(t => t.GetInterfaces()
                             .FirstOrDefault(i => i.Name == nameof(IActionEditorViewModel)) != null)
                .ToDictionary((t) => t.Name);

            foreach (var actionEditorView in actionEditorViews)
            {
                ViewModelLocationProvider.Register(actionEditorView.ToString(), actionEditorViewModels[$"{actionEditorView.Name}ViewModel"]);
                containerRegistry.RegisterForNavigation(actionEditorView, actionEditorView.Name);
            }

        }
    }
}