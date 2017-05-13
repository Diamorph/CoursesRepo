using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2
{
    /*abstract class State
    {
        protected string healthy;
        abstract public void Medicine();
    }

    class RegistryState : State
    {
        public RegistryState()
        {
            healthy = "unknown";
        }
        override public void Medicine()
        {
            Console.WriteLine("Пацієнт пройшов регістратуру");
        }
    }

    class HealthyState: State
    {
        public HealthyState()
        {
            healthy = "Healthy";
        }
        override public void Medicine()
        {
            Console.WriteLine("Пацієнт повністю здоровий");
        }
    }

    class UnhealthyState : State
    {
        public UnhealthyState()
        {
            healthy = "Unhealthy";
        }
        public override void Medicine()
        {
            Console.WriteLine("Потрібно пройти курс таблеток");
        }
    }

    class OperationState : State
    {
        public OperationState()
        {
            healthy = "Very unhealthy";
        }
        public override void Medicine()
        {
            Console.WriteLine("Терміново потрібна операція");
        }
    }

    class Patient
    {
        public enum PatientsStates
        {
            registry,
            healthy,
            unhealthy,
            operation
        }
        private State CurrentState;
        RegistryState reg = new RegistryState();
        HealthyState heal = new HealthyState();
        UnhealthyState unheal = new UnhealthyState();
        OperationState oper = new OperationState();
        public Patient(){
        CurrentState = reg;
            }
        public void SetState(PatientsStates newState)
        {
            if (newState == PatientsStates.registry)
            {
                CurrentState = reg;
            }
            else if (newState == PatientsStates.healthy)
            {
                CurrentState = heal;
            }
            else if (newState == PatientsStates.unhealthy)
            {
                CurrentState = unheal;
            }
            else
            {
                CurrentState = oper;
            }
        }
        public void Medicine()
        {
            CurrentState.Medicine();
        }   
    }
    public class Client
    {
        public static int Main(string[] args)
        {
            Patient pat = new Patient();
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Діагностика:");
            Console.WriteLine();
            Console.WriteLine("Пацієнт здоровий:");
            pat.SetState(Patient.PatientsStates.healthy);
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Пацієнт хворий:");
            pat.SetState(Patient.PatientsStates.unhealthy);
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Пацієнт потребує операцію:");
            pat.SetState(Patient.PatientsStates.operation);
            pat.Medicine();
            Console.ReadKey();
            return 0;
        }
    }*/
    interface Imed
    {
        string medicine();
    }
    class Healthy: Imed
    {
        public string medicine()
        {
            return "Patient is healthy";
        }
    }
    class Unhealthy : Imed
    {
        public string medicine()
        {
            return "Patient needs pills";
        }
    }

    class Operation : Imed
    {
        public string medicine()
        {
            return "Patient need operation";
        }
    }

    class Algorithm
    {
        public void Diagnostics(Imed a)
        {
            Console.WriteLine("1)Patient is registered\n" + "2)Patient is examined\n3)" + a.medicine());
        }
    }

    public class Program
    {
        public static int Main(string[] args)
        {
           /* Patient pat = new Patient();
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Діагностика:");
            Console.WriteLine();
            Console.WriteLine("Пацієнт здоровий:");
            pat.SetState(Patient.PatientsStates.healthy);
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Пацієнт хворий:");
            pat.SetState(Patient.PatientsStates.unhealthy);
            pat.Medicine();
            Console.WriteLine();
            Console.WriteLine("Пацієнт потребує операцію:");
            pat.SetState(Patient.PatientsStates.operation);
            pat.Medicine();
            Console.ReadKey();
            return 0;*/
            Algorithm a = new Algorithm();
            Console.WriteLine("Patient is healthy:");
            a.Diagnostics(new Healthy());
            Console.WriteLine();
            Console.WriteLine("Patient is unhealthy:");
            a.Diagnostics(new Unhealthy());
            Console.WriteLine();
            Console.WriteLine("Operation:");
            a.Diagnostics(new Operation());
            Console.ReadKey();
            return 0;

        }
    }
}