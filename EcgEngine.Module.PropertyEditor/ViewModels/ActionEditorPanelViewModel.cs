using EcgEngine.Models.VisualScript;
using Prism.Commands;
using Prism.Ioc;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System.Collections.ObjectModel;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionEditorPanelViewModel : BindableBase, INavigationAware
    {
        private ScriptComponent _scriptComponent;
        public ScriptComponent ScriptComponent
        {
            get { return _scriptComponent; }
            set { SetProperty(ref _scriptComponent, value); }
        }

        private ObservableCollection<ActionItemViewModel> _actionItemViewModels
                = new ObservableCollection<ActionItemViewModel>();
        public ObservableCollection<ActionItemViewModel> ActionItemViewModels
        {
            get { return _actionItemViewModels; }
            set { SetProperty(ref _actionItemViewModels, value); }
        }

        private int _selectedTriggerItemIndex = -1;
        private readonly IContainerExtension _containerExtension;
        private readonly IDialogService _dialogService;

        public int SelectedActionItemIndex
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
        public DelegateCommand AddNewActionCommand { get; set; }
        public DelegateCommand EditActionCommand { get; set; }

        public ActionEditorPanelViewModel(IContainerExtension containerExtension, IDialogService dialogService)
        {
            _containerExtension = containerExtension;
            _dialogService = dialogService;

            AddNewActionCommand = new DelegateCommand(AddNewAction);
            EditActionCommand = new DelegateCommand(EditAction);
        }

        private void EditAction()
        {
            _dialogService.ShowDialog("ActionSelectorDialog", null, result =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    //TODO : Add edit functionality. This is replacement by selecting new one again.
                    ScriptComponent.Actions[SelectedActionItemIndex] = result.Parameters.GetValue<Models.VisualScript.Action>("Action");
                }
            });

            RefreshActionItems();
        }

        public void AddNewAction()
        {
            Models.VisualScript.Action action = null;
            //Select new object from selector

            _dialogService.ShowDialog("ActionSelectorDialog", null, result =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    action = result.Parameters.GetValue<Models.VisualScript.Action>("Action");
                }
            });

            ScriptComponent.Actions.Add(action);
            RefreshActionItems();
        }


        public void RefreshActionItems()
        {
            //TODO : restore this value?
            SelectedActionItemIndex = -1;
            ActionItemViewModels.Clear();

            foreach (var action in ScriptComponent.Actions)
            {
                var vm = _containerExtension.Resolve<ActionItemViewModel>();

                //TODO : Try to remove this init stages
                vm.Action = action;
                //TODO : 이거 위치 바꾸기
                vm.EditActionCommand = EditActionCommand;
                ActionItemViewModels.Add(vm);
            }
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
            SelectedActionItemIndex = -1;
            ScriptComponent = navigationContext.Parameters["ScriptComponent"] as ScriptComponent;
            RefreshActionItems();
        }
    }
}
