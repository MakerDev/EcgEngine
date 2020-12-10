using EcgEngine.Core.Interfaces;
using EcgEngine.Module.ActionEditors.Views;
using EcgEngine.Module.PropertyEditor.ViewModels;
using EcgEngine.Module.PropertyEditor.Views;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Mvvm;
using System.Linq;

namespace EcgEngine.Module.PropertyEditor
{
    public class PropertyEditorModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {

        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.Register<TriggerItemViewModel>();
            containerRegistry.Register<ActionItemViewModel>();

            containerRegistry.RegisterDialog<TriggerEditorWindow, TriggerEditorWindowViewModel>();
            containerRegistry.RegisterDialog<ActionSelectorDialog, ActionSelectorDialogViewModel>();

            containerRegistry.RegisterForNavigation<ScriptEditor, ScriptEditorViewModel>();
            containerRegistry.RegisterForNavigation<ActionEditorPanel, ActionEditorPanelViewModel>();
            containerRegistry.RegisterForNavigation<PropertyEditorView, PropertyEditorViewModel>();
            containerRegistry.RegisterForNavigation<VariableEditor, VariableEditorViewModel>();
        }
    }
}