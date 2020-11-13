using EcgEngine.Models;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class PropertyEditorViewModel : BindableBase, INavigationAware
    {
        private GameObject _gameObject;
        public GameObject GameObject
        {
            get { return _gameObject; }
            set { SetProperty(ref _gameObject, value); }
        }

        public PropertyEditorViewModel()
        {

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
            GameObject = navigationContext.Parameters["GameObject"] as GameObject;

        }
    }
}
