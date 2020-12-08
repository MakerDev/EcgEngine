using EcgEngine.Core.Dialogs;
using EcgEngine.Core.Events;
using EcgEngine.Services;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.IO;

namespace EcgEngine.Editor.WPF.ViewModels
{
    public class ShellViewModel : BindableBase
    {
        private DelegateCommand _playCommand;
        private readonly IGameManager _gameManager;
        private readonly IDialogService _dialogService;
        private readonly IEventAggregator _eventAggregator;
        private readonly IPackageManager _packageManager;

        public DelegateCommand PlayCommand
        {
            get { return _playCommand; }
            set { SetProperty(ref _playCommand, value); }
        }

        public bool SaveFileLoaded { get; set; } = false;


        public DelegateCommand SelectSavefilePathCommand { get; set; }
        public DelegateCommand SaveCommand { get; set; }
        public DelegateCommand LoadCommand { get; set; }
        public DelegateCommand PublishCommand { get; set; }
        public ShellViewModel(IGameManager gameManager,
                              IDialogService dialogService,
                              IEventAggregator eventAggregator,
                              IPackageManager packageManager)
        {
            PlayCommand = new DelegateCommand(OpenPlaywindow);
            SelectSavefilePathCommand = new DelegateCommand(SelectSavefilePath);
            SaveCommand = new DelegateCommand(SaveData);
            LoadCommand = new DelegateCommand(LoadData);
            PublishCommand = new DelegateCommand(PublishPackage);


            _gameManager = gameManager;
            _dialogService = dialogService;
            _eventAggregator = eventAggregator;
            _packageManager = packageManager;
        }

        private void PublishPackage()
        {
            var gameData = _gameManager.GameData;

            var dialogParameters = new DialogParameters();
            dialogParameters.Add("Message", "Enter your packagename");

            _dialogService.ShowDialog(DialogNames.TEXT_INPUT_DIALOG, dialogParameters, async (dialogResult) =>
            {
                string userInput = dialogResult.Parameters.GetValue<string>("UserInput");

                if (string.IsNullOrEmpty(userInput))
                {
                    return;
                }

                gameData.PackageName = userInput;
                _packageManager.CreatePackage(gameData.PackageName, gameData.SavefilePath);

                var result = await _packageManager.UploadPackageAsync(gameData.PackageName, gameData.SavefilePath);

                var dialogParam = new DialogParameters();

                if (result.IsSuccess)
                {
                    dialogParam.Add("Message", "Succesfully uploaded!");
                    _dialogService.ShowDialog(DialogNames.MESSAGE_DIALOG, dialogParam, null);

                    return;
                }

                dialogParam.Add("Message", result.ErrorMessage);
                _dialogService.ShowDialog(DialogNames.MESSAGE_DIALOG, dialogParam, null);
            });
        }

        private async void LoadData()
        {
            string tempPath = Path.Combine(_gameManager.GameData.SavefilePath, _gameManager.GameData.SavefileName);
            await _gameManager.LoadSaveFile(tempPath);

            _eventAggregator.GetEvent<SavefileLoadedEvent>().Publish();
        }

        private async void SaveData()
        {
            await _gameManager.SaveAsync();
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
