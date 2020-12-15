using EcgEngine.Core.Interfaces;
using EcgEngine.Models;
using EcgEngine.Models.VariableEngine;
using EcgEngine.Models.VisualScript.ActionPresets;
using EcgEngine.Services;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class SetVariableValueEditorViewModel : BindableBase, IActionEditorViewModel
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

        private bool _isVariableSelected;
        public bool IsVariableSelected
        {
            get { return _isVariableSelected; }
            set { SetProperty(ref _isVariableSelected, value); }
        }

        private EcgVariable _selectedVariable;
        public EcgVariable SelectedVariable
        {
            get { return _selectedVariable; }
            set
            {
                SetProperty(ref _selectedVariable, value);

                if (value != null)
                {
                    IsVariableSelected = true;
                    SelectedVariableName = value.Name;
                }
            }
        }
        private string _selectedVariableName;
        public string SelectedVariableName
        {
            get { return _selectedVariableName; }
            set
            {
                SetProperty(ref _selectedVariableName, value);
            }
        }

        private string _newValue;
        public string NewValue
        {
            get { return _newValue; }
            set { SetProperty(ref _newValue, value); }
        }

        public SetVariableValueEditorViewModel(IGameManager gameManager)
        {
            GameObjects = gameManager.GameObjects;
        }

        public Models.VisualScript.Action GetAction()
        {
            return new SetVariableValue(SelectedVariable, NewValue);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as SetVariableValue;

            if (action == null)
            {
                return;
            }

            SelectedVariable = action.Variable;
            SelectedObject = GameObjects.FirstOrDefault((x) => x.Name == SelectedVariable.ParentName);
            NewValue = action.NewValue;
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
