using EcgEngine.Models.VariableEngine;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class IncreaseVariableValue : Action
    {
        public string VariableName { get; set; }
        public float IncreaseBy { get; set; }
        public string TargetObjectName { get; set; } = "";

        [JsonIgnore]
        public EcgVariable Variable { get; set; } = null;

        [JsonConstructor]
        public IncreaseVariableValue()
        {

        }

        public IncreaseVariableValue(EcgVariable ecgVariable, float increaseBy)
        {
            Name = nameof(IncreaseVariableValue);
            VariableName = ecgVariable.Name;
            TargetObjectName = ecgVariable.ParentName;
            IncreaseBy = increaseBy;
            Variable = ecgVariable;

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
                Name = nameof(IncreaseBy),
                Type = "string",
                Value = IncreaseBy.ToString(),
            });
        }
    }
}
