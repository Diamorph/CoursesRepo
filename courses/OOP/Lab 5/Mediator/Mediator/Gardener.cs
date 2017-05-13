using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
    class Gardener : AbstractWorker
    {
        public Gardener(Manager manager):base(manager)
        {
            manager.Gardener = this;
        }

        public void Water()
        {
            Console.WriteLine("Watering the flowers");

            this.NotifyManager();
        }
        public override void NotifyManager()
        {
            Console.WriteLine("-" +this.manager.name + ", I`m done");
        }
    }
}
