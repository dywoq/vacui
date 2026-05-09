// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_RESULT_H
#define _VACUI_RESULT_H

#define RESULT_DEF(name, body, ok_body, err_body)                           \
  struct name               body;                                              \
  inline static struct name name##_ok ok_body;                                 \
  inline static struct name name##_err err_body;

#endif
