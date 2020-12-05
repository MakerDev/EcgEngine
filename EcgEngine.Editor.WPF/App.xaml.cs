using EcgEngine.Core;
using EcgEngine.Editor.WPF.ViewModels;
using EcgEngine.Editor.WPF.Views;
using EcgEngine.Module.ActionEditors;
using EcgEngine.Module.PropertyEditor;
using EcgEngine.Module.SceneEditor;
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
            containerRegistry.RegisterSingleton<IApplicationCommands, ApplicationCommands>();

            containerRegistry.RegisterSingleton<IGameManager, GameManager>();
            containerRegistry.RegisterSingleton<EcgRuntime.EcgRuntime>();
            containerRegistry.RegisterSingleton<IBlobStorageFileManager, BlobStorageFileManager>();

            containerRegistry.RegisterDialog<SceneEditorWindow, SceneEditorWindowViewModel>();

            containerRegistry.Register<IAsyncJsonSavefileManager, AsyncJsonSavefileManager>();
            containerRegistry.Register<IPackageManager, PackageManager>();
        }

        protected override void ConfigureModuleCatalog(IModuleCatalog moduleCatalog)
        {
            moduleCatalog.AddModule<EcgEngineCoreModule>();
            moduleCatalog.AddModule<PropertyEditorModule>();
            moduleCatalog.AddModule<SceneEditorModule>();
            moduleCatalog.AddModule<ActionEditorsModule>();
        }
    }
}
