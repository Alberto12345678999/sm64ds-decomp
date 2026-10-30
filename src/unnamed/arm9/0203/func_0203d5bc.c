/* A Vector2's squared length, in 64 bits and shifted down by 12
   (Vector2.h). */
long long func_0203d5bc(int *p)
{
    long long s = (long long)p[0] * p[0];
    s += (long long)p[1] * p[1];
    return s >> 12;
}
