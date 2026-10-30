#include "types.h"
#include "Ov007Work.h"

/* func_ov007_020b7138's second argument: dScDSMT_c's byte-packed
 * download-play table (data_0209b340), whose first word holds the boot
 * flags; func_ov007_020cc168 fills one save file's entries. Only the slots
 * this file reads. */
typedef struct Ov007BootArgs {
    char pad_00[0xb];
    /* 0x0b: flags1 bit 0 of the loaded save file */
    u8 fileUsed[3];
    char pad_0e[3];
    /* 0x11: per course, the displayed star count less star 0 */
    u8 otherStars[3][15];
    char pad_3e[45];     /* 0x3e: per-course coin records */
    u8 firstStar[3][15]; /* 0x6b: per course, star 0 collected */
    u8 level1dStars[3];  /* 0x98: the displayed star count of level 0x1d */
} Ov007BootArgs;

/* The 0x3c-byte record func_ov007_020b6a84 allocates; only the slots this
 * file touches. */
typedef struct Ov007Settings {
    Ov007BootArgs *bootArgs; /* 0x00 */
    /* 0x04: per save file, its star total, -1 for an unused file */
    s16 starCounts[3];
} Ov007Settings;

extern char *data_ov007_0210342c;
/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Totals each save file's stars from the boot-args table: every course's
 * stars plus level 0x1d's. */
void func_ov007_020aec00(void) {
    Ov007Settings *settings;
    int i;
    int sum;
    int k;
    i = 0;
    settings = WORK->settings;
    for (; i < 3; i++) {
        Ov007BootArgs *s = settings->bootArgs;
        sum = 0;
        if (s->fileUsed[i] != 0) {
            for (k = 0; k < 15; k++) {
                sum += s->otherStars[i][k];
                sum += s->firstStar[i][k];
            }
            sum += s->level1dStars[i];
        } else {
            sum = -1;
        }
        settings->starCounts[i] = sum;
    }
}
