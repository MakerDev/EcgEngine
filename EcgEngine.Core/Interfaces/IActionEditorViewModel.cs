using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Core.Interfaces
{
    public interface IActionEditorViewModel : INavigationAware
    {
        public Models.VisualScript.Action GetAction();
    }
}
