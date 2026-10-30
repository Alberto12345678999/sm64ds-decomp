extern int data_0209e650;
extern int data_0209e654;
extern void func_0201973c(void);

extern void func_0203b9b4(int *p, int v);
extern void __register_global_object(void *object, void *destructor, void **node);

void __sinit_02074e44(void) {
    func_0203b9b4(&data_0209e650, 1);
    __register_global_object(&data_0209e650, (void *)&func_0201973c, (void **)&data_0209e654);
}
