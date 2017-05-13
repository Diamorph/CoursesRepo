using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Command
{
    class Command
    {
        protected IExecutor executor;
        public Command()
        {

        }
        public Command(IExecutor executor)
        {
            this.executor = executor;
        }

        public void Execute(){
            if (this.executor != null)
            {
                executor.Execute();
            }
        }

        public override string ToString()
        {
            return executor.ToString();
        }
    }
}
