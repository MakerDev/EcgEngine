using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VariableEngine
{
    public class VariableCondition
    {
        //Used TargetOBject 'Name' to avoid circular reference.
        public string TargetObjectName { get; set; } = "";
        public string TargetVariableName { get; set; } = "";
        public ConditionType ConditionType { get; set; } = ConditionType.EqualTo;
        public string ValueToCompare { get; set; } = "";

        public VariableCondition(string targetVairableName,
                                 string targetObjectName,
                                 ConditionType conditionType,
                                 string valueToCompare)
        {
            TargetObjectName = targetObjectName;
            TargetVariableName = targetVairableName;
            ConditionType = conditionType;
            ValueToCompare = valueToCompare;
        }

        public override string ToString()
        {
            return $"{TargetObjectName} {TargetVariableName} {ConditionType} {ValueToCompare}";
        }
    }
}
