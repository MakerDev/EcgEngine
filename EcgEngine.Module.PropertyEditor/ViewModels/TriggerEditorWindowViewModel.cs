using EcgEngine.Models.VisualScript.Triggers;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class TriggerEditorWindowViewModel : BindableBase, IDialogAware
    {
        private Trigger _trigger;
        public Trigger Trigger
        {
            get { return _trigger; }
            set { SetProperty(ref _trigger, value); }
        }
        public string Title { get; set; } = "Trigger Name";

        public event Action<IDialogResult> RequestClose;

        private bool _isLeftKey;
        public bool IsLeftKey
        {
            get { return _isLeftKey; }
            set { SetProperty(ref _isLeftKey, value); }
        }

        public DelegateCommand CloseCommand { get; set; }

        public TriggerEditorWindowViewModel()
        {
            CloseCommand = new DelegateCommand(CloseDialog);
        }

        private void CloseDialog()
        {
            var parameters = new DialogParameters();
            var trigger = new Trigger();
            trigger.KeyEventTrigger.Key = IsLeftKey ? System.Windows.Forms.Keys.Left : System.Windows.Forms.Keys.Right;
            trigger.KeyEventTrigger.KeyEventType = KeyEventType.Down;
            parameters.Add("Trigger", trigger);

            RequestClose?.Invoke(new DialogResult(ButtonResult.OK, parameters));
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
            Trigger = parameters.GetValue<Trigger>("Trigger");
        }
    }
}
