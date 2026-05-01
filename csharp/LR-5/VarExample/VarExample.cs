using System;

class Program
{
    static void Main()
    {
        var stats = GetStats(new int[] { 1, 2, 3 });
        Console.WriteLine($"Сумма: {stats.Sum}, Количество: {stats.Count}");
    }
    public static (int Sum, int Count) GetStats(int[] numbers)
    {
        return (150, 10);
    }
}