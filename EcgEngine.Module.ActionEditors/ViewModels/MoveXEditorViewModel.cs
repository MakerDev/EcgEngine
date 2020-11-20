using EcgEngine.Core.Interfaces;
using EcgEngine.Models.VisualScript;
using EcgEngine.Models.VisualScript.ActionPresets;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;

namespace EcgEngine.Module.ActionEditors.ViewModels
{
    public class MoveXEditorViewModel : BindableBase, IActionEditorViewModel
    {
        private bool _isDirectionLeft = false;
        public bool IsDirectionLeft
        {
            get { return _isDirectionLeft; }
            set
            {
                SetProperty(ref _isDirectionLeft, value);
                RaisePropertyChanged(nameof(IsDirectionRight));
            }
        }

        public bool IsDirectionRight
        {
            get { return !IsDirectionLeft; }
            set
            {
                //Just for binding
                if (value)
                {
                    IsDirectionLeft = false;
                }
            }
        }

        private int _speed = 2;
        public int Speed
        {
            get { return _speed; }
            set { SetProperty(ref _speed, value); }
        }

        public Models.VisualScript.Action GetAction()
        {
            var direction = IsDirectionLeft ? "Left" : "Right";
            Models.VisualScript.Action action = new MoveX(direction, Speed);

            return action;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            if (navigationContext.Parameters["OriginalAction"] == null)
            {
                return;
            }

            var action = navigationContext.Parameters["OriginalAction"] as Models.VisualScript.Action;
            Speed = int.Parse(action.Arguments.FirstOrDefault(x => x.Name == "Speed").Value);
            IsDirectionLeft = action.Arguments.FirstOrDefault(x => x.Name == "Direction").Value == "Left";
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
