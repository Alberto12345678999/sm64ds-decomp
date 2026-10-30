/* recovered: r0 is the FSFileID out pointer, r1 the path; FSi_FindPath is
 * handed them as (file, path, out_file_id, 0). Its one-instruction caller
 * myFS_ConvertPathToFileID reaches it with both still in the registers. */
extern void FS_InitFile(void *file);
extern int FSi_FindPath(void *file, const char *path, void *out_file_id, int c);

int func_0205d644(void *out_file_id, const char *path){
  int file[0x11];
  FS_InitFile(file);
  return FSi_FindPath(file, path, out_file_id, 0) != 0;
}
