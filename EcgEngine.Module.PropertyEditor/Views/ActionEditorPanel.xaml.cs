using EcgEngine.Models.VisualScript;
using EcgEngine.Module.PropertyEditor.ViewModels;
using System;
using System.Windows;
using System.Windows.Controls;

namespace EcgEngine.Module.PropertyEditor.Views
{
    /// <summary>
    /// Interaction logic for ActionEditorPanel
    /// </summary>
    public partial class ActionEditorPanel : UserControl
    {
        public static readonly DependencyProperty ScriptComponentProperty = DependencyProperty.Register(
            "ScriptComponent", typeof(ScriptComponent), typeof(ActionEditorPanel), new PropertyMetadata(null, OnScriptComponentChanged));

        public ScriptComponent ScriptComponent
        {
            get { 
                return (ScriptComponent)GetValue(ScriptComponentProperty); 
            }
            set { 
                SetValue(ScriptComponentProperty, value); 
            }
        }

        private static void OnScriptComponentChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var dataContext = d.GetValue(DataContextProperty) as ActionEditorPanelViewModel;
            dataContext.ScriptComponent = e.NewValue as ScriptComponent;
        }

        public ActionEditorPanel()
        {
            InitializeComponent();
        }
    }
}
