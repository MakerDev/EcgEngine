using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class MoveX : Action
    {
        public MoveX(string direction, int speed)
        {
            Name = "MoveX";
            Arguments.Add(new ActionArgument()
            {
                Name = "Direction",
                Type = "string",
                Value = direction,
            });

            int velocity = direction == "Right" ? speed : -speed;

            Arguments.Add(new ActionArgument()
            {
                Name = "Speed",
                Type = "int",
                Value = velocity.ToString(),
            });
        }
    }
}
