package android.support.v4.content;

import android.content.Context;
import java.io.File;

class ContextCompatFroyo
{
  ContextCompatFroyo() {}
  
  public static File getExternalCacheDir(Context paramContext)
  {
    return paramContext.getExternalCacheDir();
  }
  
  public static File getExternalFilesDir(Context paramContext, String paramString)
  {
    return paramContext.getExternalFilesDir(paramString);
  }
}
