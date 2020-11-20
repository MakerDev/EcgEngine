using System.Windows.Input;

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
        public CocosKeyCode Key { get; set; }

        public override string ToString()
        {
            return $"KeyEventType={KeyEventType} | Key={Key}";
        }
    }
}
