using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2
{
    // Client invoking class
    public class Client
    {
        public static void Main()
        {
            //Create a McDonald's
            //Singleton s1 = McDonaldsBuilder();
            Director dir = new Director();
            Restaurant mcrest = dir.GenerateMenu(1);
            //Print Mc
            Console.WriteLine(mcrest.Info());
            /*Console.WriteLine(mcrest.name);
            Console.WriteLine("Menu:");
            Console.WriteLine(mcrest.meat);
            Console.WriteLine(mcrest.garnish);
            Console.WriteLine(mcrest.drink);
            Console.WriteLine(mcrest.dessert);
            Console.WriteLine();

            //Console.WriteLine(Mc.Info());
            Restaurant Sc = dir.GenerateMenu(2);
            Console.WriteLine(Sc.Info());
            Restaurant Puz = dir.GenerateMenu(3);
            Console.WriteLine(Puz.Info());
            /*RestaurantBuilder mcbuilder = new McDonaldsBuilder();
            Director dir = new Director();
            Restaurant mcrest = dir.GenerateMenu(mcbuilder);*/
            //Create a Shvidko
           /* RestaurantBuilder shvidkobuilder = new ShvidkoBuilder();
            Restaurant shvidko = dir.GenerateMenu(shvidkobuilder);
            //Create a Puzatahata
            RestaurantBuilder puzatahatabuilder = new PuzatahataBuilder();
            Restaurant puzatahata = dir.GenerateMenu(puzatahatabuilder);
            //Print Mc
            Console.WriteLine(mcrest.name);
            Console.WriteLine("Menu:");
            Console.WriteLine(mcrest.meat);
            Console.WriteLine(mcrest.garnish);
            Console.WriteLine(mcrest.drink);
            Console.WriteLine(mcrest.dessert);
            Console.WriteLine();
            //Print Shvidko
            Console.WriteLine(shvidko.name);
            Console.WriteLine("Menu:");
            Console.WriteLine(shvidko.meat);
            Console.WriteLine(shvidko.garnish);
            Console.WriteLine(shvidko.drink);
            Console.WriteLine(shvidko.dessert);
            Console.WriteLine();
            //Print Puzatahata
            Console.WriteLine(puzatahata.name);
            Console.WriteLine("Menu:");
            Console.WriteLine(puzatahata.meat);
            Console.WriteLine(puzatahata.garnish);
            Console.WriteLine(puzatahata.drink);
            Console.WriteLine(puzatahata.dessert);
            Console.WriteLine();*/
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
    public class Drink : Dish
    {
        public Drink(string name, int price) : base(name, price) { }
    }
    public class Dessert : Dish
    {
        public Dessert(string name, int price) : base(name, price) { }
    }



    // Restaurant
    public class Restaurant
    {
        //public string name;
        public Meat meat;
        public Garnish garnish;
        public Drink drink;
        public Dessert dessert;
        public string Info()
        {
            return  meat.Info() + "\n" + garnish.Info() + "\n" + drink.Info() + "\n" + dessert.Info() + "\n";
        }
    }
    // Report Builder - Builder is responsible for defining
    // the construction process for individual parts. Builder
    // has those individual processes to initialize and
    // configure the report.
    public abstract class RestaurantBuilder
    {
        public Restaurant rest;
        public void CreateRestaurant()
        {
            rest = new Restaurant();
        }
        //public abstract void SetName();
        public abstract void SetMeat();
        public abstract void SetGarnish();
        public abstract void SetDrink();
        public abstract void SetDessert();
        public Restaurant GetRestaurant()
        {
            return rest;
        }
    }
    //mcdonald's 
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
       /* public override void SetName()
        {
            rest.name = "McDonald's";
        }*/
        public override void SetMeat()
        {
            rest.meat = new Meat("meat1",100);
        }
        public override void SetGarnish()
        {
            rest.garnish = new Garnish("garnish1",10);
        }
        public override void SetDrink()
        {
            rest.drink = new Drink("drink1",15);
        }
        public override void SetDessert()
        {
            rest.dessert = new Dessert("dessert1",17);
        }
    }
    //Shvidko
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
        /*public override void SetName()
        {
            rest.name = "Швидко";
        }*/
        public override void SetMeat()
        {
            rest.meat = new Meat("meat2",150);
        }
        public override void SetGarnish()
        {
            rest.garnish = new Garnish("garnish2",25);
        }
        public override void SetDrink()
        {
            rest.drink = new Drink("drink2",11);
        }
        public override void SetDessert()
        {
            rest.dessert = new Dessert("dessert2",20);
        }
    }
    //Puzatahata
    public class PuzatahataBuilder : RestaurantBuilder
    {
            private static PuzatahataBuilder _instance;
            public static PuzatahataBuilder instance
            {
                get
                {
                    if (_instance == null)
                        _instance = new PuzatahataBuilder();
                    return _instance;
                }
            }
            /*public override void SetName()
            {
                rest.name = "Пузата хата";
            }*/
            public override void SetMeat()
            {
                rest.meat = new Meat("meat3",130);
            }
            public override void SetGarnish()
            {
                rest.garnish = new Garnish("garnish3",13);
            }
            public override void SetDrink()
            {
                rest.drink = new Drink("drink3",12);
            }
            public override void SetDessert()
            {
                rest.dessert = new Dessert("dessert3",25);
            }
        }
        /// Director takes those individual processes from the builder
        /// and defines the sequence to build the report.
        public class Director
        {
            public Restaurant GenerateMenu(int name)
            {
                RestaurantBuilder builder;
                if (name == 1)
                {
                    builder = McDonaldsBuilder.instance;
                }
                if (name == 2)
                {
                    builder = ShvidkoBuilder.instance;
                }
                if (name == 3)
                {
                    builder = PuzatahataBuilder.instance;
                }
                else return null;
                builder.CreateRestaurant();
               // builder.SetName();
                builder.SetMeat();
                builder.SetGarnish();
                builder.SetDrink();
                builder.SetDessert();
                /*rest.CreateRestaurant();
                rest.SetName();
                rest.SetMeat();
                rest.SetGarnish();
                rest.SetDrink();
                rest.SetDessert();*/
                return builder.GetRestaurant();
            }
        }
    }
