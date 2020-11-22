using System;
using System.Collections.Generic;
using System.Text;

namespace EcgEngine.Models.VisualScript.ActionPresets
{
    public class SetSpriteFrame : Action
    {
        public string SpriteName { get; set; }
        public SetSpriteFrame(string spriteName)
        {
            Name = nameof(SetSpriteFrame);

            Arguments.Add(new ActionArgument
            {
                Name = "SpriteName",
                Type = "string",
                Value = spriteName,
            });

            SpriteName = spriteName;
        }
    }
}
