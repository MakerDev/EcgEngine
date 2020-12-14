using EcgEngine.Models.VariableEngine;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class VariableListItemViewModel : BindableBase
    {
        //Injected by VariableEditorViewModel
        public DelegateCommand EditVairableCommand { get; set; }
        private EcgVariable _variable;
        public EcgVariable Variable
        {
            get { return _variable; }
            set { SetProperty(ref _variable, value); }
        }

        public VariableListItemViewModel()
        {
        }
    }
}
