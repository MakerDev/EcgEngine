using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Core.Dialogs.ViewModels
{
    public class ConfirmationDialogViewModel : BindableBase, IDialogAware
    {
        private string _message;
        public string Message
        {
            get { return _message; }
            set { SetProperty(ref _message, value); }
        }

        public string Title => "Comfirmation Dialog";

        public event Action<IDialogResult> RequestClose;

        public DelegateCommand<string> CloseDialogCommand { get; set; }

        public ConfirmationDialogViewModel()
        {
            CloseDialogCommand = new DelegateCommand<string>(CloseDialog);
        }

        private void CloseDialog(string result)
        {
            var dialogResult = result == "Yes" ? ButtonResult.OK : ButtonResult.Cancel;

            RequestClose.Invoke(new DialogResult(dialogResult));
        }

        public bool CanCloseDialog()
        {
            return true;
        }

        public void OnDialogClosed()
        {
        }

        public void OnDialogOpened(IDialogParameters parameters)
        {
            Message = parameters.GetValue<string>("Message") ?? "Are you sure to do this?";
        }
    }
}
