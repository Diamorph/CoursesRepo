using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class MainApp
    {
        static void Main()
        {
            //int [] mas;
            // Non-adapted chemical compound
            int[] mas = { 3,3, 1, 7};
            Compound pin = new Compound(mas);
            pin.Display(mas);
            Compound newPin = new RichCompound(mas);
            newPin.Display(mas);
            // Wait for user
            Console.ReadKey();
        }
    }
    // The 'Target' class
     class Compound
     {
         protected int[] _pin;
         protected int[] _newPin;
         protected int[] _new12Pin;
     
    public Compound(int[] pin){
        this._pin = pin;
    }
    public virtual void Display(int [] mas)
    {
        Console.WriteLine("Pin:");
        foreach (int i in _pin)
        {
            Console.Write(i);
        }
    }
}
    // The 'Adapter' class
     class RichCompound : Compound
     {
         private PinDatabank _bank;
         public RichCompound(int[] pin)
             : base(pin)
         {

         }
         public int[] GetPin(int[] Oldpin)
         {
             const int lenghtNewPin = 12;
             const int lenghtOldPin = 8;
             const int code = 4;
             int[] pin;
             pin = new int[lenghtNewPin];
             for (int i = 0; i < lenghtOldPin; i++)
             {
                 pin[i] = Oldpin[i];
             }
             for (int i = 0; i < code; i++)
             {
                 pin[i + lenghtOldPin] = Oldpin[i];
             }
             return pin; 
         }
         public override void Display(int[] mas)
         {
             _bank = new PinDatabank();
             _newPin = _bank.GetNewPin(mas);
             _new12Pin = GetPin(_newPin);
             

             Console.WriteLine
                 ("\nNew pin:");
             foreach (int i in _new12Pin)
                 Console.Write(i);

         }
     }
    // The 'Adaptee' class
    class PinDatabank
    {
        public int[] GetNewPin(int[] Oldpin)
        {
            
            const int lenghtOldPin = 8;
            const int code = 4;
            int[] pin;
            pin = new int[lenghtOldPin];
            for (int i = 0; i < code; i++)
            {
                pin[i] = Oldpin[i];
            }
            for (int i = 0; i < code; i++)
            {
                pin[i + code] = Oldpin[i]+1;
                } 
          return pin;          
        }
    }
}
