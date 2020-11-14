using EcgEngine.Core;
using EcgEngine.Services;
using Prism.Regions;
using System.Windows;

namespace EcgEngine.Editor.WPF.Views
{
    /// <summary>
    /// Interaction logic for ShellView.xaml
    /// </summary>
    public partial class ShellView : Window
    {
        public ShellView(IRegionManager regionManager)
        {
            InitializeComponent();

            regionManager.RegisterViewWithRegion(RegionNames.GAMEOBJECT_LIST_REGION, typeof(GameObjectListView));
        }
    }
}
