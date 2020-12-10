using EcgEngine.Core;
using EcgEngine.Core.Events;
using EcgEngine.Models;
using Prism.Events;
using Prism.Mvvm;
using Prism.Regions;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class PropertyEditorViewModel : BindableBase, INavigationAware
    {
        //Dummy temp var
        private GameObject _gameObject = new GameObject();
        private readonly IEventAggregator _eventAggregator;
        private readonly IRegionManager _regionManager;

        public GameObject GameObject
        {
            get { return _gameObject; }
            set
            {
                SetProperty(ref _gameObject, value);
                RaisePropertyChanged(nameof(Name));
                RaisePropertyChanged(nameof(PosY));
                RaisePropertyChanged(nameof(PosX));
            }
        }

        public string Name
        {
            get
            {
                return GameObject != null ? GameObject.Name : "";
            }
            set
            {
                GameObject.Name = value;
                _eventAggregator.GetEvent<GameObjectModifiedEvent>().Publish(GameObject);
            }
        }

        private int _posX;
        public int PosX
        {
            get
            {
                return GameObject.Position.X;
            }
            set
            {
                GameObject.Position = new EcgPoint(value, PosY);
                SetProperty(ref _posX, value);
            }
        }

        private int _posY;
        public int PosY
        {
            get
            {
                return GameObject.Position.Y;
            }
            set
            {
                GameObject.Position = new EcgPoint(PosX, value);
                SetProperty(ref _posY, value);
            }
        }

        public PropertyEditorViewModel(IEventAggregator eventAggregator, IRegionManager regionManager)
        {
            _eventAggregator = eventAggregator;
            _regionManager = regionManager;
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

            var p = new NavigationParameters();
            p.Add("GameObject", GameObject);

            _regionManager.RequestNavigate(RegionNames.SCRIPT_EDITOR_REGION, "ScriptEditor", p);
            _regionManager.RequestNavigate(RegionNames.VARIABLE_EDITOR_REGION, "VariableEditor", p);
        }
    }
}
