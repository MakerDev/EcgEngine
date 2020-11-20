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
    public class JumpByEditorViewModel : BindableBase, IActionEditorViewModel
    {
        private int _speed;
        public int Speed
        {
            get { return _speed; }
            set { SetProperty(ref _speed, value); }
        }

        private float _duration;
        public float Duration
        {
            get { return _duration; }
            set { SetProperty(ref _duration, value); }
        }

        public Models.VisualScript.Action GetAction()
        {
            return new JumpBy(Duration, Speed);
        }
        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as Models.VisualScript.Action;
            Speed = int.Parse(action.Arguments.FirstOrDefault(x=>x.Name == "Speed").Value);
            Duration = float.Parse(action.Arguments.FirstOrDefault(x => x.Name == "Duration").Value);
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
