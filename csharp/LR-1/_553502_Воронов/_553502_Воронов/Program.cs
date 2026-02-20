using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("Input first number: ");
        double a = double.Parse(Console.ReadLine());

        Console.Write("Input second number: ");
        double b = double.Parse(Console.ReadLine());

        double result = a / b;

        Console.WriteLine("Result of division: " + result);
    }
}