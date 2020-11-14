using EcgEngine.Services;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;

namespace EcgEngine.Editor.WPF.ViewModels
{
    public class ShellViewModel : BindableBase
    {
        private DelegateCommand _playCommand;
        private readonly GameManager _gameManager;
        private readonly IDialogService _dialogService;

        public DelegateCommand PlayCommand
        {
            get { return _playCommand; }
            set { SetProperty(ref _playCommand, value); }
        }

        public bool SaveFileLoaded { get; set; } = false;


        public DelegateCommand SelectSavefilePathCommand { get; set; }

        public ShellViewModel(GameManager gameManager, IDialogService dialogService)
        {
            PlayCommand = new DelegateCommand(OpenPlaywindow);
            SelectSavefilePathCommand = new DelegateCommand(SelectSavefilePath);
            _gameManager = gameManager;
            _dialogService = dialogService;
        }

        private void SelectSavefilePath()
        {
        }

        private void OpenPlaywindow()
        {
            _dialogService.Show("SceneEditorWindow", null, (result) => { });
        }
    }
}
