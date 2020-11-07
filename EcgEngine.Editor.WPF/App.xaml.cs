using EcgEngine.Editor.WPF.Views;
using Prism.Ioc;
using Prism.Unity;
using System.Windows;
using Unity;

namespace EcgEngine.Editor.WPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : PrismApplication
    {
        protected override Window CreateShell()
        {
            return Container.Resolve<ShellView>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {

        }
    }
}
