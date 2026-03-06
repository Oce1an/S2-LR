using System;
using System.Collections.Generic;

class TransportCompany
{
    private static TransportCompany instance;

    private List<Tariff> tariffs = new List<Tariff>();

    // Singleton
    private TransportCompany() { }

    public static TransportCompany GetInstance()
    {
        if (instance == null)
            instance = new TransportCompany();

        return instance;
    }

    // Добавление перевозки
    public void AddTariff(Tariff tariff)
    {
        tariffs.Add(tariff);
    }

    // Общая выручка
    public double CalculateTotalRevenue()
    {
        double sum = 0;

        foreach (var t in tariffs)
        {
            sum += t.CalculateRevenue();
        }

        return sum;
    }

    // Вывод информации
    public void ShowAll()
    {
        foreach (var t in tariffs)
        {
            Console.WriteLine($"Фирма: {t.CompanyName}");
            Console.WriteLine($"Тариф: {t.PricePerTon}");
            Console.WriteLine($"Масса: {t.CargoMass}");
            Console.WriteLine();
        }
    }

    // Статический метод
    public static void CompanyInfo()
    {
        Console.WriteLine("Фирма занимается грузоперевозками.");
    }
}