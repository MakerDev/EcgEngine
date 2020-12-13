using EcgEngine.Models.VariableEngine;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class SetVariableValue : Action
    {
        public string VariableName { get; set; }
        public string TargetObjectName { get; set; } = "";
        public string NewValue { get; set; }

        public EcgVariable Variable { get; set; } = null;

        [JsonConstructor]
        public SetVariableValue()
        {

        }

        public SetVariableValue(EcgVariable ecgVariable, string newValue)
        {
            Name = nameof(SetVariableValue);
            Variable = ecgVariable;
            TargetObjectName = Variable.ParentName;
            VariableName = ecgVariable.Name;
            NewValue = newValue;

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(VariableName),
                Type = "string",
                Value = VariableName,
            });

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(TargetObjectName),
                Type = "string",
                Value = TargetObjectName,
            });

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(NewValue),
                Type = "string",
                Value = NewValue,
            });

        }
    }
}
