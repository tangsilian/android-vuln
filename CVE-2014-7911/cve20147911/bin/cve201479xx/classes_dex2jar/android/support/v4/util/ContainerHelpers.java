package android.support.v4.util;

class ContainerHelpers
{
  static final int[] EMPTY_INTS = new int[0];
  static final long[] EMPTY_LONGS = new long[0];
  static final Object[] EMPTY_OBJECTS = new Object[0];
  
  ContainerHelpers() {}
  
  static int binarySearch(int[] paramArrayOfInt, int paramInt1, int paramInt2)
  {
    int i = 0;
    int j = paramInt1 - 1;
    while (i <= j)
    {
      k = i + j >>> 1;
      int m = paramArrayOfInt[k];
      if (m < paramInt2)
      {
        i = k + 1;
      }
      else
      {
        if (m <= paramInt2) {
          break label61;
        }
        j = k - 1;
      }
    }
    int k = i ^ 0xFFFFFFFF;
    label61:
    return k;
  }
  
  static int binarySearch(long[] paramArrayOfLong, int paramInt, long paramLong)
  {
    int i = 0;
    int j = paramInt - 1;
    while (i <= j)
    {
      k = i + j >>> 1;
      long l = paramArrayOfLong[k];
      if (l < paramLong)
      {
        i = k + 1;
      }
      else
      {
        if (l <= paramLong) {
          break label68;
        }
        j = k - 1;
      }
    }
    int k = i ^ 0xFFFFFFFF;
    label68:
    return k;
  }
  
  public static boolean equal(Object paramObject1, Object paramObject2)
  {
    return (paramObject1 == paramObject2) || ((paramObject1 != null) && (paramObject1.equals(paramObject2)));
  }
  
  public static int idealByteArraySize(int paramInt)
  {
    for (int i = 4;; i++) {
      if (i < 32)
      {
        if (paramInt <= -12 + (1 << i)) {
          paramInt = -12 + (1 << i);
        }
      }
      else {
        return paramInt;
      }
    }
  }
  
  public static int idealIntArraySize(int paramInt)
  {
    return idealByteArraySize(paramInt * 4) / 4;
  }
  
  public static int idealLongArraySize(int paramInt)
  {
    return idealByteArraySize(paramInt * 8) / 8;
  }
}
