using EcgEngine.Models.VisualScript;
using EcgEngine.Models.VisualScript.ActionPresets;
using Prism.Regions;

namespace EcgEngine.Module.PropertyEditor.ViewModels
{
    public class ConditionalActionItemViewModel : ActionItemViewModel
    {
        private IRegionManager _scopedRegionManager;
        public IRegionManager ScopedRegionManager
        {
            get { return _scopedRegionManager; }
            set { SetProperty(ref _scopedRegionManager, value); }
        }

        private ConditionalAction _conditionalAction;

        public ConditionalAction ConditionalAction
        {
            get { return _conditionalAction; }
            set
            {
                SetProperty(ref _conditionalAction, value);

                //HACK..!!               
                var scriptComponet = new ScriptComponent();
                var conditionalAction = ConditionalAction;
                scriptComponet.Actions = conditionalAction.NestedActions;
                ScriptComponent = scriptComponet;
            }
        }

        private bool _test;
        public bool Test
        {
            get { return _test; }
            set { SetProperty(ref _test, value); }
        }

        private ScriptComponent _scriptComponent;
        public ScriptComponent ScriptComponent
        {
            get { return _scriptComponent; }
            set { 
                SetProperty(ref _scriptComponent, value); 
            }
        }

        public ConditionalActionItemViewModel(IRegionManager regionManager)
        {
            ScopedRegionManager = regionManager.CreateRegionManager();
        }
    }
}
