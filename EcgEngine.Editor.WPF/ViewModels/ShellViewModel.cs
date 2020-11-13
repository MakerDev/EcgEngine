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
        public DelegateCommand PlayCommand
        {
            get { return _playCommand; }
            set { SetProperty(ref _playCommand, value); }
        }

        public bool SaveFileLoaded { get; set; } = false;


        public ShellViewModel()
        {
            PlayCommand = new DelegateCommand(OpenPlaywindow);
        }

        private void OpenPlaywindow()
        {
            var mainWindow = new PlayWindow();
            mainWindow.ShowDialog();
        }
    }
}
