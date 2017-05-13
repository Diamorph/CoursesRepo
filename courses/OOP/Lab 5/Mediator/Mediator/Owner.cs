using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
    class Owner
    {
        public string name;
        private Manager manager = null;
        public Owner(string name){
            this.name = name;
        }
        public Manager Manager
        {
            get { return this.manager; }
            set { this.manager = value; }
        }
        public void Water()
        {
            manager.Water();
        }
        public void Clean()
        {
            manager.Clean();
        }
    }
}
