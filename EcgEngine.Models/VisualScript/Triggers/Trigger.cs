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
        static public int TriggerCount { get; private set; } = 0;
        public string Name { get; set; } = "";
        public TriggerType Type { get; set; } = TriggerType.KeyBoard;
        //TODO: try fix this
        public KeyEventTrigger KeyEventTrigger { get; set; } = new KeyEventTrigger();

        public Trigger()
        {
            TriggerCount++;
            Name = $"trigger{TriggerCount}";
        }

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
