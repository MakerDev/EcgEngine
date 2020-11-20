using EcgEngine.Models.VisualScript;
using EcgEngine.Module.PropertyEditor.ViewModels;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace EcgEngine.Module.PropertyEditor.Views
{
    /// <summary>
    /// Interaction logic for TriggerEditorWindow
    /// </summary>
    public partial class TriggerEditorWindow : UserControl
    {
        private readonly TriggerEditorWindowViewModel _viewModel = null;

        public TriggerEditorWindow()
        {
            InitializeComponent();

            _viewModel = DataContext as TriggerEditorWindowViewModel;
        }

        private void TextBox_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            e.Handled = true;

            Key key = e.SystemKey;

            if (key == Key.None)
            {
                key = e.ImeProcessedKey == Key.None ? e.Key : e.ImeProcessedKey;
            }

            var result = Enum.TryParse(typeof(CocosKeyCode), $"KEY_{key.ToString().ToUpper()}", out object cocosKeyCodeParseResult);

            if (result)
            {
                _viewModel.OnKeyPressed((CocosKeyCode)cocosKeyCodeParseResult);
            }
            else
            {
                MessageBox.Show("This key is not supported");
            }
        }
    }
}
