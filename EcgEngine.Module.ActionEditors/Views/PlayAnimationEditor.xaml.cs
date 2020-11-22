using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using System.Windows.Controls;

namespace EcgEngine.Module.ActionEditors.Views
{
    /// <summary>
    /// Interaction logic for PlayAnimationEditor
    /// </summary>    
    public partial class PlayAnimationEditor : UserControl, IActionEditorView
    {
        public PlayAnimationEditor()
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
