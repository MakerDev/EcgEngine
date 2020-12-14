using EcgEngine.Models.VariableEngine;
using EcgEngine.Models.VisualScript;
using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class ConditionalAction : Action
    {
        public VariableCondition VariableCondition { get; set; }
        public int NestedActionsCount
        {
            get
            {
                return NestedActions.Count;
            }
        }

        public List<Action> NestedActions { get; set; } = new List<Action>();

        public ConditionalAction(VariableCondition variableCondition)
        {
            VariableCondition = variableCondition;

            Name = nameof(ConditionalAction);
        }

        public override string ToString()
        {
            return $"{Name} | {VariableCondition}";
        }
    }
}
