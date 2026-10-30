extern void func_02073300(int a, int b, int c, int dtor);
extern void func_0203cbc0(void *ptr);

/* Has the shape of the Itanium C++ ABI's __cxa_vec_delete(array,
   element_size, padding_size, destructor). A null array does nothing.
   With a destructor, func_02073300 destroys the element count stored a
   word below the array (*(a - 4)). The block, starting padding bytes
   before the array, then goes to func_0203cbc0 (operator delete). */
void func_02073244(int a, int b, int c, int d)
{
    if (a == 0) return;
    if (d != 0)
        func_02073300(a, *(int*)(a - 4), b, d);
    func_0203cbc0((void *)(a - c));
}
