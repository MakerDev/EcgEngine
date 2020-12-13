using EcgEngine.Models.VariableEngine;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class VariableEditorDialogViewModel : BindableBase, IDialogAware
    {
        public string Title => "VariableEditor";

        public event Action<IDialogResult> RequestClose;

        public DelegateCommand CloseCommand { get; set; }

        private EcgVariable _variable;
        public EcgVariable Variable
        {
            get { return _variable; }
            set { SetProperty(ref _variable, value); }
        }

        public VariableEditorDialogViewModel()
        {
            CloseCommand = new DelegateCommand(CloseAndSave);
        }

        private void CloseAndSave()
        {
            var p = new DialogParameters();
            p.Add(nameof(EcgVariable), Variable);

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
            if (parameters is null)
            {
                Variable = new EcgVariable();
                return;
            }

            Variable = parameters.GetValue<EcgVariable>(nameof(EcgVariable));
        }
    }
}
