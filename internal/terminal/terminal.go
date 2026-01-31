// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

// Package terminal defines functions for logging, but with prefixes and colors.
package terminal

import (
	"fmt"

	"github.com/fatih/color"
)

// Error prints a message with colored ERROR prefix.
func Error(v ...any) { fmt.Printf("%s %s", color.RedString("[ERROR]"), fmt.Sprint(v...)) }

// Errorln prints a message with newline, and colored ERROR prefix.
func Errorln(v ...any) { Error(fmt.Sprintln(v...)) }

// Errorf returns a formatted message with colored ERROR prefix.
func Errorf(format string, v ...any) { Error(fmt.Sprintf(format, v...)) }

// Warn prints a message with colored WARN prefix.
func Warn(v ...any) { fmt.Printf("%s %s", color.YellowString("[WARN]"), fmt.Sprint(v...)) }

// Warnln prints a message with newline, and colored WARN prefix.
func Warnln(v ...any) { Warn(fmt.Sprintln(v...)) }

// Warnf returns a formatted message with colored WARN prefix.
func Warnf(format string, v ...any) { Warn(fmt.Sprintf(format, v...)) }

// Info prints a message with colored INFO prefix.
func Info(v ...any) { fmt.Printf("%s %s", color.GreenString("[INFO]"), fmt.Sprint(v...)) }

// Infoln prints a message with newline, and colored INFO prefix.
func Infoln(v ...any) { Info(fmt.Sprintln(v...)) }

// Infof returns a formatted message with colored INFO prefix.
func Infof(format string, v ...any) { Info(fmt.Sprintf(format, v...)) }
