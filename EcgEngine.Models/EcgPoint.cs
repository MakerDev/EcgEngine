using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace EcgEngine.Models
{
    /// <summary>
    /// This class is adapted because newtonsoft.json doesn't convert Point struct to desired Object form.
    /// It rather seems to call 'ToString' when converting sturct.
    /// </summary>
    public class EcgPoint
    {
        int _x = 0;
        public int X
        {
            get { return _x; }
            set
            {
                _x = value;
            }
        }

        private int _y;

        public int Y
        {
            get { return _y; }
            set { _y = value; }
        }


        public EcgPoint()
            : this(0, 0)
        {

        }

        public EcgPoint(int x, int y)
        {
            X = x;
            Y = y;
        }

    }
}
