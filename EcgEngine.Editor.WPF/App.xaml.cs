using EcgEngine.Editor.WPF.Views;
using EcgEngine.Module.PropertyEditor;
using EcgEngine.Services;
using Prism.Ioc;
using Prism.Modularity;
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
            containerRegistry.Register<IAsyncJsonSavefileManager, AsyncJsonSavefileManager>();
            containerRegistry.RegisterSingleton<GameManager>();            
        }

        protected override void ConfigureModuleCatalog(IModuleCatalog moduleCatalog)
        {
            moduleCatalog.AddModule<PropertyEditorModule>();
        }
    }
}
