using EcgEngine.Core;
using EcgEngine.Core.Events;
using EcgEngine.Models;
using EcgEngine.Services;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace EcgEngine.Editor.WPF.ViewModels
{

    public class GameObjectListViewModel : BindableBase 
    {
        private readonly GameManager _gameManager;
        private readonly IRegionManager _regionManager;

        //public List<GameObject> GameObjects
        //{
        //    get { 
        //        return _gameManager.GameObjects; 
        //    }
        //}

        private ObservableCollection<GameObject> _gameObjects = new ObservableCollection<GameObject>();
        public ObservableCollection<GameObject> GameObjects
        {
            get { return _gameObjects; }
            set { SetProperty(ref _gameObjects, value); }
        }

        private GameObject _selectedObject = null;
        public GameObject SelectedObject
        {
            get { return _selectedObject; }
            set { SetProperty(ref _selectedObject, value); }
        }

        public DelegateCommand<GameObject> ObjectSelectedCommand { get; set; }
        public DelegateCommand AddNewObjectCommand { get; set; }
        public GameObjectListViewModel(GameManager gameManager, IRegionManager regionManager, IEventAggregator eventAggregator)
        {
            _gameManager = gameManager;
            _regionManager = regionManager;

            GameObjects.AddRange(gameManager.GameObjects);

            eventAggregator.GetEvent<GameObjectModifiedEvent>().Subscribe((modifiedObject) =>
            {
                for (int i = 0; i < GameObjects.Count; i++)
                {
                    if (GameObjects[i].Id == modifiedObject.Id)
                    {
                        GameObjects[i] = modifiedObject;

                        return;
                    }
                }
            });

            ObjectSelectedCommand = new DelegateCommand<GameObject>(OnObjectSelected);
            AddNewObjectCommand = new DelegateCommand(AddNewObject);
        }

        private void AddNewObject()
        {
            var newObject = _gameManager.CreateGameObject();
            GameObjects.Add(newObject);
        }

        private void OnObjectSelected(GameObject selectedObject)
        {
            if (selectedObject == null)
            {
                return;
            }

            var param = new NavigationParameters();
            param.Add("GameObject", selectedObject);

            //TODO : Replace hardcodede data to constant
            _regionManager.RequestNavigate(RegionNames.EDITOR_REGION, "PropertyEditorView", param);
        }
    }
}
