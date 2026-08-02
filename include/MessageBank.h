#ifndef MESSAGE_BANK_H
#define MESSAGE_BANK_H

#include "types.h"

/* Layout recovered from the five western msg_data_*.bin banks and runtime use. */
typedef struct MessageBankHeader {
    char magic[8];          /* "GSEM1gmb" */
    u32 fileSize;
    u32 sectionCount;
    u32 unk_10;
    u8 reserved_14[0x0c];
} MessageBankHeader;

typedef struct MessageInfoSection {
    char magic[4];          /* "1FNI" */
    u32 sectionSize;
    u16 messageCount;
    u16 unk_0a;
    u32 unk_0c;
} MessageInfoSection;

typedef struct MessageEntry {
    u32 textOffset;
    u8 info[4];
} MessageEntry;

typedef struct MessageDataSection {
    char magic[4];          /* "1TAD" */
    u32 sectionSize;
} MessageDataSection;

typedef char MessageBankHeader_SizeIs20[sizeof(MessageBankHeader) == 0x20 ? 1 : -1];
typedef char MessageInfoSection_SizeIs10[sizeof(MessageInfoSection) == 0x10 ? 1 : -1];
typedef char MessageEntry_SizeIs8[sizeof(MessageEntry) == 8 ? 1 : -1];
typedef char MessageDataSection_SizeIs8[sizeof(MessageDataSection) == 8 ? 1 : -1];

/* Readable aliases retain the current symbols and therefore their relocations. */
#define LoadMessageBankForLanguage   func_0201fe08
#define ParseMessageBankSections     func_0201cb2c
#define gMessageBankHeader           data_0209d6e8
#define gMessageDataSection          data_0209d6ec
#define gMessageBankBase             data_0209d6fc
#define gMessageEntries              data_0209d708
#define gMessageInfoSection          data_0209d70c

#define MESSAGE_BANK_ENG_ASSET   0x0431
#define MESSAGE_BANK_FRN_ASSET   0x0432
#define MESSAGE_BANK_GMN_ASSET   0x0433
#define MESSAGE_BANK_ITL_ASSET   0x0434
#define MESSAGE_BANK_SPN_ASSET   0x0435

#endif
