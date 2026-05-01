using System;

// Абстрактный базовый класс
public abstract class ComputerTech
{
    public string Manufacturer { get; set; }
    public string Model { get; set; }
    public int Year { get; set; }
    public decimal Price { get; set; }

    // Конструктор родительского класса – будет вызываться при создании наследников
    public ComputerTech(string manufacturer, string model, int year, decimal price)
    {
        Manufacturer = manufacturer;
        Model = model;
        Year = year;
        Price = price;
    }

    // Абстрактный метод – обязателен к реализации в неабстрактных наследниках
    public abstract void DisplayInfo();

    // Обычный метод с реализацией
    public void UpdatePrice(decimal newPrice)
    {
        Price = newPrice;
        Console.WriteLine($"Цена обновлена: {Price} руб.");
    }

    // Виртуальный метод – может быть переопределён в наследниках
    public virtual void Repair()
    {
        Console.WriteLine("Выполняется стандартный ремонт компьютерной техники.");
    }

    // Метод, который в одном из наследников будет скрыт (new)
    public void ShowPrice()
    {
        Console.WriteLine($"Цена: {Price} руб.");
    }

    // Виртуальный метод, перегружаемый (overload) в наследнике
    public virtual void Diagnose()
    {
        Console.WriteLine("Диагностика устройства...");
    }
}

// Класс Laptop – наследует ComputerTech
public class Laptop : ComputerTech
{
    public double ScreenSize { get; set; } // дюймы
    public int BatteryLife { get; set; }   // часы

    // Вызов конструктора родительского класса через base
    public Laptop(string manufacturer, string model, int year, decimal price,
                  double screenSize, int batteryLife)
        : base(manufacturer, model, year, price)
    {
        ScreenSize = screenSize;
        BatteryLife = batteryLife;
    }

    // Реализация абстрактного метода
    public override void DisplayInfo()
    {
        Console.WriteLine($"Ноутбук: {Manufacturer} {Model}, {Year} г., " +
                          $"Экран: {ScreenSize}\", Батарея: {BatteryLife} ч, Цена: {Price} руб.");
    }

    // Переопределение виртуального метода Repair
    public override void Repair()
    {
        Console.WriteLine("Ремонт ноутбука: замена клавиатуры, чистка системы охлаждения.");
    }

    // Перегрузка метода Diagnose (overload) – другой набор параметров
    public void Diagnose(bool quick)
    {
        if (quick)
            Console.WriteLine("Быстрая диагностика ноутбука: проверка температуры и ОЗУ.");
        else
            Console.WriteLine("Полная диагностика ноутбука: тест SSD, батареи, стресс-тест CPU.");
    }
}

// Sealed-класс – закрыт для наследования
public sealed class GamingLaptop : Laptop
{
    public string GraphicsCard { get; set; }

    public GamingLaptop(string manufacturer, string model, int year, decimal price,
                        double screenSize, int batteryLife, string graphicsCard)
        : base(manufacturer, model, year, price, screenSize, batteryLife)
    {
        GraphicsCard = graphicsCard;
    }

    public override void DisplayInfo()
    {
        Console.WriteLine($"Игровой ноутбук: {Manufacturer} {Model}, {Year} г., " +
                          $"GPU: {GraphicsCard}, Экран: {ScreenSize}\", Батарея: {BatteryLife} ч, Цена: {Price} руб.");
    }
}

// Класс Tablet – наследует ComputerTech
public class Tablet : ComputerTech
{
    public double ScreenSize { get; set; }
    public bool StylusSupport { get; set; }

    public Tablet(string manufacturer, string model, int year, decimal price,
                  double screenSize, bool stylusSupport)
        : base(manufacturer, model, year, price)
    {
        ScreenSize = screenSize;
        StylusSupport = stylusSupport;
    }

    public override void DisplayInfo()
    {
        string stylus = StylusSupport ? "есть" : "нет";
        Console.WriteLine($"Планшет: {Manufacturer} {Model}, {Year} г., " +
                          $"Экран: {ScreenSize}\", Стилус: {stylus}, Цена: {Price} руб.");
    }

    // Repair НЕ переопределяется – используется базовая реализация
    // (виртуальный метод остался без изменений)

    // Сокрытие (new) метода родительского класса ShowPrice
    public new void ShowPrice()
    {
        Console.WriteLine("Информация о цене недоступна. Обратитесь к продавцу.");
        // Демонстрация вызова скрытого метода родительского класса
        Console.Write("Скрытая реализация: ");
        base.ShowPrice();
    }
}

// Точка входа
class Program
{
    static void Main()
    {
        Console.WriteLine("~~~~~~~~~~~~НОУТБУК~~~~~~~~~~~~");
        Laptop laptop = new Laptop("Dell", "XPS 15", 2023, 120000m, 15.6, 10);
        laptop.DisplayInfo();
        laptop.UpdatePrice(115000m);
        laptop.Repair();
        laptop.Diagnose();            // базовая версия
        laptop.Diagnose(quick: true); // перегруженная версия
        laptop.ShowPrice();

        Console.WriteLine("\n~~~~~~~~~~~~ПЛАНШЕТ~~~~~~~~~~~~");
        Tablet tablet = new Tablet("Apple", "iPad Pro", 2022, 90000m, 12.9, true);
        tablet.DisplayInfo();
        tablet.Repair();             // используется базовая реализация Repair
        tablet.ShowPrice();          // вызов скрытого метода (с new), внутри вызывается base.ShowPrice()

        Console.WriteLine("\n~~~~~~~~~~~~ИГРОВОЙ НОУТБУК (sealed)~~~~~~~~~~~~");
        GamingLaptop gl = new GamingLaptop("ASUS", "ROG Zephyrus", 2024, 200000m, 16.0, 8, "RTX 4070");
        gl.DisplayInfo();
        gl.Repair();                 // унаследован от Laptop
        gl.Diagnose();
        gl.Diagnose(false);

        // Проверка, что sealed-класс действительно нельзя наследовать
        // Следующая строка вызовет ошибку компиляции, поэтому закомментирована:
        // class SuperLaptop : GamingLaptop { } // Error CS0509

        Console.WriteLine("\nВсе методы продемонстрированы.");
    }
}