using EcgEngine.Core;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;

namespace EcgEngine.Editor.WPF.ViewModels
{
    public class SceneEditorWindowViewModel : BindableBase, IDialogAware
    {
        private readonly EcgRuntime.EcgRuntime _ecgRuntime;

        public string Title => "Scene editor";

        public event Action<IDialogResult> RequestClose;

        public DelegateCommand RunGameCommand { get; set; }
        public DelegateCommand CreateSceneCommand { get; set; }
        public DelegateCommand CreateAndRunCommand { get; set; }

        private IRegionManager _scopedRegionManager;
        public IRegionManager ScopedRegionManager
        {
            get { return _scopedRegionManager; }
            set { SetProperty(ref _scopedRegionManager, value); }
        }

        public bool CanCloseDialog()
        {
            return true;
        }

        public void OnDialogClosed()
        {
            _ecgRuntime.Destroy();
        }

        public void OnDialogOpened(IDialogParameters parameters)
        {
            ScopedRegionManager.RequestNavigate(RegionNames.SCENE_EDITOR_PANEL_REGION, "SceneEditorPanel");
        }

        public SceneEditorWindowViewModel(EcgRuntime.EcgRuntime ecgRuntime, IRegionManager regionManager)
        {
            _ecgRuntime = ecgRuntime;

            CreateSceneCommand = new DelegateCommand(() =>
            {
                _ecgRuntime.CreateNewScene("ecgsave1.json");
            });

            RunGameCommand = new DelegateCommand(() =>
            {
                _ecgRuntime.Run();
            });

            CreateAndRunCommand = new DelegateCommand(() =>
            {
                CreateSceneCommand.Execute();
                RunGameCommand.Execute();
            });

            ScopedRegionManager = regionManager.CreateRegionManager();
        }
    }
}
