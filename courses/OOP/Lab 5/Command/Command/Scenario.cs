using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Command
{
    class Scenario
    {
        public List<Command> scenario = new List<Command>();
        public Scenario() {}
        public Scenario(params Command[]cmd)
        {
            foreach (Command c in cmd)
                scenario.Add(c);
        }
        public void Run()
        {
            foreach (Command cmd in scenario)
            {
                cmd.Execute();
            }
        }
        public void Save()
        {
            using (System.IO.StreamWriter file =
            new System.IO.StreamWriter(@"D:\Учоба\2 курс\2 cеместр\ООП\Lab 5\Command\Command\output.txt"))
            {
                foreach (Command cmd in scenario)
                {
                    file.WriteLine(cmd.ToString());                 
                }
            }
        }
    }
}
