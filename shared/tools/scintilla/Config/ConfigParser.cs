// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

using System.Text;
using System.Text.RegularExpressions;

namespace Scintilla.Config;

/// <summary>
/// Class ConfigParser is responsible for parsing the configuration files,
/// and returning the dictionary map with parsed keys and values.
/// </summary>
public class ConfigParser
{
    private class StateManagement
    {
        public string FilePath { get; set; } = "UNKNOWN";

        public int CurrentLineNumber { get; set; }
        public string CurrentLine { get; set; } = "";

        public int EqualOperatorIndex { get; set; }

        public StringBuilder KeyStringBuilder { get; set; } = new();
        public StringBuilder ValueStringBuilder { get; set; } = new();

        public bool SkipLineLoop { get; set; } = false;
        public bool BreakLoop { get; set; } = false;

        public bool ParsingMultilineValue { get; set; } = false;

        public void Reset()
        {
            FilePath = "";
            CurrentLineNumber = 1;
            ResetStringBuilders();
            ResetLoopInfo();
        }

        public void ResetStringBuilders()
        {
            KeyStringBuilder.Clear();
            ValueStringBuilder.Clear();
        }

        public void ResetLoopInfo()
        {
            SkipLineLoop = false;
            BreakLoop = false;
        }

        public void ResetMultilineValueInfo()
        {
            ParsingMultilineValue = false;
        }
    }

    /// <summary>
    /// Method Parse converts the configuration file into the dictionary, with support of multi-line values,
    /// hash commentaries and expansion of config/environment variables.
    /// </summary>
    ///
    /// <param name="filePath">a file path.</param>
    /// 
    /// <exception cref="Exception"> 
    /// Thrown when:
    /// - the equal operator wasn't found (if not parsing multi-line value);
    /// - failed to find environment or config variable during a variable expansion;
    /// - failed to open file.
    /// </exception>
    public Dictionary<string, string> Parse(string filePath)
    {
        var configDictionary = new Dictionary<string, string>();
        var stateManagement = new StateManagement();
        foreach (string line in File.ReadLines(filePath))
        {
            stateManagement.CurrentLine = line;
            if (IsLineCommentOrEmpty_(ref stateManagement))
            {
                stateManagement.CurrentLineNumber++;
                continue;
            }

            HandleMultilineValue_(ref stateManagement, ref configDictionary);
            if (stateManagement.SkipLineLoop)
            {
                stateManagement.CurrentLineNumber++;
                stateManagement.SkipLineLoop = false;
                continue;
            }

            GetEqualOperatorIndex_(ref stateManagement);
            GetKeyAndValue_(ref stateManagement);
            TrimKeyAndValue_(ref stateManagement);

            SkipLineIfBackslashAtValueEnd_(ref stateManagement);
            if (stateManagement.SkipLineLoop)
            {
                stateManagement.CurrentLineNumber++;
                stateManagement.SkipLineLoop = false;
                continue;
            }

            StoreKeyAndValue_(ref stateManagement, ref configDictionary);
            stateManagement.ResetStringBuilders();
        }

        return configDictionary;
    }

    private bool IsLineCommentOrEmpty_(ref StateManagement stateManagement)
    {
        string trimmed = stateManagement.CurrentLine.Trim();
        return trimmed.Length == 0 || trimmed.StartsWith('#');
    }

    private void GetEqualOperatorIndex_(ref StateManagement stateManagement)
    {
        stateManagement.EqualOperatorIndex = stateManagement.CurrentLine.IndexOf('=');
        if (stateManagement.EqualOperatorIndex == -1)
        {
            throw new Exception(MakeError_(ref stateManagement, "Failed to find an equal operator"));
        }
    }

    private void GetKeyAndValue_(ref StateManagement stateManagement)
    {
        var key = stateManagement.CurrentLine[0..stateManagement.EqualOperatorIndex].ToString();
        var value = stateManagement.CurrentLine[(stateManagement.EqualOperatorIndex + 1)..].ToString();
        stateManagement.KeyStringBuilder.Append(key);
        stateManagement.ValueStringBuilder.Append(value);
    }

    private void TrimKeyAndValue_(ref StateManagement stateManagement)
    {
        string trimPattern = " \n\t";
        var trimmedKey = stateManagement.KeyStringBuilder.ToString().Trim(trimPattern);
        var trimmedValue = stateManagement.ValueStringBuilder.ToString().Trim(trimPattern);
        stateManagement.ResetStringBuilders();
        stateManagement.KeyStringBuilder.Append(trimmedKey);
        stateManagement.ValueStringBuilder.Append(trimmedValue);
    }

    private void SkipLineIfBackslashAtValueEnd_(ref StateManagement stateManagement)
    {
        var value = stateManagement.ValueStringBuilder.ToString();
        if (value.EndsWith('\\'))
        {
            stateManagement.SkipLineLoop = true;
            stateManagement.ParsingMultilineValue = true;
            var strippedBackslashValue = value.TrimEnd('\\').ToString();
            stateManagement.ValueStringBuilder.Clear();
            stateManagement.ValueStringBuilder.Append(strippedBackslashValue);
        }
    }

    private void HandleMultilineValue_(ref StateManagement stateManagement, ref Dictionary<string, string> configDictionary)
    {
        if (stateManagement.ParsingMultilineValue)
        {
            var trimmedLine = stateManagement.CurrentLine.Trim(" \n\t");
            if (!trimmedLine.EndsWith('\\'))
            {
                stateManagement.SkipLineLoop = true;
                stateManagement.ParsingMultilineValue = false;
                stateManagement.ValueStringBuilder.Append(' ');
                stateManagement.ValueStringBuilder.Append(trimmedLine);
                StoreKeyAndValue_(ref stateManagement, ref configDictionary);
                stateManagement.ResetStringBuilders();
                return;
            }
            else
            {
                stateManagement.SkipLineLoop = true;
                var strippedBackslashLine = trimmedLine.TrimEnd('\\').ToString();
                stateManagement.ValueStringBuilder.Append(' ');
                stateManagement.ValueStringBuilder.Append(strippedBackslashLine);
            }
        }
    }

    private void StoreKeyAndValue_(ref StateManagement stateManagement, ref Dictionary<string, string> configDictionary)
    {
        HandleVariableExpansionInValue_(ref stateManagement, ref configDictionary);
        var key = stateManagement.KeyStringBuilder.ToString();
        var value = stateManagement.ValueStringBuilder.ToString();
        configDictionary[key] = value;
    }

    private string MakeError_(ref StateManagement stateManagement, string errorMessage) =>
        $"{errorMessage}\n\t {stateManagement.CurrentLineNumber} | {stateManagement.CurrentLine}";

    private void HandleVariableExpansionInValue_(ref StateManagement stateManagement, ref Dictionary<string, string> configDictionary)
    {
        var value = stateManagement.ValueStringBuilder.ToString();
        var pattern = @"\$\{([^}]+)\}";
        var matches = Regex.Matches(value, pattern);
        for (int i = matches.Count - 1; i >= 0; i--)
        {
            var match = matches[i];
            string varName = match.Groups[1].Value;
            string resolvedValue;

            if (configDictionary.TryGetValue(varName, out string? localVal))
            {
                resolvedValue = localVal;
            }

            else
            {
                string? envVal = Environment.GetEnvironmentVariable(varName);
                if (envVal != null)
                {
                    resolvedValue = envVal;
                }
                else
                {
                    throw new Exception(MakeError_(ref stateManagement, $"Variable '{varName}' could not be resolved in local config or environment"));
                }
            }

            value = value.Remove(match.Index, match.Length).Insert(match.Index, resolvedValue);
        }

        stateManagement.ValueStringBuilder.Clear();
        stateManagement.ValueStringBuilder.Append(value);
    }
}

