using EcgEngine.Models;
using Prism.Events;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Core.Events
{
    public class GameObjectModifiedEvent : PubSubEvent<GameObject>
    {
        public GameObject GameObject { get; set; }
    }
}
