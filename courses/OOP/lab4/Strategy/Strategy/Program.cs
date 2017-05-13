using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Strategy
{
    class Program
    {
        static void Main(string[] args)
        {
            Transfer trn;
            trn = new Transfer();
            trn.TripAmount = (double)50;

            BigBus big;
            big = new BigBus();
            trn.SetTrip(big);
            Console.WriteLine("Трансфер на великому автобусі(економ):");
            Console.WriteLine(trn.Trip.ToString());

            Minibus min;
            min = new Minibus();
            trn.SetTrip(min);
            Console.WriteLine("Трансфер на мікроавтобусі(стандарт):");
            Console.WriteLine(trn.Trip.ToString());

            Taxi taxi;
            taxi = new Taxi();
            trn.SetTrip(taxi);
            Console.WriteLine("Трансфер на таксі(люкс):");
            Console.WriteLine(trn.Trip.ToString());
          
            Console.ReadKey();
        }
    }

    public interface ITripStrategy
    {
        double CalculateTrip(double distance);
    }
    public class BigBus : ITripStrategy
    {
        public BigBus(){}
        public double CalculateTrip(double distance)
        {
            return distance * 0.5;
        }

    }
    public class Minibus : ITripStrategy
    {
        public Minibus()
        {

        }
        public double CalculateTrip(double distance)
        {
            return distance * 1.5;
        }
    }

    public class Taxi : ITripStrategy
    {
        public Taxi()
        {

        }
        public double CalculateTrip(double distance)
        {
            return distance * 5;
        }
    }

      public class Transfer
    {
        private ITripStrategy _Trip;
        private double _TripAmount;

        public Transfer()
        {

        }

        public void SetTrip(ITripStrategy trip)
        {
            _Trip = trip;
        }
        public double TripAmount
        {
            get { return _TripAmount; }
            set { _TripAmount = value; }
        }
        public double Trip
        {
            get { return _Trip.CalculateTrip(_TripAmount); }
        }
    }
}