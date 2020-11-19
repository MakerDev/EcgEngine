using EcgEngine.Core;
using EcgEngine.Models;
using EcgEngine.Models.VisualScript;
using Prism.Commands;
using Prism.Ioc;
using Prism.Mvvm;
using Prism.Regions;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ScriptEditorViewModel : BindableBase, INavigationAware
    {
        private readonly IRegionManager _regionManager;
        private readonly IContainerExtension _containerExtension;

        public GameObject GameObject { get; set; }

        private List<ScriptComponent> _scriptComponents = new List<ScriptComponent>();
        public List<ScriptComponent> ScriptComponents
        {
            get { return _scriptComponents; }
            set { SetProperty(ref _scriptComponents, value); }
        }

        private ObservableCollection<TriggerItemViewModel> _triggerItemViewModels
            = new ObservableCollection<TriggerItemViewModel>();
        public ObservableCollection<TriggerItemViewModel> TriggerItemViewModels
        {
            get { return _triggerItemViewModels; }
            set { SetProperty(ref _triggerItemViewModels, value); }
        }

        private int _selectedTriggerItemIndex = -1;
        public int SelectedTriggerItemIndex
        {
            get
            {
                return _selectedTriggerItemIndex;
            }
            set
            {
                SetProperty(ref _selectedTriggerItemIndex, value);
            }
        }

        public DelegateCommand ItemSelectedCommand { get; set; }
        public DelegateCommand CreateNewScriptCommand { get; set; }

        public ScriptEditorViewModel(IRegionManager regionManager, IContainerExtension containerExtension)
        {
            _regionManager = regionManager;
            _containerExtension = containerExtension;

            ItemSelectedCommand = new DelegateCommand(() =>
            {
                if (SelectedTriggerItemIndex == -1)
                {
                    return;
                }

                var p = new NavigationParameters();
                p.Add("ScriptComponent", ScriptComponents[SelectedTriggerItemIndex]);
                _regionManager.RequestNavigate(RegionNames.ACTION_LIST_REGION, "ActionEditorPanel", p);
            });

            CreateNewScriptCommand = new DelegateCommand(CreateNewScript);
        }

        public void CreateNewScript()
        {
            //Add script component
            ScriptComponents.Add(new ScriptComponent());
            RefreshTriggerItems();
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
            var gameObject = navigationContext.Parameters["GameObject"] as GameObject;
            SelectedTriggerItemIndex = -1;

            ScriptComponents = gameObject.ScriptComponents;
            RefreshTriggerItems();
        }

        public void RefreshTriggerItems()
        {
            TriggerItemViewModels.Clear();

            foreach (var component in ScriptComponents)
            {
                var vm = _containerExtension.Resolve<TriggerItemViewModel>();
                vm.Trigger = component.Trigger;
                vm.ScriptComponent = component;

                TriggerItemViewModels.Add(vm);
            }
        }
    }
}
