using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Builder
{
    class Program
    {
        static void Main(string[] args)
        {
            //Task1
            Creator c = new Creator(); 
            IProduct product;
            for (int i = 1; i <= 12; i++) { 
                product = c.FactoryMethod(i); 
                Console.WriteLine("Products " + product.ShipFrom()); 
            } 
            Console.ReadKey();

            //Task2
            Restaurant McDonalds = RestСonsultant.GetMenu("MC");
            Restaurant Shvidko = RestСonsultant.GetMenu("Sh");
            Restaurant PuzataHata = RestСonsultant.GetMenu("Pu");
            Console.WriteLine("McDonald's:");
            Console.WriteLine(McDonalds.Info());
            Console.WriteLine("Швидко:");
            Console.WriteLine(Shvidko.Info());
            Console.WriteLine("Пузата хата:");
            Console.WriteLine(PuzataHata.Info());
            Console.ReadKey();

        }
    }
    public abstract class Dish
    {
        private int price;
        private string name;
        public Dish(string name, int price)
        {
            this.name = name;
            this.price = price;
        }
        public string Info()
        {
            return name + "\t" + price.ToString();
        }
    }

    public class Meat : Dish
    {
        public Meat(string name, int price) : base(name, price) { }
    }

    public class Garnish : Dish
    {
        public Garnish(string name, int price) : base(name, price) { }
    }
    public class Dessert : Dish
    {
        public Dessert(string name, int price) : base(name, price) { }
    }
    public class Drink : Dish
    {
        public Drink(string name, int price) : base(name, price) { }
    }

    public class Restaurant
    {
        public Meat meat;
        public Garnish garnish;
        public Drink drink;
        public Dessert dessert;

        public string Info()
        {
            return meat.Info() + "\n" + garnish.Info() + "\n" + drink.Info() + "\n" + dessert.Info() + "\n";
        }

    }
    public abstract class RestaurantBuilder
    {
        protected Restaurant rest = null;
        public void PrepareToBuild()
        {
            rest = new Restaurant();
        }
        public abstract void SetMeat();
        public abstract void SetGarnish();
        public abstract void SetDrink();
        public abstract void SetDessert();
        public Restaurant GetRest()
        {
            return rest;
        }

    }

    public class McDonaldsBuilder : RestaurantBuilder
    {
        private static McDonaldsBuilder _instance;
        public static McDonaldsBuilder instance
        {
            get
            {
                if (_instance == null)
                    _instance = new McDonaldsBuilder();
                return _instance;
            }
        }
        public override void SetMeat()
        {
            rest.meat = new Meat("Бургер", 30);
        }
        public override void SetGarnish()
        {
            rest.garnish = new Garnish("Фри", 30);
        }
        public override void SetDrink()
        {
            rest.drink = new Drink("Кола", 20);
        }
        public override void SetDessert()
        {
            rest.dessert = new Dessert("Пирожок", 10);
        }

    }

    public class ShvidkoBuilder : RestaurantBuilder
    {
        private static ShvidkoBuilder _instance;
        public static ShvidkoBuilder instance
        {
            get
            {
                if (_instance == null)
                    _instance = new ShvidkoBuilder();
                return _instance;
            }
        }
        public override void SetMeat()
        {
            rest.meat = new Meat("Котлета", 25);
        }
        public override void SetGarnish()
        {
            rest.garnish = new Garnish("Гречка", 15);
        }
        public override void SetDrink()
        {
            rest.drink = new Drink("Чай", 10);
        }
        public override void SetDessert()
        {
            rest.dessert = new Dessert("Пирог", 15);
        }

    }

    public class PuzataHataBuilder : RestaurantBuilder
    {
        private static PuzataHataBuilder _instance;
        public static PuzataHataBuilder instance
        {
            get
            {
                if (_instance == null)
                    _instance = new PuzataHataBuilder();
                return _instance;
            }
        }
        public override void SetMeat()
        {
            rest.meat = new Meat("Отбивна", 30);
        }
        public override void SetGarnish()
        {
            rest.garnish = new Garnish("Рис", 15);
        }
        public override void SetDrink()
        {
            rest.drink = new Drink("Кофе", 20);
        }
        public override void SetDessert()
        {
            rest.dessert = new Dessert("Торт", 15);
        }

    }

    public class RestСonsultant
    {
        public static Restaurant GetMenu(string name)
        {
            RestaurantBuilder builder = null;
            if (name == "MC")
                builder = McDonaldsBuilder.instance;
            else if (name == "Sh")
                builder = ShvidkoBuilder.instance;
            else if (name == "Pu")
                builder = PuzataHataBuilder.instance;
            else return null;
            builder.PrepareToBuild();
            builder.SetMeat();
            builder.SetGarnish();
            builder.SetDrink();
            builder.SetDessert();
            return builder.GetRest();
        }
    }
}
