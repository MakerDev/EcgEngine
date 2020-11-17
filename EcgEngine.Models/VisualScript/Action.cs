using EcgEngine.Models.VisualScript.Triggers;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript
{
    public class Action
    {
        public string Name { get; set; }
        public List<ActionArgument> Arguments { get; set; } = new List<ActionArgument>();

        public override string ToString()
        {
            var result = $"{Name} + ";

            foreach (var arg in Arguments)
            {
                result += arg.ToString();
            }

            return result;
        }
    }
}
