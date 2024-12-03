using System;
using System.Text;
using System.Collections.Generic;
 
namespace CalculatorApp
{
    class Program
    {
        static void Main(string[] args)
        {
            bool keepRunning = true;
 
            Console.WriteLine("Welcome to the Cagdas's Magical Calculator App!");
 
            while (keepRunning)
            {
                Console.WriteLine("\nChoose an operation:");
                Console.WriteLine("1. Addition (+)");
                Console.WriteLine("2. Subtraction (-)");
                Console.WriteLine("3. Multiplication (*)");
                Console.WriteLine("4. Division (/)");
                Console.WriteLine("5. Sorry I Want To Exit");
 
                Console.Write("Enter your choice (1-5): ");
                string choice = Console.ReadLine();
 
                if (choice == "5")
                {
                    keepRunning = false;
                    Console.WriteLine("You have choosed Exit. Goodbye!");
                    break;
                }
 
                Console.Write("Enter the first number: ");
                if (!double.TryParse(Console.ReadLine(), out double num1))
                {
                    Console.WriteLine("Please do not write letter here!");
                    continue;
                }
 
                Console.Write("Enter the second number: ");
                if (!double.TryParse(Console.ReadLine(), out double num2))
                {
                    Console.WriteLine("Please do not write letter here!");
                    continue;
                }
 
                switch (choice)
                {
                    case "1":
                        Console.WriteLine($"Result: {num1} + {num2} = {num1 + num2}");
                        break;
                    case "2":
                        Console.WriteLine($"Result: {num1} - {num2} = {num1 - num2}");
                        break;
                    case "3":
                        Console.WriteLine($"Result: {num1} * {num2} = {num1 * num2}");
                        break;
                    case "4":
                        if (num2 == 0)
                        {
                            Console.WriteLine("Error: Division by zero is not allowed. If you wanna learn more: https://www.youtube.com/shorts/O9JvaOQsJDM ");
                        }
                        else
                        {
                            Console.WriteLine($"Result: {num1} / {num2} = {num1 / num2}");
                        }
                        break;
                    default:
                        Console.WriteLine("Invalid choice. Please select a valid operation.");
                        break;
                }
            }
        }
    }
}
 