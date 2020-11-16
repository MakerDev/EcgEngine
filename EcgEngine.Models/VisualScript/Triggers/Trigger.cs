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
        //TODO : Create default name with trigger global id
        public string Name { get; set; } = "trigger1";
        public TriggerType Type { get; set; } = TriggerType.KeyBoard;
        //TODO: try fix this
        public KeyEventTrigger KeyEventTrigger { get; set; } = new KeyEventTrigger();

        public override string ToString()
        {
            switch (Type)
            {
                case TriggerType.KeyBoard:
                    return KeyEventTrigger.ToString();

                case TriggerType.Mouse:
                    break;
                case TriggerType.Interaction:
                    break;
                case TriggerType.Variable:
                    break;
                default:
                    break;
            }

            return Name;
        }
    }
}
