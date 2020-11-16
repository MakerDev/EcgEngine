using EcgEngine.Editor.WPF.ViewModels;
using System.Windows.Controls;

namespace EcgEngine.Editor.WPF.Views
{
    /// <summary>
    /// Interaction logic for GameObjectListView
    /// </summary>
    public partial class GameObjectListView : UserControl
    {
        public GameObjectListView()
        {
            InitializeComponent();

            var viewModel = this.DataContext as GameObjectListViewModel;
            viewModel.RefreshList = () =>
            {
                _gameObjectListBox.Items.Refresh();
            };
        }
    }
}
