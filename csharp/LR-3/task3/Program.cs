using System;
using DateLibrary;

namespace DateApp
{
    class Program
    {
        static void Main()
        {
            DateService dateService = new DateService();

            Console.WriteLine("\nProgram for working with time dates");

            while (true)
            {
                Console.WriteLine("1. Determine the day of the week by date");
                Console.WriteLine("2. Find out the difference between the current date and the specified date");
                Console.WriteLine("3. Exit");

                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1":
                        Console.Write("Input date. \nExamples: 2024-03-15 or 15.03.2024: ");
                        string dateInput = Console.ReadLine();

                        string dayOfWeek = dateService.GetDay(dateInput);

                        Console.WriteLine($"Result: {dayOfWeek}");
                        break;

                    case "2":
                        Console.Write("Input day (1-31): ");
                        int day = int.Parse(Console.ReadLine());

                        Console.Write("Input month (1-12): ");
                        int month = int.Parse(Console.ReadLine());

                        Console.Write("Input year: ");
                        int year = int.Parse(Console.ReadLine());

                        int daysDifference = dateService.GetDaysSpan(day, month, year);

                        Console.WriteLine($"\nResult: {daysDifference} days");

                        if (daysDifference > 0)
                            Console.WriteLine($"Days until specified date: {daysDifference}");
                        else if (daysDifference < 0)
                            Console.WriteLine($"Specified date was {Math.Abs(daysDifference)} days ago");
                        else
                            Console.WriteLine("Specified date is today!");
                        break;

                    case "3":
                        return;

                    default:
                        Console.WriteLine("Not valid input.");
                        break;
                }
            }
        }
    }
}