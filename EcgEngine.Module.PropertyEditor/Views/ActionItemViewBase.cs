using EcgEngine.Module.PropertyEditor.ViewModels;
using Prism.Commands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace EcgEngine.Module.PropertyEditor.Views
{
    public class ActionItemViewBase: UserControl
    {
        public DelegateCommand EditCommand
        {
            get { return (DelegateCommand)GetValue(EditCommandProperty); }
            set { SetValue(EditCommandProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MyProperty.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty EditCommandProperty =
            DependencyProperty.Register("EditCommand", typeof(DelegateCommand), typeof(ActionItemViewBase), new PropertyMetadata(OnCommandSet));

        private static void OnCommandSet(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (e.NewValue == null)
            {
                return;
            }

            var vm = d.GetValue(DataContextProperty) as ActionItemViewModel;
            vm.EditActionCommand = e.NewValue as DelegateCommand;
        }
    }
}
