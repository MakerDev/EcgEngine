using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;

namespace EcgEngine.Editor.WPF.Views
{
    /// <summary>
    /// Interaction logic for SceneEditorWindow.xaml
    /// </summary>
    public partial class SceneEditorWindow : UserControl
    {
        private readonly EcgRuntime.EcgRuntime _ecgRuntime;

        public SceneEditorWindow(EcgRuntime.EcgRuntime ecgRuntime)
        {
            InitializeComponent();

            _ecgRuntime = ecgRuntime;
            var task = Task.Delay(100).ContinueWith((task) => Dispatcher.Invoke(InitializeEngine));
        }

        //HACK : Do initialization here for hwnd
        private void InitializeEngine()
        {
            var handle = ((HwndSource)HwndSource.FromVisual(_stackPanel)).Handle.ToInt32();
            _ecgRuntime.Initialize(handle);
        }
    }
}
