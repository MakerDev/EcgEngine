using EcgEngine.Core.Dialogs;
using EcgEngine.Core.Interfaces;
using EcgEngine.Models;
using EcgEngine.Models.VariableEngine;
using EcgEngine.Models.VisualScript.ActionPresets;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class IncreaseVariableValueViewModel : BindableBase, IActionEditorViewModel
    {
        private List<GameObject> _gameObjects;
        public List<GameObject> GameObjects
        {
            get { return _gameObjects; }
            set { SetProperty(ref _gameObjects, value); }
        }

        private bool _isObjectSelected = false;
        public bool IsObjectSelected
        {
            get { return _isObjectSelected; }
            set { SetProperty(ref _isObjectSelected, value); }
        }

        private GameObject _selectedObject = null;
        public GameObject SelectedObject
        {
            get { return _selectedObject; }
            set
            {
                SetProperty(ref _selectedObject, value);
                IsObjectSelected = true;
                if (value != null)
                {
                    Variables = _selectedObject.Variables;
                }
            }
        }

        private List<EcgVariable> _variables;
        public List<EcgVariable> Variables
        {
            get { return _variables; }
            set { SetProperty(ref _variables, value); }
        }

        private EcgVariable _selectedVariable;
        public EcgVariable SelectedVariable
        {
            get { return _selectedVariable; }
            set { SetProperty(ref _selectedVariable, value); }
        }

        private bool _isVariableSelected;
        public bool IsVariableSelected
        {
            get { return _isVariableSelected; }
            set { SetProperty(ref _isVariableSelected, value); }
        }

        private string _increaseBy;
        private readonly IDialogService _dialogService;

        public string IncreaseBy
        {
            get { return _increaseBy; }
            set { SetProperty(ref _increaseBy, value); }
        }

        public IncreaseVariableValueViewModel(IDialogService dialogService)
        {
            _dialogService = dialogService;
        }

        public Models.VisualScript.Action GetAction()
        {
            bool result = float.TryParse(IncreaseBy, out float increaseBy);

            if (result == false)
            {
                var p = new DialogParameters();
                p.Add("Message", "IncreaseBy value must be a number");
                _dialogService.ShowDialog(DialogNames.MESSAGE_DIALOG, p, null);
            }

            var action = new IncreaseVariableValue(SelectedVariable, increaseBy);

            return action;
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
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as IncreaseVariableValue;

            if (action == null)
            {
                return;
            }

            SelectedVariable = action.Variable;
            SelectedObject = GameObjects.FirstOrDefault((x) => x.Name == SelectedVariable.ParentName);
            IncreaseBy = action.IncreaseBy.ToString();
        }
    }
}
