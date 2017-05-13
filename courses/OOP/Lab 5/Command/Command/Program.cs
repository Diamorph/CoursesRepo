using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Command
{
    class Program
    {
        static void Main(string[] args)
        {
            Scenario sc1 = new Scenario(new Command(new Archivator()), new Command(new Corrector()));
            sc1.Run();
            sc1.Save();
            Console.ReadKey();
        }
    }
}
