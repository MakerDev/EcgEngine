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

        private int _selectedObjectIndex;
        public int SelectedObjectIndex
        {
            get { return _selectedObjectIndex; }
            set { SetProperty(ref _selectedObjectIndex, value); }
        }

        public DelegateCommand<GameObject> ObjectSelectedCommand { get; set; }
        public DelegateCommand AddNewObjectCommand { get; set; }
        public GameObjectListViewModel(GameManager gameManager, IRegionManager regionManager)
        {
            _gameManager = gameManager;
            _regionManager = regionManager;

            GameObjects.AddRange(gameManager.GameObjects);

            ObjectSelectedCommand = new DelegateCommand<GameObject>(OnObjectSelected);
            AddNewObjectCommand = new DelegateCommand(AddNewObject);
        }

        private void AddNewObject()
        {
            var newObject = _gameManager.CreateGameObject();
            GameObjects.Add(newObject);
            RaisePropertyChanged(nameof(GameObjects));
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
