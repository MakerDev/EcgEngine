using EcgEngine.Core;
using EcgEngine.Core.Events;
using Prism.Events;
using Prism.Regions;
using System;
using System.Windows.Controls;

namespace EcgEngine.Editor.WPF.Views
{
    /// <summary>
    /// Interaction logic for GameObjectListView
    /// </summary>
    public partial class GameObjectListView : UserControl
    {
        public GameObjectListView(IEventAggregator eventAggregator)
        {
            InitializeComponent();
            eventAggregator.GetEvent<GameObjectModifiedEvent>().Subscribe((modifiedObject) =>
            {
                _gameObjectListBox.Items.Refresh();
            });
        }
    }
}
