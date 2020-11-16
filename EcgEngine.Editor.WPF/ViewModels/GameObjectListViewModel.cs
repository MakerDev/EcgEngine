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
using System.Runtime.InteropServices.WindowsRuntime;

namespace EcgEngine.Editor.WPF.ViewModels
{

    public class GameObjectListViewModel : BindableBase
    {
        private readonly GameManager _gameManager;
        private readonly IRegionManager _regionManager;

        public Action RefreshList { get; set; } = null;

        private ObservableCollection<GameObject> _gameObjects = new ObservableCollection<GameObject>();
        public ObservableCollection<GameObject> GameObjects
        {
            get
            {
                return _gameObjects;
            }
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

        public DelegateCommand ObjectSelectedCommand { get; set; }
        public DelegateCommand AddNewObjectCommand { get; set; }
        public GameObjectListViewModel(GameManager gameManager,
                                       IRegionManager regionManager,
                                       IEventAggregator eventAggregator)
        {
            _gameManager = gameManager;
            _regionManager = regionManager;

            //TODO : 두 번쨰 로딩에서 오브젝트 클릭하면 터지는 거 해결하기
            ObjectSelectedCommand = new DelegateCommand(OnObjectSelected);
            AddNewObjectCommand = new DelegateCommand(AddNewObject);

            eventAggregator.GetEvent<SavefileLoadedEvent>().Subscribe(() =>
            {
                SelectedObjectIndex = -1;
                GameObjects.Clear();
                GameObjects.AddRange(_gameManager.GameObjects);
            });

            eventAggregator.GetEvent<GameObjectModifiedEvent>().Subscribe((obj) =>
            {
                RefreshList?.Invoke();
            });
        }

        private void AddNewObject()
        {
            var newObject = _gameManager.CreateGameObject();
            GameObjects.Add(newObject);
        }

        private void OnObjectSelected()
        {
            if (SelectedObjectIndex == -1)
            {
                _regionManager.Regions[RegionNames.EDITOR_REGION].RemoveAll();
                return;
            }

            GameObject selectedObject = GameObjects[SelectedObjectIndex];

            var param = new NavigationParameters();
            param.Add("GameObject", selectedObject);

            //TODO : Replace hardcodede data to constant
            _regionManager.RequestNavigate(RegionNames.EDITOR_REGION, "PropertyEditorView", param);
        }
    }
}
