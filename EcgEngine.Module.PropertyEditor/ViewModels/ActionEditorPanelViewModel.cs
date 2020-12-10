using EcgEngine.Core.Dialogs;
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
                RaisePropertyChanged(nameof(CanDeleteAction));
            }
        }
        public bool CanDeleteAction
        {
            get
            {
                return SelectedActionItemIndex >= 0;
            }
        }

        public DelegateCommand AddNewActionCommand { get; set; }
        public DelegateCommand EditActionCommand { get; set; }
        public DelegateCommand DeleteCommand { get; set; }

        public ActionEditorPanelViewModel(IContainerExtension containerExtension, IDialogService dialogService)
        {
            _containerExtension = containerExtension;
            _dialogService = dialogService;

            AddNewActionCommand = new DelegateCommand(AddNewAction);
            EditActionCommand = new DelegateCommand(EditAction);
            DeleteCommand = new DelegateCommand(DeleteScript).ObservesCanExecute(() => CanDeleteAction);
        }

        private void DeleteScript()
        {
            var dialogParams = new DialogParameters();
            dialogParams.Add("Message", "Are you sure to delete this?");
            _dialogService.ShowDialog(DialogNames.CONFIRMATION_DIALOG, dialogParams, (result) =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    var scriptToDeleteIndex = SelectedActionItemIndex;
                    SelectedActionItemIndex = -1;

                    ScriptComponent.Actions.RemoveAt(scriptToDeleteIndex);
                    RefreshActionItems();
                }
            });
        }

        private void EditAction()
        {
            var dialogParameters = new DialogParameters();
            dialogParameters.Add("OriginalAction", ScriptComponent.Actions[SelectedActionItemIndex]);

            _dialogService.ShowDialog("ActionSelectorDialog", dialogParameters, result =>
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

            _dialogService.ShowDialog("ActionSelectorDialog", null, result =>
            {
                if (result.Result == ButtonResult.OK)
                {
                    action = result.Parameters.GetValue<Models.VisualScript.Action>("Action");
                    ScriptComponent.Actions.Add(action);
                    RefreshActionItems();
                }
            });
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

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            SelectedActionItemIndex = -1;
            ScriptComponent = navigationContext.Parameters["ScriptComponent"] as ScriptComponent;
            RefreshActionItems();
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
