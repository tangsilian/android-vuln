package android.support.v4.os;

import android.os.Environment;
import java.io.File;

class EnvironmentCompatKitKat
{
  EnvironmentCompatKitKat() {}
  
  public static String getStorageState(File paramFile)
  {
    return Environment.getStorageState(paramFile);
  }
}
