using System;

class Program
{
    static void Main()
    {
        TransportCompany company = TransportCompany.GetInstance();

        Tariff t1 = new Tariff("FastCargo", 100, 20);
        Tariff t2 = new Tariff("FastCargo", 100, 15);

        company.AddTariff(t1);
        company.AddTariff(t2);

        Console.WriteLine("Начальные данные:");
        company.ShowAll();

        Console.WriteLine("Общая выручка:");
        Console.WriteLine(company.CalculateTotalRevenue());

        Console.WriteLine("\nИзменение тарифа");

        Console.Write("Введите величину изменения: ");
        double change = Convert.ToDouble(Console.ReadLine());

        t1.ChangeTariff(change, true);

        Console.WriteLine("\nНовые данные:");
        company.ShowAll();

        Console.WriteLine("Новая выручка:");
        Console.WriteLine(company.CalculateTotalRevenue());
    }
}