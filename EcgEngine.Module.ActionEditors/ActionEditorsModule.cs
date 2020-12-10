using EcgEngine.Core.Interfaces;
using EcgEngine.Module.ActionEditors.ViewModels;
using EcgEngine.Module.ActionEditors.Views;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Mvvm;
using System;
using System.Linq;
using System.Reflection;

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
                .Where(t => t.BaseType == typeof(ActionEditorViewBase))
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

            containerRegistry.RegisterDialog<VariableEditorDialog, VariableEditorDialogViewModel>();
        }
    }
}