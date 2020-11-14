using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Editor.WPF.ViewModels
{
    public class SceneEditorWindowViewModel : BindableBase, IDialogAware
    {
        private readonly EcgRuntime.EcgRuntime _ecgRuntime;

        public string Title => "Scene editor";

        public event Action<IDialogResult> RequestClose;

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
            
        }

        public SceneEditorWindowViewModel(EcgRuntime.EcgRuntime ecgRuntime)
        {
            _ecgRuntime = ecgRuntime;
        }
    }
}
