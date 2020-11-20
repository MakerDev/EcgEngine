using EcgEngine.Models.VisualScript;
using EcgEngine.Models.VisualScript.Triggers;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Windows.Input;

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

        private CocosKeyCode _keyCode = CocosKeyCode.KEY_NONE;
        public CocosKeyCode KeyCode
        {
            get
            {
                return _keyCode;
            }
            set
            {
                SetProperty(ref _keyCode, value);
                Trigger.KeyEventTrigger.Key = value;
            }
        }

        private KeyEventType _keyEventType = KeyEventType.Down;
        public KeyEventType KeyEventType
        {
            get { return _keyEventType; }
            set
            {
                SetProperty(ref _keyEventType, value);
                Trigger.KeyEventTrigger.KeyEventType = value;
            }
        }

        public void OnKeyPressed(CocosKeyCode key)
        {
            KeyCode = key;
        }

        private void CloseDialog()
        {
            var parameters = new DialogParameters();
            parameters.Add("Trigger", Trigger);

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
            KeyCode = Trigger.KeyEventTrigger.Key;
            KeyEventType = Trigger.KeyEventTrigger.KeyEventType;
        }
    }
}
