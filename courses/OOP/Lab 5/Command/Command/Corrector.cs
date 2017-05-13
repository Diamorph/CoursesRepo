using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Command
{
    public class Corrector:IExecutor
    {
        public void Execute()
        {
            Console.WriteLine("Corrected");
        }
        public override string ToString()
        {
            return "Corrected";
        }
    }
}
