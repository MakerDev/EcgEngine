using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using System.Windows.Controls;

namespace EcgEngine.Module.ActionEditors.Views
{
    /// <summary>
    /// Interaction logic for SetSpriteFrameEditor
    /// </summary>
    public partial class SetSpriteFrameEditor : UserControl, IActionEditorView
    {
        public SetSpriteFrameEditor()
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
