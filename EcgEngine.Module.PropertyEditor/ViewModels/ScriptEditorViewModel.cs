using EcgEngine.Core;
using EcgEngine.Core.Dialogs;
using EcgEngine.Models;
using EcgEngine.Models.VisualScript;
using Prism.Commands;
using Prism.Ioc;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ScriptEditorViewModel : BindableBase, INavigationAware
    {
        private readonly IContainerExtension _containerExtension;
        private readonly IDialogService _dialogService;

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

                if (_selectedTriggerItemIndex == -1)
                {
                    ScopedRegionManager.Regions[RegionNames.ACTION_LIST_REGION].RemoveAll();
                }

                RaisePropertyChanged(nameof(CanDeleteScript));
            }
        }

        public bool CanDeleteScript
        {
            get
            {
                return SelectedTriggerItemIndex >= 0;
            }
        }


        private IRegionManager _scopedRegionManager;
        public IRegionManager ScopedRegionManager
        {
            get { return _scopedRegionManager; }
            set { SetProperty(ref _scopedRegionManager, value); }
        }

        public DelegateCommand ItemSelectedCommand { get; set; }
        public DelegateCommand CreateNewScriptCommand { get; set; }
        public DelegateCommand DeleteScriptCommand { get; set; }

        public ScriptEditorViewModel(IRegionManager regionManager, IContainerExtension containerExtension, IDialogService dialogService)
        {
            _containerExtension = containerExtension;
            _dialogService = dialogService;

            ScopedRegionManager = regionManager.CreateRegionManager();

            ItemSelectedCommand = new DelegateCommand(() =>
            {
                if (SelectedTriggerItemIndex == -1)
                {
                    return;
                }

                var p = new NavigationParameters();
                p.Add("ScriptComponent", ScriptComponents[SelectedTriggerItemIndex]);
                ScopedRegionManager.RequestNavigate(RegionNames.ACTION_LIST_REGION, "ActionEditorPanel", p);
            });

            CreateNewScriptCommand = new DelegateCommand(CreateNewScript);
            DeleteScriptCommand = new DelegateCommand(DeleteScript).ObservesCanExecute(() => CanDeleteScript);
        }

        private void DeleteScript()
        {
            var dialogParams = new DialogParameters();
            dialogParams.Add("Message", "Are you sure to delete this?");
            _dialogService.ShowDialog(DialogNames.CONFIRMATION_DIALOG, dialogParams, (result) =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    var scriptToDeleteIndex = SelectedTriggerItemIndex;
                    SelectedTriggerItemIndex = -1;

                    ScriptComponents.RemoveAt(scriptToDeleteIndex);
                    RefreshTriggerItems();
                }
            });
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
