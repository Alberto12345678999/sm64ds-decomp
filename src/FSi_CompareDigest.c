/* NitroSDK FS_overlay.c FSi_CompareDigest: HMAC the image with the digest
 * key (fsi_digest_key_ptr and fsi_digest_key_len, data_0209a04c and
 * data_0209a050) and compare the 20-byte result with spec_digest a word at a
 * time. */
void func_0205a588(void* p, int v, int n);
void CpuCopy8(int a, void* b, int c);
void DGT_Hash2CalcHmac(void* a, int b, int c, void* d, int e);

extern int data_0209a04c;
extern int data_0209a050;

int FSi_CompareDigest(char *spec_digest, int src, int len) {
    int digest[5];
    int digest_key[16];
    unsigned int i;
    int *p;
    func_0205a588(digest, 0, 0x14);
    CpuCopy8(data_0209a04c, digest_key, data_0209a050);
    DGT_Hash2CalcHmac(digest, src, len, digest_key, data_0209a050);
    p = digest;
    for (i = 0; i < 0x14; i += 4) {
        if (*p != *(int *)(spec_digest + i))
            break;
        p++;
    }
    return i == 0x14;
}
