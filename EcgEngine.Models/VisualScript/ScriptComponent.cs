using EcgEngine.Models.VisualScript.VisualScript;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript
{
    public class ScriptComponent
    {
        public int Id { get; set; }
        public string Comment { get; set; }
        public  Dictionary<Trigger, List<Action>> TriggerActionsPair { get; set; }

    }
}
