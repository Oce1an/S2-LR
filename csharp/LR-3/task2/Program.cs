using System;
using Services;

class Program
{
    static void Main()
    {
        Console.WriteLine("Program for evaluating value of y.\nFor exit type exit.");

        try
        {
            Console.Write("Input value of c: ");
            double c = double.Parse(Console.ReadLine());

            Console.Write("Input value of d: ");
            double d = double.Parse(Console.ReadLine());

            Console.Write("Input value of k: ");
            double k = double.Parse(Console.ReadLine());

            Console.Write("Input value of z: ");
            double z = double.Parse(Console.ReadLine());

            var pgrm = new Functions();
            double result = pgrm.ProcessFunctions(c, d, k, z);

            Console.WriteLine($"Final result: y = {result}");
        }
        catch (FormatException)
        {
            return;
        }
    }
}