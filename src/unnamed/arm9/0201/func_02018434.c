struct P { int a, b; };
extern void myFS_ConvertPathToFileID(struct P *buf, int x);
extern void func_02018474(struct P p, int b, int c);
void func_02018434(int a0, int a1, int a2){
  struct P buf;
  myFS_ConvertPathToFileID(&buf, a0);
  func_02018474(buf, a1, a2);
}
