using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Command
{
    class Archivator:IExecutor
    {
        public void Execute()
        {
            Console.WriteLine("Archivated");
        }
        public override string ToString()
        {
            return "Archivated";
        }
    }
}
