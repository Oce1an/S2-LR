using System;
using System.Globalization;

namespace DateLibrary
{
    public class DateService
    {
        public string GetDay(string date)
        {
            DateTime parsedDate;

            string[] formats = { "yyyy-MM-dd", "dd.MM.yyyy", "dd/MM/yyyy", "MM/dd/yyyy" };

            if (DateTime.TryParseExact(date, formats, CultureInfo.InvariantCulture,
                DateTimeStyles.None, out parsedDate))
            {
                return parsedDate.ToString("dddd", new CultureInfo("ru-RU"));
            }
            else if (DateTime.TryParse(date, out parsedDate))
            {
                return parsedDate.ToString("dddd", new CultureInfo("ru-RU"));
            }
            else
            {
                return "Invalid date format.";
            }
        }
        public int GetDaysSpan(int day, int month, int year)
        {
            try
            {
                DateTime targetDate = new DateTime(year, month, day);
                DateTime currentDate = DateTime.Now.Date;

                TimeSpan difference = targetDate - currentDate;
                return difference.Days;
            }
            catch (ArgumentOutOfRangeException)
            {
                throw new ArgumentException("Incorrect date.");
            }
        }
    }
}