using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProxyExample
{
class Program
{
static void Main(string[] args)
{
    Text text = new Text();
    Punct p = new Punct();
    p.text = "gfdg.gdfg.gfd";
    DotControlledText dot = new DotControlledText(text);
    dot.Enter_Text(p);
    Console.WriteLine(dot.Get_text());
    Console.ReadKey();
}
}
class Punct
{
    public string text;
}
//interface
abstract class Abst_Text
{
    public abstract void Enter_Text(Punct p);
    public abstract string Get_text();
}
//realsubject
class Text : Abst_Text
{
    public string str;
    public override void Enter_Text(Punct p)
    {
        str += p.text;
    }
    public override string Get_text()
    {
        return str;
    }
       
}
//proxy
class DotControlledText : Abst_Text
{
    private Text text;
    public DotControlledText(Text text)
    {
        this.text = text;
    }
    
    public override void Enter_Text(Punct p)
    {
        char c = '.';
        bool dot = false;
        Punct punct = new Punct();
        for (int i = 0; i < p.text.Length; i++)
        {
            char x = p.text[i];
            if (dot)
            {
                punct.text = x.ToString().ToUpper();
                text.Enter_Text(punct);
                dot = false;
            }
            if (c == x)
                dot = true;
            else
            {
                punct.text = x.ToString();
                text.Enter_Text(punct);
            }
        }
    }
    public override string Get_text()
    {
        return text.Get_text();
    }
}
}