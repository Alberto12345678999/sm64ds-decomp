extern void myFS_ConvertPathToFileID(void *, int);
extern int data_0209d3b4;

int func_020189f0(int path) {
    int buf[3];
    myFS_ConvertPathToFileID(buf, path);
    data_0209d3b4 = buf[0];
    return buf[1];
}
