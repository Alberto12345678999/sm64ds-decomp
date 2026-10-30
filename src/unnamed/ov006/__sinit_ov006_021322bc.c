/* ov006 static initializer at 0x021322bc (0x5d8): the Roulette board's
 * thirty-seven tile centres (sRouletteTiles, stride 8, fx32 x and y), each
 * built in place and registered with the shared empty destructor
 * NullDestructor_0203d47c through its own 12-byte node (data_ov006_0214xxxx).
 *
 * Not folded: its owner is d_s_mg_roulette_methods.cpp, but the nodes in
 * 0x021428c8..0x02142bdc interleave with that TU's sRouletteLandedRacer,
 * sRouletteResultsTimer and the function-local sRouletteRacerGoal (guard,
 * object and node), so compiler emission needs all of them defined together.
 * Every element after the first is stored through a volatile pointer; that
 * is the shape that matched.
 */

/* local extern: no C header declares the registration helper. */
extern void __register_global_object(void *object, void *dtor, void **node);
extern void NullDestructor_0203d47c(void);

/* One tile centre, x and y: d_s_mg_roulette_methods.cpp's TileXY. */
typedef struct TileXY {
    int x, y;
} TileXY;

extern TileXY sRouletteTiles;
extern void *data_ov006_021429a8[3];
extern TileXY data_ov006_02142abc;
extern void *data_ov006_021429c0[3];
extern TileXY data_ov006_02142ac4;
extern void *data_ov006_021429fc[3];
extern TileXY data_ov006_02142acc;
extern void *data_ov006_021429f0[3];
extern TileXY data_ov006_02142ad4;
extern void *data_ov006_02142990[3];
extern TileXY data_ov006_02142adc;
extern void *data_ov006_02142a08[3];
extern TileXY data_ov006_02142ae4;
extern void *data_ov006_02142a14[3];
extern TileXY data_ov006_02142aec;
extern void *data_ov006_02142a20[3];
extern TileXY data_ov006_02142af4;
extern void *data_ov006_021428dc[3];
extern TileXY data_ov006_02142afc;
extern void *data_ov006_02142a38[3];
extern TileXY data_ov006_02142b04;
extern void *data_ov006_02142a50[3];
extern TileXY data_ov006_02142b0c;
extern void *data_ov006_02142a68[3];
extern TileXY data_ov006_02142b14;
extern void *data_ov006_02142a80[3];
extern TileXY data_ov006_02142b1c;
extern void *data_ov006_02142a98[3];
extern TileXY data_ov006_02142b24;
extern void *data_ov006_02142a8c[3];
extern TileXY data_ov006_02142b2c;
extern void *data_ov006_0214293c[3];
extern TileXY data_ov006_02142b34;
extern void *data_ov006_02142a74[3];
extern TileXY data_ov006_02142b3c;
extern void *data_ov006_02142930[3];
extern TileXY data_ov006_02142b44;
extern void *data_ov006_02142a5c[3];
extern TileXY data_ov006_02142b4c;
extern void *data_ov006_02142924[3];
extern TileXY data_ov006_02142b54;
extern void *data_ov006_02142a44[3];
extern TileXY data_ov006_02142b5c;
extern void *data_ov006_02142918[3];
extern TileXY data_ov006_02142b64;
extern void *data_ov006_02142a2c[3];
extern TileXY data_ov006_02142b6c;
extern void *data_ov006_0214290c[3];
extern TileXY data_ov006_02142b74;
extern void *data_ov006_021428e8[3];
extern TileXY data_ov006_02142b7c;
extern void *data_ov006_021428f4[3];
extern TileXY data_ov006_02142b84;
extern void *data_ov006_02142900[3];
extern TileXY data_ov006_02142b8c;
extern void *data_ov006_02142954[3];
extern TileXY data_ov006_02142b94;
extern void *data_ov006_021429e4[3];
extern TileXY data_ov006_02142b9c;
extern void *data_ov006_021429d8[3];
extern TileXY data_ov006_02142ba4;
extern void *data_ov006_021429cc[3];
extern TileXY data_ov006_02142bac;
extern void *data_ov006_02142960[3];
extern TileXY data_ov006_02142bb4;
extern void *data_ov006_021429b4[3];
extern TileXY data_ov006_02142bbc;
extern void *data_ov006_0214296c[3];
extern TileXY data_ov006_02142bc4;
extern void *data_ov006_02142978[3];
extern TileXY data_ov006_02142bcc;
extern void *data_ov006_02142984[3];
extern TileXY data_ov006_02142bd4;
extern void *data_ov006_0214299c[3];

void __sinit_ov006_021322bc(void) {
    sRouletteTiles.x = 0x70000;
    sRouletteTiles.y = 0x24000;
    __register_global_object(&sRouletteTiles, (void *)&NullDestructor_0203d47c, data_ov006_021429a8);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142abc;
        p->x = 0xa0000;
        p->y = 0x24000;
    }
    __register_global_object(&data_ov006_02142abc, (void *)&NullDestructor_0203d47c, data_ov006_021429c0);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142ac4;
        p->x = 0xd0000;
        p->y = 0x24000;
    }
    __register_global_object(&data_ov006_02142ac4, (void *)&NullDestructor_0203d47c, data_ov006_021429fc);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142acc;
        p->x = 0x70000;
        p->y = 0x4c000;
    }
    __register_global_object(&data_ov006_02142acc, (void *)&NullDestructor_0203d47c, data_ov006_021429f0);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142ad4;
        p->x = 0xa0000;
        p->y = 0x4c000;
    }
    __register_global_object(&data_ov006_02142ad4, (void *)&NullDestructor_0203d47c, data_ov006_02142990);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142adc;
        p->x = 0xd0000;
        p->y = 0x4c000;
    }
    __register_global_object(&data_ov006_02142adc, (void *)&NullDestructor_0203d47c, data_ov006_02142a08);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142ae4;
        p->x = 0x70000;
        p->y = 0x74000;
    }
    __register_global_object(&data_ov006_02142ae4, (void *)&NullDestructor_0203d47c, data_ov006_02142a14);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142aec;
        p->x = 0xa0000;
        p->y = 0x74000;
    }
    __register_global_object(&data_ov006_02142aec, (void *)&NullDestructor_0203d47c, data_ov006_02142a20);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142af4;
        p->x = 0xd0000;
        p->y = 0x74000;
    }
    __register_global_object(&data_ov006_02142af4, (void *)&NullDestructor_0203d47c, data_ov006_021428dc);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142afc;
        p->x = 0x70000;
        p->y = 0x9c000;
    }
    __register_global_object(&data_ov006_02142afc, (void *)&NullDestructor_0203d47c, data_ov006_02142a38);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b04;
        p->x = 0xa0000;
        p->y = 0x9c000;
    }
    __register_global_object(&data_ov006_02142b04, (void *)&NullDestructor_0203d47c, data_ov006_02142a50);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b0c;
        p->x = 0xd0000;
        p->y = 0x9c000;
    }
    __register_global_object(&data_ov006_02142b0c, (void *)&NullDestructor_0203d47c, data_ov006_02142a68);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b14;
        p->x = 0x88000;
        p->y = 0x24000;
    }
    __register_global_object(&data_ov006_02142b14, (void *)&NullDestructor_0203d47c, data_ov006_02142a80);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b1c;
        p->x = 0xb8000;
        p->y = 0x24000;
    }
    __register_global_object(&data_ov006_02142b1c, (void *)&NullDestructor_0203d47c, data_ov006_02142a98);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b24;
        p->x = 0x88000;
        p->y = 0x4c000;
    }
    __register_global_object(&data_ov006_02142b24, (void *)&NullDestructor_0203d47c, data_ov006_02142a8c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b2c;
        p->x = 0xb8000;
        p->y = 0x4c000;
    }
    __register_global_object(&data_ov006_02142b2c, (void *)&NullDestructor_0203d47c, data_ov006_0214293c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b34;
        p->x = 0x88000;
        p->y = 0x74000;
    }
    __register_global_object(&data_ov006_02142b34, (void *)&NullDestructor_0203d47c, data_ov006_02142a74);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b3c;
        p->x = 0xb8000;
        p->y = 0x74000;
    }
    __register_global_object(&data_ov006_02142b3c, (void *)&NullDestructor_0203d47c, data_ov006_02142930);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b44;
        p->x = 0x88000;
        p->y = 0x9c000;
    }
    __register_global_object(&data_ov006_02142b44, (void *)&NullDestructor_0203d47c, data_ov006_02142a5c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b4c;
        p->x = 0xb8000;
        p->y = 0x9c000;
    }
    __register_global_object(&data_ov006_02142b4c, (void *)&NullDestructor_0203d47c, data_ov006_02142924);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b54;
        p->x = 0x70000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142b54, (void *)&NullDestructor_0203d47c, data_ov006_02142a44);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b5c;
        p->x = 0xa0000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142b5c, (void *)&NullDestructor_0203d47c, data_ov006_02142918);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b64;
        p->x = 0xd0000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142b64, (void *)&NullDestructor_0203d47c, data_ov006_02142a2c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b6c;
        p->x = 0x70000;
        p->y = 0x60000;
    }
    __register_global_object(&data_ov006_02142b6c, (void *)&NullDestructor_0203d47c, data_ov006_0214290c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b74;
        p->x = 0xa0000;
        p->y = 0x60000;
    }
    __register_global_object(&data_ov006_02142b74, (void *)&NullDestructor_0203d47c, data_ov006_021428e8);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b7c;
        p->x = 0xd0000;
        p->y = 0x60000;
    }
    __register_global_object(&data_ov006_02142b7c, (void *)&NullDestructor_0203d47c, data_ov006_021428f4);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b84;
        p->x = 0x70000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142b84, (void *)&NullDestructor_0203d47c, data_ov006_02142900);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b8c;
        p->x = 0xa0000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142b8c, (void *)&NullDestructor_0203d47c, data_ov006_02142954);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b94;
        p->x = 0xd0000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142b94, (void *)&NullDestructor_0203d47c, data_ov006_021429e4);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142b9c;
        p->x = 0x88000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142b9c, (void *)&NullDestructor_0203d47c, data_ov006_021429d8);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142ba4;
        p->x = 0xb8000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142ba4, (void *)&NullDestructor_0203d47c, data_ov006_021429cc);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bac;
        p->x = 0x88000;
        p->y = 0x60000;
    }
    __register_global_object(&data_ov006_02142bac, (void *)&NullDestructor_0203d47c, data_ov006_02142960);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bb4;
        p->x = 0xb8000;
        p->y = 0x60000;
    }
    __register_global_object(&data_ov006_02142bb4, (void *)&NullDestructor_0203d47c, data_ov006_021429b4);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bbc;
        p->x = 0x88000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142bbc, (void *)&NullDestructor_0203d47c, data_ov006_0214296c);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bc4;
        p->x = 0xb8000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142bc4, (void *)&NullDestructor_0203d47c, data_ov006_02142978);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bcc;
        p->x = 0x38000;
        p->y = 0x38000;
    }
    __register_global_object(&data_ov006_02142bcc, (void *)&NullDestructor_0203d47c, data_ov006_02142984);
    {
        volatile TileXY *p = (volatile TileXY *)&data_ov006_02142bd4;
        p->x = 0x38000;
        p->y = 0x88000;
    }
    __register_global_object(&data_ov006_02142bd4, (void *)&NullDestructor_0203d47c, data_ov006_0214299c);
}
