// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

using System.Text;

namespace Scintilla.Config;

public class ConfigParser
{
    public Dictionary<string, string> Parse(string filePath)
    {
        var configDictionary = new Dictionary<string, string>();
        var valueStringBuilder = new StringBuilder();
        var keyStringBuilder = new StringBuilder();
        var trimPattern = " \n\t";
        var lineNumber = 0;
        foreach (string line in File.ReadLines(filePath))
        {
            if (line.Length == 0 || line.Contains('#'))
            {
                lineNumber++;
                continue;
            }

            // Find equal operator and its index in the string
            int equalOperatorIndex = line.IndexOf('=');
            if (equalOperatorIndex == -1)
            {
                throw new Exception($"Failed to find an equal operator:\n\t {lineNumber} | {line}");
            }

            // Select sub-strings from the line, using equalOperatorIndex
            // as the bridge
            string keyName = line[0..equalOperatorIndex].ToString();
            string partialValue = line[(equalOperatorIndex + 1)..].ToString();

            // Store key and its value into the dictionary, along with trimming the strings.
            keyStringBuilder.Append(keyName);
            var finalKeyName = keyStringBuilder.ToString().Trim(trimPattern).ToString();
            valueStringBuilder.Append(partialValue);
            var finalValue = valueStringBuilder.ToString().Trim(trimPattern).ToString();

            configDictionary[finalKeyName] = finalValue;
            keyStringBuilder.Clear();
            valueStringBuilder.Clear();
        }
        return configDictionary;
    }
}

