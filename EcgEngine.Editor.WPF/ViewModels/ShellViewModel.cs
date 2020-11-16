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
        private readonly GameManager _gameManager;
        private readonly IDialogService _dialogService;
        private readonly IEventAggregator _eventAggregator;

        public DelegateCommand PlayCommand
        {
            get { return _playCommand; }
            set { SetProperty(ref _playCommand, value); }
        }

        public bool SaveFileLoaded { get; set; } = false;


        public DelegateCommand SelectSavefilePathCommand { get; set; }
        public DelegateCommand SaveCommand { get; set; }
        public DelegateCommand LoadCommand { get; set; }

        public ShellViewModel(GameManager gameManager, IDialogService dialogService, IEventAggregator eventAggregator)
        {
            PlayCommand = new DelegateCommand(OpenPlaywindow);
            SelectSavefilePathCommand = new DelegateCommand(SelectSavefilePath);
            SaveCommand = new DelegateCommand(SaveData);
            LoadCommand = new DelegateCommand(LoadData);

            _gameManager = gameManager;
            _dialogService = dialogService;
            _eventAggregator = eventAggregator;
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
