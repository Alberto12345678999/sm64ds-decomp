#ifndef SM64DS_CSTD_H
#define SM64DS_CSTD_H

/* cstd -- the game's own runtime helpers: the division- and square-root-unit
 * routines (src/cstd.cpp, src/cstd_sqrt.cpp), atan2 (src/cstd_atan2.cpp), abs
 * (src/cstd4.cpp) and the string routines (src/cstd6.cpp). Each declaration is
 * spelled as its definition; return types are not part of the mangled name, so
 * they come from the bodies, not from the symbols. Parameters stay unnamed: a
 * name here takes an @NNN in every includer. */
namespace cstd {
int mod(int, int);
int div(int, int);
int fdiv(int, int);
long long ldiv(int, int);
int fdiv_result(void);
long long ldiv_result(void);
int sqrt(unsigned long long);
short atan2(int, int);
int abs(int);
unsigned int strlen(const char *);
char *strncpy(char *, const char *, unsigned int);
int strcmp(const char *, const char *);
char *strchr(const char *, char);
}

#endif
