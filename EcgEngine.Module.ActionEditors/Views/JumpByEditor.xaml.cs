using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using System.Windows.Controls;

namespace EcgEngine.Module.ActionEditors.Views
{
    /// <summary>
    /// Interaction logic for JumpByEditor
    /// </summary>
    public partial class JumpByEditor : ActionEditorViewBase
    {
        public JumpByEditor()
        {
            InitializeComponent();
        }

        //TODO : Probabily better to extract this to seperate class or use attribute or default interface to reduce code duplication
        //TODO : Create ActionEditorViewBase, ActionEditorViewModelBase
        
    }
}
