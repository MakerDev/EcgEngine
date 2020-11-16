using EcgEngine.Models.VisualScript;
using Prism.Commands;
using Prism.Ioc;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionEditorPanelViewModel : BindableBase, INavigationAware
    {
        private ScriptComponent _scriptComponent;
        public ScriptComponent ScriptComponent
        {
            get { return _scriptComponent; }
            set { SetProperty(ref _scriptComponent, value); }
        }

        private ObservableCollection<ActionItemViewModel> _actionItemViewModels
                = new ObservableCollection<ActionItemViewModel>();
        public ObservableCollection<ActionItemViewModel> ActionItemViewModels
        {
            get { return _actionItemViewModels; }
            set { SetProperty(ref _actionItemViewModels, value); }
        }

        private int _selectedTriggerItemIndex = -1;
        private readonly IContainerExtension _containerExtension;
        private readonly IDialogService _dialogService;

        public int SelectedTriggerItemIndex
        {
            get
            {
                return _selectedTriggerItemIndex;
            }
            set
            {
                SetProperty(ref _selectedTriggerItemIndex, value);
            }
        }

        public DelegateCommand ItemSelectedCommand { get; set; }
        public DelegateCommand AddNewActionCommand { get; set; }

        public ActionEditorPanelViewModel(IContainerExtension containerExtension, IDialogService dialogService)
        {
            _containerExtension = containerExtension;
            _dialogService = dialogService;

            AddNewActionCommand = new DelegateCommand(AddNewAction);
        }

        public void AddNewAction()
        {
            Models.VisualScript.Action action = null;
            //Select new object from selector

            //TODO : Dialog service bug? Fix this
            _dialogService.ShowDialog("ActionSelectorDialog", null, result =>
            {
                action = result.Parameters.GetValue<Models.VisualScript.Action>("Action");
            });

            ScriptComponent.Action.Add(action);
            RefreshActionItems();
        }
        public void RefreshActionItems()
        {
            ActionItemViewModels.Clear();

            foreach (var action in ScriptComponent.Action)
            {
                var vm = _containerExtension.Resolve<ActionItemViewModel>();
                vm.Action = action;

                ActionItemViewModels.Add(vm);
            }
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            SelectedTriggerItemIndex = -1;
            ScriptComponent = navigationContext.Parameters["ScriptComponent"] as ScriptComponent;
            RefreshActionItems();
        }
    }
}
