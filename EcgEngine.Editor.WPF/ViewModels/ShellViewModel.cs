using EcgEngine.Services;
using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;

namespace EcgEngine.Editor.WPF.ViewModels
{
    public class ShellViewModel : BindableBase
    {
        private DelegateCommand _playCommand;
        private readonly GameManager _gameManager;

        public DelegateCommand PlayCommand
        {
            get { return _playCommand; }
            set { SetProperty(ref _playCommand, value); }
        }

        public bool SaveFileLoaded { get; set; } = false;


        public DelegateCommand SelectSavefilePathCommand { get; set; }

        public ShellViewModel(GameManager gameManager)
        {
            PlayCommand = new DelegateCommand(OpenPlaywindow);
            SelectSavefilePathCommand = new DelegateCommand(SelectSavefilePath);
            _gameManager = gameManager;
        }

        private void SelectSavefilePath()
        {
        }

        private void OpenPlaywindow()
        {
            var mainWindow = new PlayWindow();
            mainWindow.ShowDialog();
        }
    }
}
