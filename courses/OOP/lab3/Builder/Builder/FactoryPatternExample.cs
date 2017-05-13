using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Builder
{
    interface IProduct { 
        string ShipFrom(); 
    }
    class ProductA : IProduct { 
        public String ShipFrom() { 
            return " from Ukraine"; 
        } 
    }
    class ProductB : IProduct { 
        public String ShipFrom() {
            return "from Turkey"; 
        } 
    }
    class DefaultProduct : IProduct { 
        public String ShipFrom() { 
            return "not available"; 
        } 
    }
    class Creator { 
        public IProduct FactoryMethod(int month) 
        { if (month >= 4 && month <= 11) 
            return new ProductA(); 
        else if (month == 1 || month == 2 || month == 12) 
            return new ProductB(); 
        else return new DefaultProduct(); } }
}
