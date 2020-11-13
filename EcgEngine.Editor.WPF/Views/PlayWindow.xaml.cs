using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using EcgRuntime;

namespace EcgEngine.Editor.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class PlayWindow : Window
    {
        private readonly EcgRuntime.EcgRuntime _ecgRuntime = new EcgRuntime.EcgRuntime();
        private int _currentSpeed = 4;

        public PlayWindow()
        {
            InitializeComponent();

            var task = Task.Delay(100).ContinueWith((task) => Dispatcher.Invoke(StartGame));
        }

        private void StartGame()
        {
            var handle = ((HwndSource)HwndSource.FromVisual(_stackPanel)).Handle.ToInt32();
            _ecgRuntime.Initialize(handle);
        }

        private void NextScene(object sender, RoutedEventArgs e)
        {
            _ecgRuntime.SwitchScene();
        }

        private void CreateScene(object sender, RoutedEventArgs e)
        {
            _ecgRuntime.CreateNewScene(_currentSpeed);
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);
            _ecgRuntime.Destroy();
        }

        private void IncreaseSpeed(object sender, RoutedEventArgs e)
        {
            var button = sender as System.Windows.Controls.Button;
            int delta = int.Parse(button.Tag.ToString());
            _currentSpeed += delta;

            _ecgRuntime.CreateNewScene(_currentSpeed);
        }
    }
}
