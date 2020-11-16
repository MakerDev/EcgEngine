using EcgEngine.Models.VisualScript.Triggers;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript
{
    public class ScriptComponent
    {
        public int Id { get; set; }
        public string Comment { get; set; }
        public Trigger Trigger { get; set; } = new Trigger();
        public List<Action> Action { get; set; } = new List<Action>();
    }
}
