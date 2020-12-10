using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript.ActionPresets;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class SetSpriteFrameEditorViewModel : BindableBase, IActionEditorViewModel
    {
        private string _spriteName;
        public string SpriteName
        {
            get { return _spriteName; }
            set { SetProperty(ref _spriteName, value); }
        }

        public SetSpriteFrameEditorViewModel()
        {

        }

        public Models.VisualScript.Action GetAction()
        {
            Models.VisualScript.Action action = new SetSpriteFrame(SpriteName);

            return action;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as SetSpriteFrame;

            if (action == null)
            {
                return;
            }

            SpriteName = action.SpriteName;
        }
        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
