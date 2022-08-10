- Resolve errors from *Build #41*:
```bash
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:42:34: error: expected expression before ‘;’ token
42 |   alloc_addr = SYS_MALLOC(amount);
|                                  ^
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c: In function ‘make_rame’:
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:165:67: error: expected expression before ‘;’ token
165 | static Rame *make_rame() { return (Rame *)SYS_MALLOC(sizeof(Rame)); }
|                                                                   ^
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c: In function ‘make_cherry’:
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:168:3: warning: ‘return’ with no value, in function returning non-void
168 |   return SYS_MALLOC(_cherry_size);
|   ^~~~~~
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:167:14: note: declared here
167 | static void *make_cherry(size_t _cherry_size) {
|              ^~~~~~~~~~~
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c: In function ‘pick_all_cherries’:
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:244:7: error: ‘system_free’ undeclared (first use in this function)
244 |   if (system_free == NULL) {
|       ^~~~~~~~~~~
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:244:7: note: each undeclared identifier is reported only once for each function it appears in
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:245:19: warning: implicit declaration of function ‘dlsym’ [-Wimplicit-function-declaration]
245 |     system_free = dlsym(RTLD_NEXT, "free");
|                   ^~~~~
/home/runner/work/cherryleaks/cherryleaks/cherry_leaks/cherry_leaks.c:245:25: error: ‘RTLD_NEXT’ undeclared (first use in this function)
245 |     system_free = dlsym(RTLD_NEXT, "free");
|                         ^~~~~~~~~
```
- Resolve **TODO's** in cherry_leaks/cherry_leaks.*
- Add Unittests for Rame functionality