using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
     class Housekeeper:AbstractWorker
    {
          public Housekeeper(Manager manager):base(manager)
        {
            manager.Housekeeper = this;
        }

        public void Clean()
        {
            Console.WriteLine("Cleaning the house");
            this.NotifyManager();
        }
        public override void NotifyManager()
        {
            Console.WriteLine("-"+this.manager.name + ", I`m done");
        }
    }
}
