using System;

enum OrderStatus {New, Processing, Shipped, Cancelled}

class Program
{
	static void Main()
	{
		OrderStatus myOrder = OrderStatus.New;

		switch (myOrder)
		{
			case OrderStatus.New:
				Console.WriteLine("Заказ ожидает обработки.");
				break;
			case OrderStatus.Shipped:
				Console.WriteLine("Заказ уже в пути!");
				break;
		}

		Console.WriteLine((int)myOrder);      // 0
		Console.WriteLine(myOrder.ToString()); // "New"
	}
}