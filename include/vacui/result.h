// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_RESULT_H
#define _VACUI_RESULT_H

// Generates a result struct with pre-added functions.
// The struct is named 'name'.
//
// This macro generator is used to reduce boilerplate code
// and provide standard interface for interactinig with result
// types.
//
// The form:
//
//      struct <name> <fields>;
//
//      static inline struct name <name>_ok <ok_body>
//      static inline struct name <name>_err <err_body>
//
// Example:
//      
//      VAC_RESULT_DEF(
//          foo_res, 
//          { 
//              int a;
//              int b;
//              bool ok; 
//          },
//          () { return (struct foo_res){ .a = 0, .b = 0, .ok = true }; },
//          () { return (struct foo_res){ .a = -1, .b = -1, .ok = false }; }
//      )
//
#define VAC_RESULT_DEF(name, fields, ok_body, err_body)                        \
    struct name fields;                                                        \
    static inline struct name name##_ok ok_body static inline struct name      \
        name##_err err_body

#endif

