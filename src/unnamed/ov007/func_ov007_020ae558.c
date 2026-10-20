#include "types.h"
#include "Ov007MenuState.h"
extern u8 data_ov007_0210342c[];
extern void Sprite_SetAnimation(char *c, int r1, int r2, int r3, int sp0);

/* *self: the 0x2c-byte func_ov007_020aea6c record; only its +4 Ov007MenuState has a header. */
int func_ov007_020ae558(char *self)
{
    int *g = *(int**)data_ov007_0210342c;
    Ov007MenuState *b = *(Ov007MenuState **)((char *)g + 0xc);
    int flag = b->stateTicks;
    int *a = *(int**)self;
    int sel = b->currentState;
    int *r3ptr = *(int**)((char*)a + 0x24);
    int r6 = (flag == 0);
    Ov007MenuState *c = *(Ov007MenuState **)((char *)a + 4);
    int lr_v = *(u16*)r3ptr;
    int ip_v = *(u16*)a;
    int r3_v = c->currentState;
    int ret = c->requestedState;

    switch (sel) {
    case 0:  if (r6) ret = 1; break;
    case 1:  if (r6) { if (ip_v == 1) Sprite_SetAnimation(*(char**)(self + 4), 0, 0, 0, 0); } break;
    case 3:  if (r6) { if (lr_v == 1) ret = 7; else if (ip_v == 7) ret = 1; } break;
    case 2:  if (r6) { if (lr_v == 1) { if (ip_v != 2) ret = 4; } } break;
    case 4:  if (r6) { if (lr_v == 1) ret = 7; } break;
    case 5:  if (r6) { if (lr_v == 1) ret = 7; } break;
    case 7:  if (r6) { if (lr_v == 1) ret = 3; } break;
    case 6:  if (r6) { if (lr_v == 1) ret = 4; } break;
    case 8:
        if (r6) {
            short d = b->previousState;
            int t = (d == 1 || d == 3);
            if (lr_v == 1) {
                if (t) {
                    if (ip_v != 2) { ret = 0; if (ip_v == 1) Sprite_SetAnimation(*(char**)(self + 4), 4, 0, 0, 0); }
                    else ret = 1;
                } else ret = 7;
            } else if (lr_v == 5) {
                ret = 0;
                Sprite_SetAnimation(*(char**)(self + 4), 0, 1, 0, 0);
            } else ret = 1;
        }
        break;
    case 9: case 10: case 13: if (r6) { if (lr_v == 1) ret = 7; } break;
    case 11: if (lr_v == 1) { if (r6) ret = 4; } break;
    case 12:
        if (lr_v == 1) {
            if (r6) ret = 7;
            else {
                int *g2 = *(int * volatile *)data_ov007_0210342c;
                short v = (*(Ov007MenuState **)((char *)g2 + 8))->currentState;
                u8 flag2 = *(u8*)((char*)*(int**)((char*)*(int**)((char*)g2 + 0xa8) + 4) + 0x1d);
                int x;
                if (v != 7) break;
                if (r3_v != 0) break;
                x = *(int*)((char*)g + 0x58);
                if ((x != -1 && flag2 == 7) || (x == -1 && flag2 == 8))
                    ret = 7;
            }
        }
        break;
    case 14: if (r6) { if (lr_v == 1) ret = 7; else if (ip_v == 7) ret = 0; } break;
    }
    return ret;
}
