The idea behind this small project is to put in practice some concurrency programming using C.

### f(x)

This function is the entry point (our main one). It basically calls two functions, `g(x)` and `h(x)`, and **both functions** should be called in separated processes by using the `fork()` system call.

### g(x)

This is called in our first child process, created by `f(x)`. This function should **not** call any extra `fork()`. We'll consider its calculation is simple enough to run in a single process.

### h(x)

This is called in our second child process, created by `f(x)`. This function should call two more functions, `i(x)` and `l(x)`. The `i(x)` should run in the same process, but a new process should be created for `l(x)` using `fork()`.

### i(x)

This is called in the same process as its caller, `h(x)`. We'll consider its calculation is simple enough to run in a single process.

### l(x)

This is called in our third child process, created by `h(x)`.

### Generic implementations for each function

```c
/* Main process (P1): */
f(x) = g(x) + h(x)

/* 1st child process (P2): */
g(x) = x!

/* 2nd child process (P3): */
h(x) = i(x) + l(x)

/* 3rd child process (P4): */
i(x) = x² / sqrt(x)

/* 4th child process (P5): */
l(x) = (x! - (x²)!) / sumatory(x, 1, i²)
```

