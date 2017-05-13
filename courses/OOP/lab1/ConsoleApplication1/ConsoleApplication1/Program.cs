using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            Phone p1 = new Camera("Camera 1", 2000, 10, 15, true);
            Decorator d1 = new FlashDecorator();
            Decorator d2 = new RedEyeDecorator();
            Decorator d3 = new FocusDecorator();
            d3.SetGadgetOn(p1);
            if (p1.Time > 18 || p1.Time < 8)
            {
                d1.SetGadgetOn(d3);
                if (p1.Light)
                {
                    d2.SetGadgetOn(d1);
                    d2.Show_Info();
                    d2.Make_Photo();
                }
                else
                {
                    d1.Show_Info();
                    d1.Make_Photo();
                }
            }
            else 
            {
                if (p1.Light)
                {
                    d2.SetGadgetOn(d3);
                    d2.Show_Info();
                    d2.Make_Photo();
                }
                else
                {
                    d3.Show_Info();
                    d3.Make_Photo();
                }
            }
            /*if (p1.Time > 18 && p1.Light && p1.Time < 8) 
            {
                d1.SetGadgetOn(d3);
                d2.SetGadgetOn(d1);
                d2.Show_Info();
                d2.Make_Photo();
            }
            if (!p1.Light && p1.Time > 8 && p1.Time < 18)
            {
                d3.Show_Info();
                d3.Make_Photo();
            }
            if (p1.Light && p1.Time > 18 && p1.Time < 8)
            /*if (p1.Light)
            {
                d2.SetGadgetOn(p1);
            }
            /*d1.SetGadgetOn(p1);
            d2.SetGadgetOn(d1);
            d3.SetGadgetOn(d2);
            d3.Show_Info();
            d3.Make_Photo();*/
            //p1.Show_Info();
            //p1.Make_Photo();
            Console.ReadKey();
        }
    }


// Абстрактний клас "Фотоапарат"
abstract class Phone
{
    protected string Model;
    protected int Memory;
    protected int Quality;
    public int Time;
    public bool Light;


    public abstract void Show_Info();
    public abstract void Make_Photo();
}

class Camera : Phone
{
    public Camera(string M, int Mem, int Q, int T, bool L)
    {
        this.Model = M;
        this.Memory = Mem;
        this.Quality = Q;
        this.Time = T;
        this.Light = L;
    }
    public override void Show_Info()
    {
        Console.WriteLine("Model: {0}\nFree memory: {1} M\nQuality of photo: {2}\nTime: {3}\nLight: {4}", this.Model, this.Memory, this.Quality, this.Time, this.Light);
    }
    public override void Make_Photo()
    {
        if (Memory < 1)
        {
            Console.WriteLine("\nOut of Memory");
            return;
        }
        Memory--;
        /*if (Time > 18 || Light)
        {
            Console.WriteLine("\nFlash is on");
        }*/
        Console.WriteLine("\nPhoto is made. Free memory left: {0}", Memory);
    }
}
    // Декоратор
    abstract class Decorator:Phone
    {
        protected Phone Ph;
        public void SetGadgetOn(Phone basePhone)
        {
            this.Ph = basePhone;
        }
        public override void Show_Info()
        {
            if (Ph != null) Ph.Show_Info();
        }
        public override void Make_Photo()
        {
            if (Ph != null) Ph.Make_Photo();
        }
    }

    //Конкретні декоратори:
    //Спалах
    class FlashDecorator : Decorator
    {
        public override void Make_Photo()
        {
            Console.Write("\nPhoto with flash.");
            base.Make_Photo();
        }
        public override void Show_Info()
        {
            base.Show_Info();
            Console.WriteLine("Flash is on");
        }
    }
    // Ефект червоних очей
    class RedEyeDecorator : Decorator
    {
        public override void Make_Photo()
        {
            Console.Write("\nRed eyes were destroyed");
            base.Make_Photo();
        }
        public override void Show_Info()
        {
            base.Show_Info();
            Console.WriteLine("Red eyes destroyer is on");
        }
    }
    // Фокус
    class FocusDecorator : Decorator
    {
        public override void Make_Photo()
        {
            Console.Write("\nPhoto with focus");
            base.Make_Photo();
        }
        public override void Show_Info()
        {
            base.Show_Info();
            Console.WriteLine("Focus is on");
        }
    }

    }