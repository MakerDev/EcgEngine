﻿using EcgEngine.Core.Interfaces;
using EcgEngine.Module.PropertyEditor.ViewModels;
using EcgEngine.Module.PropertyEditor.Views;
using EcgEngine.Module.PropertyEditor.Views.ActionEditorViews;
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

            //containerRegistry.RegisterForNavigation<MoveXEditor, MoveXEditorViewModel>();
            RegisterActionEditors(containerRegistry);
        }

        public void RegisterActionEditors(IContainerRegistry containerRegistry)
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