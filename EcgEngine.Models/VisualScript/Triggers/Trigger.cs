using EcgEngine.Models.VisualScript.Triggers;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EcgEngine.Models.VisualScript.Triggers
{
    public enum TriggerType
    {
        KeyBoard,
        Mouse,
        Interaction,
        Variable,
    }

    public class Trigger
    {
        public string Name { get; set; } = "";        
        public TriggerType Type { get; protected set; }        

        public KeyEventTrigger KeyEventTrigger { get; set; }
    }
}
