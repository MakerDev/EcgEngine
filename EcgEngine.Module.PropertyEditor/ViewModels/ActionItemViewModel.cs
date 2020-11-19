using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionItemViewModel : BindableBase
    {
        private Models.VisualScript.Action _action;
        private readonly IDialogService _dialogService;

        public Models.VisualScript.Action Action
        {
            get { return _action; }
            set
            {
                SetProperty(ref _action, value);

            }
        }

        private DelegateCommand _editActionCommand;
        public DelegateCommand EditActionCommand
        {
            get { return _editActionCommand; }
            set { SetProperty(ref _editActionCommand, value); }
        }

        public ActionItemViewModel(IDialogService dialogService)
        {
            _dialogService = dialogService;
        }
    }
}
