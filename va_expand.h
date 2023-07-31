#ifndef __VA_EXPAND_H__
#define __VA_EXPAND_H__

#define __EVAL__(...) __EVAL1__(__EVAL1__(__EVAL1__(__EVAL1__(__EVAL1__(__VA_ARGS__)))))
#define __EVAL1__(...) __EVAL2__(__EVAL2__(__EVAL2__(__EVAL2__(__EVAL2__(__VA_ARGS__)))))
#define __EVAL2__(...) __EVAL3__(__EVAL3__(__EVAL3__(__EVAL3__(__EVAL3__(__VA_ARGS__)))))
#define __EVAL3__(...) __VA_ARGS__

#define __EMPTY__(...)
#define __DEFER__(id) id __EMPTY__()

#define __VA_GRAB_A__(a, ...) a
#define __VA_GRAB_B__(a, b, ...) b

#define __VA_ENDING_FALSE__(a, b, c, ...) __VA_GRAB_A__ a(c, __VA_GRAB_B__ b) __DEFER__(__VA_EXPAND_IND__)()(a, (__VA_GRAB_A__ b, __VA_GRAB_A__ b(__VA_GRAB_B__ b)), __VA_ARGS__)
#define __VA_ENDING_TRUE__(a, b, c, ...) __VA_GRAB_B__ a(c, __VA_GRAB_B__ b)
#define __VA_ENDING__(a, b, ...) __VA_ENDING_ ## b
#define __VA_ENDING_INT__(...) __VA_ENDING__(__VA_ARGS__, FALSE__)

#define __VA_CHECK_END__(a, b, c, d, ...) __VA_ENDING_INT__(__VA_CHECK_END_ ## d)(a, b, c, d, __VA_ARGS__)
#define __VA_CHECK_END_TRUE__ , TRUE__

#define __VA_EXPAND_INT__(...) __VA_CHECK_END__(__VA_ARGS__, TRUE__)
#define __VA_EXPAND_IND__() __VA_EXPAND_INT__
#define __VA_EXPAND__(macros, state, ...) __EVAL__(__VA_EXPAND_INT__(macros, state, __VA_ARGS__))

#endif
