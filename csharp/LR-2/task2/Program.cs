using System;

class Program
{
    static void Main()
    {
        string choice;

        do
        {
            Console.WriteLine("\n--Menu--");
            Console.WriteLine("1. Continue");
            Console.WriteLine("2. Exit");

            choice = Console.ReadLine();

            switch (choice)
            {
                case "1":

                    Console.Write("Input x value: ");
                    string choiceX = Console.ReadLine();

                    Console.Write("Input y value: ");
                    string choiceY = Console.ReadLine();

                    bool dX = double.TryParse(choiceX, out double x);
                    bool dY = double.TryParse(choiceY, out double y);

                    if (dX && dY)
                    {
                        if (x * x + y * y < 225.0)
                        {
                            Console.WriteLine("Yes.");
                        }
                        else if (x * x + y * y > 625.0)
                        {
                            Console.WriteLine("Yes.");
                        }
                        else if (x * x + y * y == 225.0 || x * x + y * y == 625.0)
                        {
                            Console.WriteLine("On the edge.");
                        }
                        else
                        {
                            Console.WriteLine("No.");
                        }
                    }
                    else
                    {
                        Console.WriteLine("Input valid numbers.");
                    }
                    break;

                case "2":
                    break;

                default:
                    Console.WriteLine("Choose between 1 and 2.");
                    break;
            }

        } while (choice != "2");
    }
}