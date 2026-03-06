using System;
using System.Collections.Generic;
using System.Linq;

namespace FreightCompany
{
    /// <summary>
    /// Класс-контейнер (Singleton) - Фирма грузоперевозок
    /// </summary>
    public sealed class FreightCompany
    {
        // Статическое поле для хранения единственного экземпляра
        private static FreightCompany _instance;
        private static readonly object _lock = new object();

        // Поля
        private string _companyName;
        private List<Shipment> _shipments;      // список перевозок
        private Tariff _currentTariff;           // текущий тариф

        // Статическое свойство для доступа к экземпляру (Singleton)
        public static FreightCompany Instance
        {
            get
            {
                // Потокобезопасная реализация (Double-check locking)
                if (_instance == null)
                {
                    lock (_lock)
                    {
                        if (_instance == null)
                        {
                            _instance = new FreightCompany();
                        }
                    }
                }
                return _instance;
            }
        }

        // Приватный конструктор (Singleton)
        private FreightCompany()
        {
            _shipments = new List<Shipment>();
            _currentTariff = new Tariff(); // тариф по умолчанию
            _companyName = "Неназванная фирма";
        }

        // Свойства
        public string CompanyName
        {
            get { return _companyName; }
            set
            {
                if (string.IsNullOrWhiteSpace(value))
                    throw new ArgumentException("Название фирмы не может быть пустым");
                _companyName = value;
            }
        }

        public Tariff CurrentTariff
        {
            get { return _currentTariff; }
        }

        public int TotalShipmentsCount => _shipments.Count;

        public decimal TotalCargoMass => _shipments.Sum(s => s.CargoMass);

        // Статический метод для создания фирмы с параметрами
        public static FreightCompany CreateCompany(string name, decimal initialRate, string currency)
        {
            var company = Instance;
            company.CompanyName = name;
            company._currentTariff = new Tariff(initialRate, currency);
            return company;
        }

        // Перегруженные методы для добавления перевозки
        public void AddShipment(string cargoName, double mass)
        {
            AddShipment(cargoName, (decimal)mass);
        }

        public void AddShipment(string cargoName, decimal mass)
        {
            if (mass <= 0)
                throw new ArgumentException("Масса груза должна быть положительной");

            var shipment = new Shipment
            {
                CargoName = cargoName,
                CargoMass = mass,
                ShipmentDate = DateTime.Now
            };

            _shipments.Add(shipment);
            Console.WriteLine($"Добавлена перевозка: {cargoName}, масса: {mass} т");
        }

        public void AddShipment(string cargoName, decimal mass, DateTime date)
        {
            if (mass <= 0)
                throw new ArgumentException("Масса груза должна быть положительной");

            var shipment = new Shipment
            {
                CargoName = cargoName,
                CargoMass = mass,
                ShipmentDate = date
            };

            _shipments.Add(shipment);
            Console.WriteLine($"Добавлена перевозка: {cargoName}, масса: {mass} т, дата: {date:dd.MM.yyyy}");
        }

        // Метод для подсчета общей выручки
        public decimal CalculateTotalRevenue()
        {
            return _shipments.Sum(s => s.CargoMass * _currentTariff.RatePerTon);
        }

        // Перегруженный метод для подсчета выручки за период
        public decimal CalculateTotalRevenue(DateTime startDate, DateTime endDate)
        {
            return _shipments
                .Where(s => s.ShipmentDate >= startDate && s.ShipmentDate <= endDate)
                .Sum(s => s.CargoMass * _currentTariff.RatePerTon);
        }

        public decimal CalculateTotalRevenue(int year, int month)
        {
            return _shipments
                .Where(s => s.ShipmentDate.Year == year && s.ShipmentDate.Month == month)
                .Sum(s => s.CargoMass * _currentTariff.RatePerTon);
        }

        // Методы для работы с тарифом (делегирование)
        public void ChangeTariff(decimal newRate)
        {
            _currentTariff.ChangeRate(newRate);
        }

        public void IncreaseTariff(decimal percent)
        {
            _currentTariff.IncreaseRate(percent);
        }

        public void DecreaseTariff(decimal percent)
        {
            _currentTariff.DecreaseRate(percent);
        }

        // Метод для получения отчета
        public string GetCompanyReport()
        {
            var report = $"=== ОТЧЕТ ФИРМЫ '{_companyName}' ===\n";
            report += $"Количество перевозок: {TotalShipmentsCount}\n";
            report += $"Общая масса грузов: {TotalCargoMass:F2} т\n";
            report += $"Текущий {_currentTariff}\n";
            report += $"Общая выручка: {CalculateTotalRevenue():F2} {_currentTariff.Currency}\n";

            if (_shipments.Any())
            {
                report += "\nПоследние перевозки:\n";
                foreach (var shipment in _shipments.OrderByDescending(s => s.ShipmentDate).Take(5))
                {
                    report += $"  - {shipment}\n";
                }
            }

            return report;
        }

        // Вложенный класс для хранения информации о перевозке
        private class Shipment
        {
            public string CargoName { get; set; }
            public decimal CargoMass { get; set; } // в тоннах
            public DateTime ShipmentDate { get; set; }

            public override string ToString()
            {
                return $"{CargoName}: {CargoMass:F2} т ({ShipmentDate:dd.MM.yyyy})";
            }
        }
    }
}