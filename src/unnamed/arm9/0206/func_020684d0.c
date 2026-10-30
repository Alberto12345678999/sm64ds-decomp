struct Node { char pad[0x4b4]; struct Node* next; };
extern struct Node* data_020a9d2c;

/* Append a game record to the beacon list whose head is the send status's
   first word (data_020a9d2c). Records chain through their last word, +0x4b4
   of the 0x4b8-byte MBGameInfo, and the new one ends the list.
   func_02067928 adds each registered file's record this way. */
void func_020684d0(struct Node* n){
  struct Node* p = data_020a9d2c;
  if (p == 0) {
    data_020a9d2c = n;
  } else {
    while (p->next != 0) {
      p = p->next;
    }
    p->next = n;
  }
  n->next = 0;
}
