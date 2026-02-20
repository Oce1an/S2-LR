using System;

class Program
{
    static void Main()
    {
        bool continueProgram = true;
        Console.WriteLine("-Program for verifying if digits of double digit number are equal-");

        while (continueProgram)
        {
            Console.WriteLine("\nMenu:");
            Console.WriteLine("1 for Continue");
            Console.WriteLine("2 for End.\n");

            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    CheckTwoDigitNumber();
                    break;

                case "2":
                    continueProgram = false;
                    break;

                default:
                    Console.WriteLine("\nIncorrect choice.");
                    break;
            }
        }
    }

    static void CheckTwoDigitNumber()
    {
        int number;

        while (true)
        {
            Console.Write("\nInput double diggit number: ");
            string input = Console.ReadLine();

            if (int.TryParse(input, out number))
            {
                if (number >= 10 && number <= 99)
                {
                    break;
                }
                else
                {
                    Console.WriteLine("\nError: number should only have two digits.");
                }
            }
            else
            {
                Console.WriteLine("\nError: input valid double digit number");
            }
        }

        int firstDigit = number / 10;
        int secondDigit = number % 10;

        if (firstDigit == secondDigit)
        {
            Console.WriteLine($"Digits of number {number} are the same.");
        }
        else
        {
            Console.WriteLine($"Digits of number {number} are not the same.");
        }
    }
}