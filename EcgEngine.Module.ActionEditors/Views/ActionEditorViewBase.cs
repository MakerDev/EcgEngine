using EcgEngine.Core.Interfaces;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;

namespace EcgEngine.Module.ActionEditors.Views
{
    public class ActionEditorViewBase : UserControl, IActionEditorView
    {
        public Models.VisualScript.Action GetAction()
        {
            var vm = DataContext as IActionEditorViewModel;

            return vm.GetAction();
        }
    }
}
