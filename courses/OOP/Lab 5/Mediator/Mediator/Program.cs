using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
    class Program
    {
        static void Main(string[] args)
        {
            /*Manager John = new Manager("John");
            Gardener gardener = new Gardener(John);
            Housekeeper housekeeper = new Housekeeper(John);
            John.Water();
            John.Clean();
            */
            Owner Vlad = new Owner("Vlad");
            Manager Anton = new Manager(Vlad);
            Gardener gardener = new Gardener(Anton);
            Housekeeper housekeeper = new Housekeeper(Anton);
            Vlad.Water();
            Vlad.Clean();
            Console.ReadKey();
        }
    }
}
