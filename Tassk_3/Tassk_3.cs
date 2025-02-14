using System;
using System.Collections.Generic;
using System.Text;

namespace Tassk_3
{
    class RPN
    {
        static public double Calculate(string input)
        {
            string output = GetExpression(input);
            Console.WriteLine($"Reverse Polish Notation: {output}");
            double result = Counting(output);
            return result;
        }

        static public string GetExpression(string input)
        {
            input = input.Replace(" ", "");
            input = input.Replace("sqrt", "√");
            string output = string.Empty;
            Stack<char> operStack = new Stack<char>();
            for (int i = 0; i < input.Length; i++)
            {
                if (IsDelimeter(input[i]))
                    continue;
                if (input[i] == '-' && ((i > 0 && !Char.IsDigit(input[i - 1])) || i == 0))
                {
                    i++;
                    output += "-";
                }
                if (Char.IsDigit(input[i]))
                {
                    while (!IsDelimeter(input[i]) && !IsOperator(input[i]))
                    {
                        output += input[i];
                        i++;
                        if (i == input.Length) break;
                    }
                    output += " ";
                    i--;
                }
                if (IsOperator(input[i]))
                {
                    if (input[i] == '(')
                        operStack.Push(input[i]);
                    else if (input[i] == ')')
                    {
                        char s = operStack.Pop();

                        while (s != '(')
                        {
                            output += s.ToString() + ' ';

                            s = operStack.Pop();
                        }
                    }
                    else
                    {
                        if (operStack.Count > 0)
                            if (GetPriority(input[i]) <= GetPriority(operStack.Peek()))
                                output += operStack.Pop().ToString() + " ";

                        operStack.Push(char.Parse(input[i].ToString()));
                    }
                }
            }
            while (operStack.Count > 0)
                output += operStack.Pop() + " ";
            return output;
        }

        public static double Counting(string output)
        {
            string result;
            string[] mas = output.Split(" ".ToCharArray());
            for (int i = 0; i < mas.Length; i++)
                switch (mas[i])
                {
                    case "+":
                        result = (double.Parse(mas[i - 2]) + double.Parse(mas[i - 1])).ToString();
                        mas[i - 2] = result;
                        for (int j = i - 1; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 2];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 2;
                        break;
                    case "-":
                        result = (double.Parse(mas[i - 2]) - double.Parse(mas[i - 1])).ToString();
                        mas[i - 2] = result;
                        for (int j = i - 1; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 2];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 2;
                        break;
                    case "*":
                        result = (double.Parse(mas[i - 2]) * double.Parse(mas[i - 1])).ToString();
                        mas[i - 2] = result;
                        for (int j = i - 1; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 2];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 2;
                        break;
                    case "/":
                        result = (double.Parse(mas[i - 2]) / double.Parse(mas[i - 1])).ToString();
                        mas[i - 2] = result;
                        for (int j = i - 1; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 2];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 2;
                        break;
                    case "^":
                        result = (Math.Pow(double.Parse(mas[i - 2]), double.Parse(mas[i - 1]))).ToString();
                        mas[i - 2] = result;
                        for (int j = i - 1; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 2];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 2;
                        break;
                    case "√":
                        result = (Math.Sqrt(double.Parse(mas[i - 1]))).ToString();
                        mas[i - 1] = result;
                        for (int j = i; j < mas.Length - 2; j++)
                            mas[j] = mas[j + 1];
                        Array.Resize(ref mas, mas.Length - 2);
                        i -= 1;
                        break;
                }
            return double.Parse(mas[0]);
        }

        static private byte GetPriority(char s)
        {
            switch (s)
            {
                case '(': return 0;
                case ')': return 1;
                case '+': return 2;
                case '-': return 3;
                case '*': return 4;
                case '/': return 4;
                case '^': return 5;
                case '√': return 6;
                default: return 7;
            }
        }

        static private bool IsOperator(char с)
        {
            if (("+-/*^()√".IndexOf(с) != -1))
                return true;
            return false;
        }

        static private bool IsDelimeter(char c)
        {
            if ((" =".IndexOf(c) != -1))
                return true;
            return false;
        }
    }

    class Tassk_3
    {
        static void Main(string[] args)
        {
            System.Globalization.CultureInfo customCulture = (System.Globalization.CultureInfo)System.Threading.Thread.CurrentThread.CurrentCulture.Clone();
            customCulture.NumberFormat.NumberDecimalSeparator = ".";
            System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;
            Console.OutputEncoding = Encoding.Unicode;
            Console.InputEncoding = Encoding.Unicode;
            Console.WriteLine("Enter the expression: ");
            string expression = Console.ReadLine();
            double result = RPN.Calculate(expression);
            Console.WriteLine("Result: " + result);
            Console.ReadKey();
        }
    }
}