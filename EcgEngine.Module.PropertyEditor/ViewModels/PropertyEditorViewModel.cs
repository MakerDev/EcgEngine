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
                GameObject.Position = new System.Drawing.Point(value, PosY);
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
                GameObject.Position = new System.Drawing.Point(PosX, value);
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

            //HACK: ActionListRegion should be deleted as it's nested region. Create custom
            //region behavior or interface to force clean up the subregions when removing the containing view.
            //Probably the interface should be attached to the view not to the viewmodel
            //_regionManager.Regions.Remove(RegionNames.ACTION_LIST_REGION);
            _regionManager.RequestNavigate(RegionNames.SCRIPT_EDITOR_REGION, "ScriptEditor", p);
        }
    }
}
