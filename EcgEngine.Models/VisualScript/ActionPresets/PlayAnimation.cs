using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class PlayAnimation : Action
    {
        public string AnimationName { get; set; } = "";

        public PlayAnimation(string animationName)
        {
            Name = nameof(PlayAnimation);

            Arguments.Add(new ActionArgument()
            {
                Name = nameof(AnimationName),
                Type = "string",
                Value = animationName,
            });

            AnimationName = animationName;
        }
    }
}
