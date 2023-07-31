# \_\_VA_EXPAND\_\_

A c macro that expands \_\_VA_ARGS\_\_ no matter the length.

A Simple example, creating an `add` macro:
```c
#define add(...) ( __VA_EXPAND__((addn, addl), (__EMPTY__,), __VA_ARGS__) )
#define addn(arg, _) arg +
#define addl(arg, _) arg

add(1, 2, 3, 4) // expands to => ( 1 + 2 + 3 + 4 )
```

The first argument is `macros` which consists of a pair of macros. The first, which in this example is `addn`, is the macro that is called every time `__VA_EXPAND__` finds an argument that is NOT the last argument. The opposite is true for the second macro, or in this case `addl`, ONLY the last argument is passed in to this macro.

What this `add` macro does overall add a `+` token after every argument, except the last one so that there isn't a trailing `+` that will cause errors.

The second argument is state, which is not used in this example. It is instead replaced with `(__EMPTY__,)` basically not using that functionality. The first argument, which is `__EMPTY__` in this case, is a macro for changing state. Every argument, this macro is called with the current state and will return the mutated state. This state is the second argument of both macros in the first argument of `__VA_EXPAND__`, which in this case is ignored by using the `_`.

A way that you can use state is in a tuple-like struct definition. With a bunch of macros like this, you can start to create a changing state:
```c
#define next_letter(letter) next_letter_from_ ## letter

#define next_letter_from_a b
#define next_letter_from_b c
#define next_letter_from_c d
...
#define next_letter_from_y z
```

Although this is limited to the 26 characters in the alphabet, it's unlikely that you will need more than that in a tuple struct. We can create the rest of the tuple macro, which I will call `tup` like this:
```c
#define tup(...) struct { __VA_EXPAND__((tupn, tupn), (next_letter, a)) }
#define tupn(type, name) type name;

tup(int, char, int) // expands to => struct { int a; char b; int c; }
```

In this case, I use the same macro for both the arguments that are not the final ones, and the final one because I don't need to tell the difference. I wrap the whole `__VA_EXPAND__` call within a struct declaration and use the sate mutator to increment the letter everytime I parse a new argument.

## End of README

Thank you for reading into this project. If you have any questions or suggestions, feel free to open an issue. You can download the simple code for this macro in the [`va_expand.h`](./va_expand.h) file.

If you find this project useful, consider giving it a star on GitHub and sharing it with others who might benefit from it. Your support is greatly appreciated!

Happy coding! 🚀
