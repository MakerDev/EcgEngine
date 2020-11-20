using EcgEngine.Models.VisualScript;
using EcgEngine.Models.VisualScript.Triggers;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class TriggerItemViewModel : BindableBase
    {
        private Trigger _trigger;
        public Trigger Trigger
        {
            get { return _trigger; }
            set { SetProperty(ref _trigger, value); }
        }

        public ScriptComponent ScriptComponent { get; set; }

        public string TriggerDescription
        {
            get
            {
                return Trigger.ToString();
            }
        }

        public DelegateCommand EditTriggerPropertyCommand { get; set; }

        public TriggerItemViewModel(IDialogService dialogService)
        {
            EditTriggerPropertyCommand = new DelegateCommand(() =>
            {
                var p = new DialogParameters();
                p.Add("Trigger", Trigger);

                dialogService.ShowDialog("TriggerEditorWindow", p, (result) =>
                {
                    if (result.Result == ButtonResult.OK)
                    {
                        Trigger = result.Parameters.GetValue<Trigger>("Trigger");
                        RaisePropertyChanged(nameof(Trigger));
                        ScriptComponent.Trigger = Trigger;
                    }
                });
            });
        }
    }
}
