using EcgEngine.Core;
using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Linq;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ActionSelectorDialogViewModel : BindableBase, IDialogAware
    {
        public string Title => "Action Selector";

        public event Action<IDialogResult> RequestClose;


        private IRegionManager _scopedRegionManager;
        public IRegionManager ScopedRegionManager
        {
            get { return _scopedRegionManager; }
            set { SetProperty(ref _scopedRegionManager, value); }
        }

        public Models.VisualScript.Action OriginalAction { get; set; } = null;

        public DelegateCommand CloseDialogCommand { get; set; }
        public DelegateCommand<string> OnActionToEditSelectedCommand { get; set; }

        public IActionEditorView ActionEditorView { get; set; } = null;


        public ActionSelectorDialogViewModel(IRegionManager regionManager)
        {
            ScopedRegionManager = regionManager.CreateRegionManager();

            CloseDialogCommand = new DelegateCommand(CloseDialog);
            OnActionToEditSelectedCommand = new DelegateCommand<string>(OpenActionEditor);
        }

        private void CloseDialog()
        {
            if (ActionEditorView == null)
            {
                RequestClose?.Invoke(new DialogResult(ButtonResult.Cancel));
                return;
            }

            var p = new DialogParameters();
            p.Add("Action", ActionEditorView.GetAction());

            RequestClose?.Invoke(new DialogResult(ButtonResult.OK, p));
        }

        public void OpenActionEditor(string editorName)
        {
            var parameters = new NavigationParameters();
            parameters.Add("OriginalAction", OriginalAction);

            ScopedRegionManager.RequestNavigate(RegionNames.ACTION_SELECTOR_EDITOR_REGION, editorName, parameters);
            ActionEditorView = ScopedRegionManager.Regions[RegionNames.ACTION_SELECTOR_EDITOR_REGION]
                                                  .ActiveViews
                                                  .FirstOrDefault() as IActionEditorView;
        }

        public bool CanCloseDialog()
        {
            return true;
        }

        public void OnDialogClosed()
        {

        }

        public void OnDialogOpened(IDialogParameters parameters)
        {
            if (parameters == null)
            {
                return;
            }

            //Now it's editor mode
            OriginalAction = parameters.GetValue<Models.VisualScript.Action>("OriginalAction");
            OpenActionEditor($"{OriginalAction.Name}Editor");
        }
    }
}
