#ifndef SM64DS_CSTD_H
#define SM64DS_CSTD_H

/* cstd -- the division-unit routines defined in src/cstd.cpp. Only fdiv
 * (20.12 fixed-point divide) is declared so far. Parameters stay unnamed: a
 * name here takes an @NNN in every includer. */
namespace cstd {
int fdiv(int, int);
}

#endif
