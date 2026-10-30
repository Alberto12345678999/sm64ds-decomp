struct S72d90 {
    int pad[2];
    unsigned char *p;
};

/* EH runtime: the current action's opcode, the low 5 bits of the byte at
   the iterator's action pointer, or 0 when there is none. The handler
   search (func_02071d3c) and the rethrow (func_02072014) switch on it. */
unsigned char func_02072d90(struct S72d90 *c)
{
    unsigned char *p = c->p;
    int r;
    if (p)
        r = p[0] & 0x1f;
    else
        r = 0;
    return (unsigned char)r;
}
