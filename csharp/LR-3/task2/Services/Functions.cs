using System;

namespace Services
{
	public class Functions
	{
		public double ProcessFunctions(double c, double d, double k, double z)
		{
			double x;
			int branch;

			if (z < 0)
			{
				x = (z * z) - z;
				branch = 1;
			}
			else
			{
				x = z * z * z;
				branch = 2;
			}

			double arg = c * x + d * d + k * x * x;
			double sin = Math.Sin(arg);
			double result = Math.Pow(sin, 3);

			Console.WriteLine($"Branch number is {branch}");

			return result;
		}
	}
}