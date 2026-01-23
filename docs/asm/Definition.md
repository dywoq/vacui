`Vacui ASM` is an Assembly-like programming language interpreter.

Unlike other Assembly-like languages, `Vacui ASM` doesn't require memory management and has no fixed types. It ensures all objects are valid, therefore undefined behavior is impossible.

- File extensions: `.vasm`
# Program example

In this snippet of code, in `main` entry function, it defines two variables (`x` and `y`), initializes result with zero value and adds `x` and `y`. In the end of function, it returns result as the exit code.
```vasm
main () {
	mov x, 12;
	mov y, 63; 
	mov result, 0;
	add result, x, y;
	ret result;
}
```
