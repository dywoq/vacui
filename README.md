# Vacui

Vacui is a simple Assembly interpreter, written in Go.

# Example

Here, you can see a "Hello, world!" example in Vacui:

```vac
main {
  # Perform system call (1 = print)
  push "Hello, world!"
  sys 1

  # Return
  ret 0
}
```

# Copyright

MIT License 2.0
