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
    public class PlayAnimationEditorViewModel : BindableBase, IActionEditorViewModel
    {
        private string _animationName;
        public string AnimationName
        {
            get { return _animationName; }
            set { SetProperty(ref _animationName, value); }
        }

        public Models.VisualScript.Action GetAction()
        {            
            Models.VisualScript.Action action = new PlayAnimation(AnimationName);

            return action;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as Models.VisualScript.Action;

            if (action.Name != "PlayAnimation")
            {
                return;
            }

            AnimationName = action.Arguments.FirstOrDefault(x => x.Name == "AnimationName").Value;
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
