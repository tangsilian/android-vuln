package android.support.v4.content;

import android.content.ComponentName;
import android.content.Intent;
import android.os.Build.VERSION;

public class IntentCompat
{
  public static final String ACTION_EXTERNAL_APPLICATIONS_AVAILABLE = "android.intent.action.EXTERNAL_APPLICATIONS_AVAILABLE";
  public static final String ACTION_EXTERNAL_APPLICATIONS_UNAVAILABLE = "android.intent.action.EXTERNAL_APPLICATIONS_UNAVAILABLE";
  public static final String EXTRA_CHANGED_PACKAGE_LIST = "android.intent.extra.changed_package_list";
  public static final String EXTRA_CHANGED_UID_LIST = "android.intent.extra.changed_uid_list";
  public static final String EXTRA_HTML_TEXT = "android.intent.extra.HTML_TEXT";
  public static final int FLAG_ACTIVITY_CLEAR_TASK = 32768;
  public static final int FLAG_ACTIVITY_TASK_ON_HOME = 16384;
  private static final IntentCompatImpl IMPL = new IntentCompatImplBase();
  
  static
  {
    int i = Build.VERSION.SDK_INT;
    if (i >= 15)
    {
      IMPL = new IntentCompatImplIcsMr1();
      return;
    }
    if (i >= 11)
    {
      IMPL = new IntentCompatImplHC();
      return;
    }
  }
  
  private IntentCompat() {}
  
  public static Intent makeMainActivity(ComponentName paramComponentName)
  {
    return IMPL.makeMainActivity(paramComponentName);
  }
  
  public static Intent makeMainSelectorActivity(String paramString1, String paramString2)
  {
    return IMPL.makeMainSelectorActivity(paramString1, paramString2);
  }
  
  public static Intent makeRestartActivityTask(ComponentName paramComponentName)
  {
    return IMPL.makeRestartActivityTask(paramComponentName);
  }
  
  static abstract interface IntentCompatImpl
  {
    public abstract Intent makeMainActivity(ComponentName paramComponentName);
    
    public abstract Intent makeMainSelectorActivity(String paramString1, String paramString2);
    
    public abstract Intent makeRestartActivityTask(ComponentName paramComponentName);
  }
  
  static class IntentCompatImplBase
    implements IntentCompat.IntentCompatImpl
  {
    IntentCompatImplBase() {}
    
    public Intent makeMainActivity(ComponentName paramComponentName)
    {
      Intent localIntent = new Intent("android.intent.action.MAIN");
      localIntent.setComponent(paramComponentName);
      localIntent.addCategory("android.intent.category.LAUNCHER");
      return localIntent;
    }
    
    public Intent makeMainSelectorActivity(String paramString1, String paramString2)
    {
      Intent localIntent = new Intent(paramString1);
      localIntent.addCategory(paramString2);
      return localIntent;
    }
    
    public Intent makeRestartActivityTask(ComponentName paramComponentName)
    {
      Intent localIntent = makeMainActivity(paramComponentName);
      localIntent.addFlags(268468224);
      return localIntent;
    }
  }
  
  static class IntentCompatImplHC
    extends IntentCompat.IntentCompatImplBase
  {
    IntentCompatImplHC() {}
    
    public Intent makeMainActivity(ComponentName paramComponentName)
    {
      return IntentCompatHoneycomb.makeMainActivity(paramComponentName);
    }
    
    public Intent makeRestartActivityTask(ComponentName paramComponentName)
    {
      return IntentCompatHoneycomb.makeRestartActivityTask(paramComponentName);
    }
  }
  
  static class IntentCompatImplIcsMr1
    extends IntentCompat.IntentCompatImplHC
  {
    IntentCompatImplIcsMr1() {}
    
    public Intent makeMainSelectorActivity(String paramString1, String paramString2)
    {
      return IntentCompatIcsMr1.makeMainSelectorActivity(paramString1, paramString2);
    }
  }
}
