using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Core.Dialogs.ViewModels
{
    public class TextInputDialogViewModel : BindableBase, IDialogAware
    {
        public string Title => "TextInputDialog";

        public event Action<IDialogResult> RequestClose;


        private string _message = "";
        public string Message
        {
            get { return _message; }
            set { SetProperty(ref _message, value); }
        }

        private string _userInput = "";
        public string UserInput
        {
            get { return _userInput; }
            set { SetProperty(ref _userInput, value); }
        }

        public DelegateCommand CloseDialogCommand { get; set; }


        public TextInputDialogViewModel()
        {
            CloseDialogCommand = new DelegateCommand(() =>
            {
                var dialogParam = new DialogParameters();
                dialogParam.Add(nameof(UserInput), UserInput);

                var dialogResult = new DialogResult(ButtonResult.OK, dialogParam);
             
                RequestClose?.Invoke(dialogResult);
            });
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
            Message = parameters.GetValue<string>(nameof(Message));
        }
    }
}
