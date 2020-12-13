using EcgEngine.Core.Events;
using EcgEngine.Models;
using EcgEngine.Models.VariableEngine;
using Prism.Commands;
using Prism.Events;
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
    public class VariableEditorViewModel : BindableBase, INavigationAware
    {
        private GameObject _gameObject;
        private readonly IDialogService _dialogService;
        private readonly IContainerExtension _containerExtension;

        public GameObject GameObject
        {
            get { return _gameObject; }
            set
            {
                SetProperty(ref _gameObject, value);
                VariableItemViewModels.Clear();

                foreach (var variable in _gameObject.Variables)
                {
                    VariableItemViewModels.Add(CreateNewListItemViewModel(variable));
                }
            }
        }

        private ObservableCollection<VariableListItemViewModel> _variableItemViewModels
            = new ObservableCollection<VariableListItemViewModel>();
        public ObservableCollection<VariableListItemViewModel> VariableItemViewModels
        {
            get { return _variableItemViewModels; }
            set
            {
                SetProperty(ref _variableItemViewModels, value);
            }
        }

        private int _currentSelectedVariableIndex = -1;
        public int CurrentSelectedVariableIndex
        {
            get { return _currentSelectedVariableIndex; }
            set { SetProperty(ref _currentSelectedVariableIndex, value); }
        }

        public DelegateCommand AddNewVariableCommand { get; set; }
        public DelegateCommand OpenVariableEditorCommmand { get; set; }

        public VariableEditorViewModel(IDialogService dialogService,
            IEventAggregator eventAggregator,
            IContainerExtension containerExtension
            )
        {
            _dialogService = dialogService;
            _containerExtension = containerExtension;
            eventAggregator.GetEvent<SelectedGameObjectChangedEvent>().Subscribe((newObject) =>
            {
                GameObject = newObject;
            });

            AddNewVariableCommand = new DelegateCommand(AddNewVariable);
            OpenVariableEditorCommmand = new DelegateCommand(OpenVariableEditor);
        }

        public void AddNewVariable()
        {
            _dialogService.ShowDialog("VariableEditorDialog", null, (result) =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    var newVariable = result.Parameters.GetValue<EcgVariable>("EcgVariable");
                    newVariable.ParentName = GameObject.Name;
                    GameObject.Variables.Add(newVariable);
                    VariableItemViewModels.Add(CreateNewListItemViewModel(newVariable));
                }
            });
        }

        public void OpenVariableEditor()
        {
            var selectedVariable = VariableItemViewModels[CurrentSelectedVariableIndex].Variable;

            var p = new DialogParameters();
            p.Add("EcgVariable", selectedVariable);

            _dialogService.ShowDialog("VariableEditorDialog", p, (result) =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    var newVariable = result.Parameters.GetValue<EcgVariable>("EcgVariable");                    
                    GameObject.Variables[CurrentSelectedVariableIndex] = newVariable;
                    VariableItemViewModels[CurrentSelectedVariableIndex] = CreateNewListItemViewModel(newVariable);
                }
            });
        }

        private VariableListItemViewModel CreateNewListItemViewModel(EcgVariable variable)
        {
            var vm = _containerExtension.Resolve<VariableListItemViewModel>();
            vm.Variable = variable;
            vm.EditVairableCommand = OpenVariableEditorCommmand;

            return vm;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            GameObject = navigationContext.Parameters["GameObject"] as GameObject;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
