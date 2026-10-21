extern void func_ov007_020c421c(int x);

/* data_ov007_0210342c: the overlay's manager; only the slots this function
 * reads. */
typedef struct Ov007Work {
    char pad_00[0x108];
    /* 0x108: the three full-screen Ov007Sprite quads func_ov007_020b2998
     * builds (centred on 128,96, 0x100 square): [0] a corner-colour fill,
     * [1] textured, [2] plain white; func_ov007_020b2764 recolours [0] and
     * [1]. Drawn here through func_ov007_020c421c. */
    int screenSprites[3];
} Ov007Work;

extern int* data_ov007_0210342c;
/* The extern keeps the tree's int * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b2728(void){
  int i;
  for(i=0;i<3;i++){
    func_ov007_020c421c(WORK->screenSprites[i]);
  }
}
