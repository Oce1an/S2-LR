using System;

namespace FreightCompany
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("=== ДЕМОНСТРАЦИЯ РАБОТЫ СИСТЕМЫ ГРУЗОПЕРЕВОЗОК ===\n");

                // Получаем экземпляр Singleton и настраиваем фирму
                var company = FreightCompany.Instance;
                company.CompanyName = "Быстрые Грузоперевозки";

                Console.WriteLine($"Создана фирма: {company.CompanyName}");
                Console.WriteLine($"Начальный {company.CurrentTariff}\n");

                // Добавляем перевозки (демонстрация перегруженных методов)
                company.AddShipment("Строительные материалы", 25.5); // double
                company.AddShipment("Продукты питания", 15.3m);      // decimal
                company.AddShipment("Оборудование", 8.7m, DateTime.Now.AddDays(-5)); // с датой
                company.AddShipment("Мебель", 12.0);
                company.AddShipment("Химикаты", 5, DateTime.Now.AddDays(-10));

                Console.WriteLine();

                // Демонстрация работы с тарифом
                Console.WriteLine("=== РАБОТА С ТАРИФОМ ===");
                company.IncreaseTariff(10);      // увеличение на 10%
                company.IncreaseTariff(5);      // увеличение на 5.5%
                company.DecreaseTariff(3);        // уменьшение на 3%

                Console.WriteLine($"Текущий {company.CurrentTariff}\n");

                // Демонстрация расчета выручки
                Console.WriteLine("=== РАСЧЕТ ВЫРУЧКИ ===");
                decimal totalRevenue = company.CalculateTotalRevenue();
                Console.WriteLine($"Общая выручка: {totalRevenue:F2} {company.CurrentTariff.Currency}");

                // Выручка за последние 30 дней
                decimal monthlyRevenue = company.CalculateTotalRevenue(
                    DateTime.Now.AddDays(-30),
                    DateTime.Now);
                Console.WriteLine($"Выручка за последние 30 дней: {monthlyRevenue:F2} {company.CurrentTariff.Currency}");

                // Выручка за текущий месяц
                decimal currentMonthRevenue = company.CalculateTotalRevenue(
                    DateTime.Now.Year,
                    DateTime.Now.Month);
                Console.WriteLine($"Выручка за текущий месяц: {currentMonthRevenue:F2} {company.CurrentTariff.Currency}\n");

                // Проверка Singleton (оба объекта ссылаются на один экземпляр)
                var sameCompany = FreightCompany.Instance;
                Console.WriteLine($"Проверка Singleton: {ReferenceEquals(company, sameCompany)} (обе переменные ссылаются на один объект)\n");

                // Статический метод для создания фирмы
                Console.WriteLine("=== СОЗДАНИЕ ЕЩЕ ОДНОЙ ФИРМЫ (НО ЭТО ТОТ ЖЕ SINGLETON) ===");
                var anotherCompany = FreightCompany.CreateCompany("Экспресс Доставка", 1500, "USD");
                Console.WriteLine($"Имя фирмы изменено на: {anotherCompany.CompanyName}");
                Console.WriteLine($"Новый {anotherCompany.CurrentTariff}");
                Console.WriteLine($"Всего перевозок: {anotherCompany.TotalShipmentsCount} (данные сохранились!)");

                // Полный отчет
                Console.WriteLine("\n" + company.GetCompanyReport());

                // Демонстрация обработки ошибок
                Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ ОБРАБОТКИ ОШИБОК ===");
                try
                {
                }
                catch (ArgumentException ex)
                {
                    Console.WriteLine($"Ошибка: {ex.Message}");
                }

                try
                {
                    company.ChangeTariff(-500); // отрицательный тариф
                }
                catch (ArgumentException ex)
                {
                    Console.WriteLine($"Ошибка: {ex.Message}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Необработанная ошибка: {ex.Message}");
            }

            Console.WriteLine("\nНажмите любую клавишу для выхода...");
            Console.ReadKey();
        }
    }
}