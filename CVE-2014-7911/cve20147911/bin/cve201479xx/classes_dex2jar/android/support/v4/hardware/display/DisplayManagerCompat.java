package android.support.v4.hardware.display;

import android.content.Context;
import android.os.Build.VERSION;
import android.view.Display;
import android.view.WindowManager;
import java.util.WeakHashMap;

public abstract class DisplayManagerCompat
{
  public static final String DISPLAY_CATEGORY_PRESENTATION = "android.hardware.display.category.PRESENTATION";
  private static final WeakHashMap<Context, DisplayManagerCompat> sInstances = new WeakHashMap();
  
  DisplayManagerCompat() {}
  
  public static DisplayManagerCompat getInstance(Context paramContext)
  {
    synchronized (sInstances)
    {
      Object localObject2 = (DisplayManagerCompat)sInstances.get(paramContext);
      if (localObject2 == null)
      {
        if (Build.VERSION.SDK_INT >= 17)
        {
          localObject2 = new JellybeanMr1Impl(paramContext);
          sInstances.put(paramContext, localObject2);
        }
      }
      else {
        return localObject2;
      }
      localObject2 = new LegacyImpl(paramContext);
    }
  }
  
  public abstract Display getDisplay(int paramInt);
  
  public abstract Display[] getDisplays();
  
  public abstract Display[] getDisplays(String paramString);
  
  private static class JellybeanMr1Impl
    extends DisplayManagerCompat
  {
    private final Object mDisplayManagerObj;
    
    public JellybeanMr1Impl(Context paramContext)
    {
      this.mDisplayManagerObj = DisplayManagerJellybeanMr1.getDisplayManager(paramContext);
    }
    
    public Display getDisplay(int paramInt)
    {
      return DisplayManagerJellybeanMr1.getDisplay(this.mDisplayManagerObj, paramInt);
    }
    
    public Display[] getDisplays()
    {
      return DisplayManagerJellybeanMr1.getDisplays(this.mDisplayManagerObj);
    }
    
    public Display[] getDisplays(String paramString)
    {
      return DisplayManagerJellybeanMr1.getDisplays(this.mDisplayManagerObj, paramString);
    }
  }
  
  private static class LegacyImpl
    extends DisplayManagerCompat
  {
    private final WindowManager mWindowManager;
    
    public LegacyImpl(Context paramContext)
    {
      this.mWindowManager = ((WindowManager)paramContext.getSystemService("window"));
    }
    
    public Display getDisplay(int paramInt)
    {
      Display localDisplay = this.mWindowManager.getDefaultDisplay();
      if (localDisplay.getDisplayId() == paramInt) {
        return localDisplay;
      }
      return null;
    }
    
    public Display[] getDisplays()
    {
      Display[] arrayOfDisplay = new Display[1];
      arrayOfDisplay[0] = this.mWindowManager.getDefaultDisplay();
      return arrayOfDisplay;
    }
    
    public Display[] getDisplays(String paramString)
    {
      if (paramString == null) {
        return getDisplays();
      }
      return new Display[0];
    }
  }
}
