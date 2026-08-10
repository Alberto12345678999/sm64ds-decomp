long long Vec3_DistSq(int* a, int* b){
  long long acc = (long long)(a[0] - b[0]) * (a[0] - b[0]);
  acc += (long long)(a[1] - b[1]) * (a[1] - b[1]);
  acc += (long long)(a[2] - b[2]) * (a[2] - b[2]);
  return acc >> 12;
}
