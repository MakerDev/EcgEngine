using EcgEngine.Core.Interfaces;
using EcgEngine.Models;
using EcgEngine.Models.VariableEngine;
using EcgEngine.Models.VisualScript.ActionPresets;
using EcgEngine.Services;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class ConditionalActionEditorViewModel : BindableBase, IActionEditorViewModel
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

                if (value != null)
                {
                    IsObjectSelected = true;
                    Variables = _selectedObject.Variables;
                }
            }
        }

        private List<EcgVariable> _variables;
        public List<EcgVariable> Variables
        {
            get { return _variables; }
            set
            {
                SetProperty(ref _variables, value);
            }
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

        private bool _isVariableSelected = false;
        public bool IsVariableSelected
        {
            get { return _isVariableSelected; }
            set { SetProperty(ref _isVariableSelected, value); }
        }

        private string valueToCompare = "";
        public string ValueToCompare
        {
            get { return valueToCompare; }
            set { SetProperty(ref valueToCompare, value); }
        }

        private string _selectedVariableName = "";
        public string SelectedVariableName
        {
            get { return _selectedVariableName; }
            set { SetProperty(ref _selectedVariableName, value); }
        }

        private ConditionType _conditionType = ConditionType.EqualTo;
        public ConditionType ConditionType
        {
            get { return _conditionType; }
            set { SetProperty(ref _conditionType, value); }
        }


        public ConditionalActionEditorViewModel(IGameManager gameManager)
        {
            GameObjects = gameManager.GameObjects;
        }

        public Models.VisualScript.Action GetAction()
        {
            var variableCondition = new VariableCondition(SelectedVariableName, SelectedObject.Name, ConditionType, ValueToCompare);

            return new ConditionalAction(variableCondition);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as ConditionalAction;

            if (action == null)
            {
                return;
            }

            var variableCondition = action.VariableCondition;

            //WARNING : This initialization order matters
            SelectedObject = GameObjects.FirstOrDefault((x) => x.Name == variableCondition.TargetObjectName);
            SelectedVariable = SelectedObject.Variables.FirstOrDefault(x => x.Name == variableCondition.TargetVariableName);
            ValueToCompare = variableCondition.ValueToCompare;
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
