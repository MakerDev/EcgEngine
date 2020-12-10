using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VariableEngine
{
    public enum EcgVariableType
    {
        TypeInteger,
        TypeFloat,
        TypeString,
    }

    public class EcgVariable
    {
        public string Name { get; set; }
        public EcgVariableType EcgVariableType { get; set; } = EcgVariableType.TypeString;
        public string Value { get; set; }
    }
}
