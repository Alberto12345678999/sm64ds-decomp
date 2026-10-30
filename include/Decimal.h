#ifndef DECIMAL_H
#define DECIMAL_H

/* The Decimal type behind __dorounddecup (increment) and its family:
   __timesdec (multiply), __str2dec (build from a digit string) and
   __rounddec (truncate/round). Those four either define or declare
   __dorounddecup, and this header is the one spelling all four now use for its
   first parameter. Before it, __timesdec carried this exact layout as a
   file-scope copy while __str2dec and __rounddec carried flattened
   partial views of the same bytes (`struct S`, `struct T`), which is what made
   their declarations of __dorounddecup disagree with its definition.
   __two_exp, __must_round and printf.c's round_decimal take it as well.

   __ull2dec (build from an unsigned long long) keeps its own identical
   local copy on purpose: it never names __dorounddecup, so no declaration there
   is made coherent by sharing the type, and folding it in would put a fifth
   byte-verified function in this slice for no interface gain.

   DELIBERATELY DEPENDENCY-FREE, mirroring OamAttr.h: every field is a raw C
   type (unsigned char, char, short), never a project typedef, so this header
   needs no #include and cannot collide with a file-scope typedef any of its
   includers carries. */

typedef struct Decimal
{
  unsigned char sign;
  char unused;
  short exp;
  struct
  {
    unsigned char length;
    unsigned char text[32];
    unsigned char unused;
  } sig;
} Decimal;

#endif
