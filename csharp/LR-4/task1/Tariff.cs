using System;

class Tariff
{
    private double pricePerTon;
    private double cargoMass;
    private string companyName;

    // Свойства
    public double PricePerTon
    {
        get { return pricePerTon; }
        set { pricePerTon = value; }
    }

    public double CargoMass
    {
        get { return cargoMass; }
        set { cargoMass = value; }
    }

    public string CompanyName
    {
        get { return companyName; }
        set { companyName = value; }
    }

    // Конструктор
    public Tariff(string name, double price, double mass)
    {
        companyName = name;
        pricePerTon = price;
        cargoMass = mass;
    }

    // Метод подсчета выручки
    public double CalculateRevenue()
    {
        return pricePerTon * cargoMass;
    }

    // Перегруженные методы изменения тарифа
    public void ChangeTariff(double value)
    {
        pricePerTon += value;
    }

    public void ChangeTariff(double value, bool increase)
    {
        if (increase)
            pricePerTon += value;
        else
            pricePerTon -= value;
    }

    // Статический метод
    public static void ShowInfo()
    {
        Console.WriteLine("Тариф — стоимость перевозки одной тонны груза.");
    }
}