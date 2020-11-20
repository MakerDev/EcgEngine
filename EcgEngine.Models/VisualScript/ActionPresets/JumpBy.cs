using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class JumpBy: Action
    {
        public int Speed { get; private set; }
        public float Duration { get; private set; }


        public JumpBy(float duration, int speed)
        {
            Name = nameof(JumpBy);
            Arguments.Add(new ActionArgument()
            {
                Name = "Duration",
                Type = "float",
                Value = duration.ToString(),
            });

            Arguments.Add(new ActionArgument()
            {
                Name = "Speed",
                Type = "int",
                Value = speed.ToString(),
            });

            Duration = duration;
            Speed = speed;
        }
    }
}
