using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.VisualScript
{
    public enum TriggetType
    {
        KeyBoard,
        Mouse,
        Interaction,
        Variable,
    }

    public class Trigger
    {
        public TriggetType Type { get; protected set; }
    }
}
