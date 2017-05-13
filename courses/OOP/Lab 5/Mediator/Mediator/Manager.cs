using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mediator
{
    class Manager
    {
        public String name;
        private Housekeeper housekeeper = null;
        private Gardener gardener = null;
        public Manager(Owner owner)
        {
            owner.Manager = this;
        }
        public Manager(String name)
        {
            this.name = name;                  
        }
        public Housekeeper Housekeeper
        {
            get { return this.housekeeper;}
            set { this.housekeeper = value; }
        }
        public Gardener Gardener
        {
            get { return this.gardener; }
            set { this.gardener = value; }
        }

        public void Water(){
            gardener.Water();
        }
        public void Clean()
        {
            housekeeper.Clean();
        }
    }
}
