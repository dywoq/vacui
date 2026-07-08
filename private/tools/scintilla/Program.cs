// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

using Scintilla.Config;

public class Program
{
    static void Main()
    {
        var configParser = new ConfigParser();
        try
        {
            var dictionary = configParser.Parse("scintilla.conf");
            foreach (var (key, keyValue) in dictionary)
            {
                Console.WriteLine($"dictionary[\"{key}\"]=\"{keyValue}\"");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"exception caught: {ex.Message}");
        }
    }
}
