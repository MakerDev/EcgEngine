using EcgEngine.Models.VisualScript.Triggers;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.Windows.Data;

namespace EcgEngine.Core.Converters
{
    public class KeyEventTypeToRadioButtonStateConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null || parameter == null)
                return null;

            KeyEventType keyEventType = (KeyEventType)value;
            int paramInt = int.Parse(parameter.ToString());
            return ((int)keyEventType == paramInt);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null || parameter == null)
                return null;

            return Enum.Parse(typeof(KeyEventType), parameter.ToString());
        }
    }
}
