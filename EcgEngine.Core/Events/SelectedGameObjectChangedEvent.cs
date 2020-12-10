using EcgEngine.Models;
using Prism.Events;

namespace EcgEngine.Core.Events
{
    public class SelectedGameObjectChangedEvent : PubSubEvent<GameObject>
    {
        public GameObject GameObject { get; set; } = null;
    }
}
