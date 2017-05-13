using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/*
namespace task2
{
    class Program
    {
        static void Main(string[] args)
        {
            Composite Course = new Composite("PZKS");

            Composite Group1 = new Composite("KP-51");
            Course.Add(Group1);
            Composite Group2 = new Composite("KP-52");
            Course.Add(Group2);

            Composite Student1 = new Composite("Ivan");
            Group1.Add(Student1);
            Composite Student2 = new Composite("Anton");
            Group1.Add(Student2);
            Composite Student3 = new Composite("Vlad");
            Group1.Add(Student3);
            Composite Student4 = new Composite("Sasha");
            Group2.Add(Student4);
            Composite Student5 = new Composite("Stas");
            Group2.Add(Student5);

            Course.GetExamInfo();
            Course.Display(2);
            Console.ReadKey();

        }
    }

    abstract class StudentComponent
    {
        protected string name;
        protected int exam;

        public StudentComponent(string name)
        {
            this.name = name;
        }
        public abstract void Add(StudentComponent s);
        public abstract void Remove(StudentComponent s);
        public abstract int GetExamInfo();
        public abstract void Display(int depth);
    }

    class Composite : StudentComponent
{
        private List<StudentComponent> _children = new List<StudentComponent>();
    // Constructor
        public Composite(string name) : base(name)
        {
            this.exam = 0;
        }
        public override void Add(StudentComponent component)
        {
            _children.Add(component);
        }

        public override void Remove(StudentComponent component)
        {
            _children.Remove(component);
        }
        public override void Display(int depth)
        {
            Console.WriteLine(new String('-', depth) + name + " " + this.exam.ToString());
        // Recursively display child nodes
            foreach (StudentComponent component in _children)
            component.Display(depth + 2);
        }
        public override int GetExamInfo()
        {
            Random rnd = new Random();
            this.exam = rnd.Next(2, 6);
            foreach (StudentComponent component in _children)
            this.exam += component.GetExamInfo();
            return this.exam;
        }
}

    class Student : StudentComponent
    {
        public Student(string name) : base(name)
        {
            Random rnd = new Random();
            this.exam = rnd.Next(2,6);
        }
        public override void Add(StudentComponent c)
        {
        Console.WriteLine("Impossible operation");
        }
        public override void Remove(StudentComponent c)
        {
        Console.WriteLine("Impossible operation");
        }
        public override void Display(int depth)
        {
        Console.WriteLine(new String('-', depth) + name + " " + exam.ToString());
        }
        public override int GetExamInfo()
        {
        return this.exam;
        }
    }
}
*/
namespace CompositeExample
{
 class MainApp
 {
    static void Main()
 {
     //district is a root
     Composite university = new Composite("KPI");
     //streets
     Composite faculty = new Composite("FPM");
     university.Add(faculty);
     //buildings
     Composite group1 = new Composite("KP-51");
     Composite group2 = new Composite("Kp-52");
     faculty.Add(group1);
     faculty.Add(group2);
     Student s1 = new Student("Ivan");
     Student s2 = new Student("Anton");
     Student s3 = new Student("Vlad");
     Student s4 = new Student("Sasha");

     group1.Add(s1);
     group2.Add(s2);
     group1.Add(s3);
     group1.Add(s4);

     // Display all info
     university.GetExamInfo();
     university.Display(2);
     Console.ReadKey();
     }
 }
     abstract class StudentComponent
     {
         protected string name;
         // Constructor
         public StudentComponent(string name)
         {
         this.name = name;
         }
         public abstract void Add(StudentComponent c);
         public abstract void Remove(StudentComponent c);
         public abstract bool GetExamInfo();
         public abstract void Display(int depth);

     }
 /// <summary>
 /// The 'Composite' class
 /// </summary>
     class Composite : StudentComponent
     {
             private List<StudentComponent> _children = new List<StudentComponent>();
         // Constructor
         public Composite(string name) : base(name)
         {
         }
         public override void Add(StudentComponent component)
         {
            _children.Add(component);
         }
         public override void Remove(StudentComponent component)
         {
            _children.Remove(component);
         }
         public override void Display(int depth)
         {
             Console.WriteLine(new String('-', depth) + name);
             // Recursively display child nodes
             foreach (StudentComponent component in _children)
                component.Display(depth + 2);
         }       
         public override bool GetExamInfo()
         {
             return true;
         }
     }

     class Student : StudentComponent
     {
         private static Random rnd = new Random();
         protected bool exam = Convert.ToBoolean(rnd.Next(0, 2));

         public Student(string name) : base(name)
         {
         }
         public override void Add(StudentComponent c)
         {
            Console.WriteLine("Impossible operation");
         }

         public override void Remove(StudentComponent c)
         {
            Console.WriteLine("Impossible operation");
         }
         public override void Display(int depth)
         {
            Console.WriteLine(new String('-', depth) + name + " " + exam.ToString());
         }
         public override bool GetExamInfo()
         {          
            return this.exam;
         }
         }
}
