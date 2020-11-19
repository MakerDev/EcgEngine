using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionSelectorDialogViewModel : BindableBase, IDialogAware
    {
        public string Title => "Action Selector";

        public event Action<IDialogResult> RequestClose;

        private bool _isDirectionLeft = false;
        public bool IsDirectionLeft
        {
            get { return _isDirectionLeft; }
            set { SetProperty(ref _isDirectionLeft, value); }
        }

        private int _speed = 2;
        public int Speed
        {
            get { return _speed; }
            set { SetProperty(ref _speed, value); }
        }

        public DelegateCommand CloseDialogCommand { get; set; }


        public ActionSelectorDialogViewModel()
        {
            CloseDialogCommand = new DelegateCommand(CloseDialog);
        }

        private void CloseDialog()
        {
            var p = new DialogParameters();
            var direction = IsDirectionLeft ? "Left" : "Right";
            Models.VisualScript.Action action = new Models.VisualScript.ActionPresets.MoveX(direction, Speed);
            p.Add("Action", action);

            RequestClose?.Invoke(new DialogResult(ButtonResult.OK, p));
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

        }
    }
}
