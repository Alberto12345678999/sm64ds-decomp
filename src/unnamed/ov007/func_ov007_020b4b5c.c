#include "Ov007Sprite.h"

extern void func_ov007_020c43bc(void *p, void *q);
extern void func_ov007_020c4388(char *r0, int r1);

/* The 10-byte layout row func_ov007_020aea6c's item points at; names as in
 * func_ov007_020b5bf0, only the slots this file reads. */
typedef struct Ov007ItemLayout {
  u16 kind;  /* 0x0 */
  s16 homeX; /* 0x2: func_ov007_020ae810 seeds the item position from home */
  s16 homeY; /* 0x4 */
} Ov007ItemLayout;

/* The 0x2c-byte record func_ov007_020aea6c allocates; names as in
 * func_ov007_020b5bf0, only the slot this file reads. */
typedef struct Ov007Item {
  char pad_00[0x24];
  Ov007ItemLayout *layout; /* 0x24 */
} Ov007Item;

/* One of the manager's itemViews (func_ov007_020b4c04); names as there. */
typedef struct Ov007ItemView {
  Ov007Item *item;     /* 0x00 */
  Ov007Sprite *sprite; /* 0x04: func_ov007_020c44e4 */
} Ov007ItemView;

/* Resets the view's sprite to unit scale, full alpha and white, sizes it
 * for camera `arg` (func_ov007_020c43bc), puts it at the item's home point
 * and places it in the world (func_ov007_020c4388). c keeps the char *
 * spelling of the definition; `view` is the typed view. */
void func_ov007_020b4b5c(char *c, int arg){
  Ov007ItemView *view = (Ov007ItemView *)c;
  Ov007Sprite *o = view->sprite;
  int t;
  o->scaleY = 0x1000;
  o->scaleX = o->scaleY;
  func_ov007_020c43bc(o, (void *)arg);
  o->alpha = 0x1f000;
  o->color = 0x7fff;
  o->screenX = view->item->layout->homeX << 0xc;
  o->screenY = view->item->layout->homeY << 0xc;
  (void)t;
  func_ov007_020c4388((char *)o, arg);
}
