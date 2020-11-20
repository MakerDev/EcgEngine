using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using System.Windows.Controls;

namespace EcgEngine.Module.ActionEditors.Views
{
    /// <summary>
    /// Interaction logic for MoveXEditor
    /// </summary>
    public partial class MoveXEditor : UserControl, IActionEditorView
    {
        public MoveXEditor()
        {
            InitializeComponent();
        }

        public Action GetAction()
        {
            var viewModel = DataContext as IActionEditorViewModel;

            return viewModel.GetAction();
        }
    }
}
