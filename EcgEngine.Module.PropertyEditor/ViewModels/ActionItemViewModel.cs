using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;
using EcgEngine.Models.VisualScript;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionItemViewModel : BindableBase
    {
        private Models.VisualScript.Action _action;

        public Models.VisualScript.Action Action
        {
            get { return _action; }
            set { SetProperty(ref _action, value); }
        }

        public string ActionDescription
        {
            get
            {
                return Action.ToString();
            }
        }
    }
}
