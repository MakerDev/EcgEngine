using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class JumpBy: Action
    {
        public int Height { get; private set; }
        public float Duration { get; private set; }

        public JumpBy(float duration, int height)
        {
            Name = nameof(JumpBy);

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(Duration),
                Type = "float",
                Value = duration.ToString(),
            });

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(Height),
                Type = "int",
                Value = height.ToString(),
            });

            Duration = duration;
            Height = height;
        }
    }
}
