#ifndef NNSYS_FND_H
#define NNSYS_FND_H

/*
 * NitroSystem foundation types, as the Sonic Rush Adventure decomp spells
 * them. Only the list link is needed so far (NNSSndSeqPlayer embeds two).
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

#ifdef __cplusplus
}
#endif

#endif
