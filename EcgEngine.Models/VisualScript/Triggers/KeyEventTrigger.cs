using System.Windows.Forms;

namespace EcgEngine.Models.VisualScript.Triggers
{
    public enum KeyEventType
    {
        Down,
        Press,
        Up,
    }

    public class KeyEventTrigger
    {
        public KeyEventType KeyEventType { get; set; } = KeyEventType.Down;
        public Keys Key { get; set; }

        public override string ToString()
        {
            return $"KeyEventType={KeyEventType} | Key={Key}";
        }
    }
}
