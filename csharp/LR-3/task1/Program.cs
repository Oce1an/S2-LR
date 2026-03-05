using System;

namespace ProcessingProgram
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Program for manipulating even and odd numbers.\nFor exit type exit.");

            ProcessingProgram pgrm = new ProcessingProgram();

            while (true)
            {
                Console.Write("\nInput integer: ");
                string input = Console.ReadLine();

                if (input.Trim().ToLower() == "exit")
                {
                    break;
                }

                if (!int.TryParse(input, out int number))
                {
                    Console.WriteLine("Input valid number.");
                    continue;
                }

                bool continueProcessing = true;
                int currentNumber = number;

                while (continueProcessing)
                {
                    int result = pgrm.ProcessNumber(currentNumber);

                    Console.WriteLine($"Original number: {currentNumber} -> Result: {result}");

                    if (result % 2 == 0 && result != 0)
                    {
                        Console.Write("Would you like to continue dividing? (y/n): ");
                        string answer = Console.ReadLine().Trim().ToLower();

                        if (answer == "y")
                        {
                            currentNumber = result;
                        }
                        else
                        {
                            continueProcessing = false;
                        }
                    }
                    else
                    {
                        if (result == 0)
                        {
                            Console.WriteLine("Odd number was replaced by 0.");
                        }
                        else if (result % 2 != 0)
                        {
                            Console.WriteLine("Odd number will be replaced by 0 in next turn.");
                        }
                        continueProcessing = false;
                    }
                }
            }
        }
    }
}