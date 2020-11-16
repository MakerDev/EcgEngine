using System.Windows.Forms;

namespace EcgEngine.Models.VisualScript.Triggers
{
    public enum KeyEventType
    {
        Down,
        Press,
        Up,
    }

    public class KeyEventTrigger : Trigger
    {        
        public KeyEventType KeyEventType { get; set; } = KeyEventType.Down;
        public Keys Key { get; set; }

        public KeyEventTrigger()
        {
            Type = TriggerType.KeyBoard;
        }
    }
}
