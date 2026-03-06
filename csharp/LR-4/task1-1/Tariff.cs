using System;

namespace FreightCompany
{
    /// <summary>
    /// Контейнеризируемый класс - Тариф
    /// </summary>
    public class Tariff
    {
        // Поля
        private decimal _ratePerTon;      // тариф за тонну
        private string _currency;          // валюта
        private DateTime _lastUpdated;     // дата последнего изменения

        // Свойства
        public decimal RatePerTon
        {
            get { return _ratePerTon; }
            private set
            {
                if (value <= 0)
                    throw new ArgumentException("Тариф должен быть положительным числом");
                _ratePerTon = value;
                _lastUpdated = DateTime.Now;
            }
        }

        public string Currency
        {
            get { return _currency; }
            set
            {
                if (string.IsNullOrWhiteSpace(value))
                    throw new ArgumentException("Валюта не может быть пустой");
                _currency = value.ToUpper();
            }
        }

        public DateTime LastUpdated => _lastUpdated;

        // Конструкторы
        public Tariff()
        {
            RatePerTon = 1000; // тариф по умолчанию
            Currency = "RUB";
            _lastUpdated = DateTime.Now;
        }

        public Tariff(decimal ratePerTon, string currency)
        {
            RatePerTon = ratePerTon;
            Currency = currency;
            _lastUpdated = DateTime.Now;
        }

        // Перегруженные методы для изменения тарифа
        public void ChangeRate(decimal newRate)
        {
            RatePerTon = newRate;
            Console.WriteLine($"Тариф изменен на {newRate} {Currency}");
        }

        public void ChangeRate(double newRate)
        {
            ChangeRate((decimal)newRate);
        }

        public void ChangeRate(int newRate)
        {
            ChangeRate((decimal)newRate);
        }

        // Методы для увеличения/уменьшения тарифа
        public void IncreaseRate(decimal percent)
        {
            if (percent <= 0)
                throw new ArgumentException("Процент должен быть положительным");

            decimal increaseAmount = RatePerTon * percent / 100;
            RatePerTon += increaseAmount;
            Console.WriteLine($"Тариф увеличен на {percent}%");
        }

        public void IncreaseRate(double percent)
        {
            IncreaseRate((decimal)percent);
        }

        public void DecreaseRate(decimal percent)
        {
            if (percent <= 0 || percent >= 100)
                throw new ArgumentException("Процент должен быть в диапазоне (0, 100)");

            decimal decreaseAmount = RatePerTon * percent / 100;
            RatePerTon -= decreaseAmount;
            Console.WriteLine($"Тариф уменьшен на {percent}%");
        }

        public void DecreaseRate(double percent)
        {
            DecreaseRate((decimal)percent);
        }

        // Переопределение метода ToString()
        public override string ToString()
        {
            return $"Тариф: {RatePerTon:F2} {Currency} за тонну (последнее обновление: {LastUpdated:dd.MM.yyyy HH:mm})";
        }
    }
}