using System;

namespace ProcessingProgram
{
    public class ProcessingProgram
    {
        public int ProcessNumber(int number)
        {
            if (number % 2 == 0)
            {
                return number / 2;
            }
            else
            {
                return 0;
            }
        }
    }
}