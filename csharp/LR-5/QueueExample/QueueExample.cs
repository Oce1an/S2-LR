using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        var person = ("Иван", 25);
        Console.WriteLine(person.Item1);

        var employee = (Name: "Анна", Age: 30);
        Console.WriteLine(employee.Name);
        Console.WriteLine(employee.Age);

        var (name, age) = ("Максим", 22);
        Console.WriteLine(name);

        Tuple<string, int> oldTuple = new Tuple<string, int>("Петр", 40);


        Queue<string> tasks = new Queue<string>();

        tasks.Enqueue("Скачать файл");
        tasks.Enqueue("Распаковать архив");
        tasks.Enqueue("Удалить временные файлы");

        Console.WriteLine($"Задач в очереди: {tasks.Count}");

        Console.WriteLine($"Следующая задача на выполнение: {tasks.Peek()}");

        while (tasks.Count > 0)
        {
            string currentTask = tasks.Dequeue();
            Console.WriteLine($"Выполняется: {currentTask}. Осталось задач: {tasks.Count}");
        }
    }
}
