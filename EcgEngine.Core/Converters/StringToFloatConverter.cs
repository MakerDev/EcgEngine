using System;
using System.Globalization;
using System.Windows.Data;

namespace EcgEngine.Core.Converters
{
    public class StringToFloatConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value.ToString();
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string valueString = value.ToString();

            return float.Parse(valueString);
        }
    }
}
