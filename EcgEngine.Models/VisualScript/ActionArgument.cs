using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript
{
    public class ActionArgument
    {
        public string Name { get; set; } = "";
        public string Type { get; set; } = "int";
        public string Value { get; set; } = "0";

        public override string ToString()
        {
            return $"{Name} {Type} {Value}";
        }
    }
}
