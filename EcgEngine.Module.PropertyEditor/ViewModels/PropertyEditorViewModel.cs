using EcgEngine.Core.Events;
using EcgEngine.Models;
using Prism.Commands;
using Prism.Events;
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
        private readonly IEventAggregator _eventAggregator;

        public GameObject GameObject
        {
            get { return _gameObject; }
            set {
                SetProperty(ref _gameObject, value); 
                RaisePropertyChanged(nameof(Name));
            }
        }

        public string Name
        {
            get { 
                return GameObject != null ? GameObject.Name : ""; 
            }
            set
            {
                GameObject.Name = value;
                _eventAggregator.GetEvent<GameObjectModifiedEvent>().Publish(GameObject);
            }
        }

        public PropertyEditorViewModel(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;
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
