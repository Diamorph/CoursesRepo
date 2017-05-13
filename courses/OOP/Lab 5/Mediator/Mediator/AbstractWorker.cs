using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
   abstract class AbstractWorker
    {
      protected  Manager manager;
       public AbstractWorker(Manager manager)
       {
           this.manager = manager;
       }

      public abstract void NotifyManager();

    }

}
