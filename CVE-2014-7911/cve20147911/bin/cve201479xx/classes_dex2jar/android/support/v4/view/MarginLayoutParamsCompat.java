package android.support.v4.view;

import android.os.Build.VERSION;
import android.view.ViewGroup.MarginLayoutParams;

public class MarginLayoutParamsCompat
{
  static final MarginLayoutParamsCompatImpl IMPL = new MarginLayoutParamsCompatImplBase();
  
  static
  {
    if (Build.VERSION.SDK_INT >= 17)
    {
      IMPL = new MarginLayoutParamsCompatImplJbMr1();
      return;
    }
  }
  
  public MarginLayoutParamsCompat() {}
  
  public static int getLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
  {
    return IMPL.getLayoutDirection(paramMarginLayoutParams);
  }
  
  public static int getMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
  {
    return IMPL.getMarginEnd(paramMarginLayoutParams);
  }
  
  public static int getMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
  {
    return IMPL.getMarginStart(paramMarginLayoutParams);
  }
  
  public static boolean isMarginRelative(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
  {
    return IMPL.isMarginRelative(paramMarginLayoutParams);
  }
  
  public static void resolveLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
  {
    IMPL.resolveLayoutDirection(paramMarginLayoutParams, paramInt);
  }
  
  public static void setLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
  {
    IMPL.setLayoutDirection(paramMarginLayoutParams, paramInt);
  }
  
  public static void setMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
  {
    IMPL.setMarginEnd(paramMarginLayoutParams, paramInt);
  }
  
  public static void setMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
  {
    IMPL.setMarginStart(paramMarginLayoutParams, paramInt);
  }
  
  static abstract interface MarginLayoutParamsCompatImpl
  {
    public abstract int getLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams);
    
    public abstract int getMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams);
    
    public abstract int getMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams);
    
    public abstract boolean isMarginRelative(ViewGroup.MarginLayoutParams paramMarginLayoutParams);
    
    public abstract void resolveLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt);
    
    public abstract void setLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt);
    
    public abstract void setMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt);
    
    public abstract void setMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt);
  }
  
  static class MarginLayoutParamsCompatImplBase
    implements MarginLayoutParamsCompat.MarginLayoutParamsCompatImpl
  {
    MarginLayoutParamsCompatImplBase() {}
    
    public int getLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return 0;
    }
    
    public int getMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return paramMarginLayoutParams.rightMargin;
    }
    
    public int getMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return paramMarginLayoutParams.leftMargin;
    }
    
    public boolean isMarginRelative(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return false;
    }
    
    public void resolveLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt) {}
    
    public void setLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt) {}
    
    public void setMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      paramMarginLayoutParams.rightMargin = paramInt;
    }
    
    public void setMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      paramMarginLayoutParams.leftMargin = paramInt;
    }
  }
  
  static class MarginLayoutParamsCompatImplJbMr1
    implements MarginLayoutParamsCompat.MarginLayoutParamsCompatImpl
  {
    MarginLayoutParamsCompatImplJbMr1() {}
    
    public int getLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return MarginLayoutParamsCompatJellybeanMr1.getLayoutDirection(paramMarginLayoutParams);
    }
    
    public int getMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return MarginLayoutParamsCompatJellybeanMr1.getMarginEnd(paramMarginLayoutParams);
    }
    
    public int getMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return MarginLayoutParamsCompatJellybeanMr1.getMarginStart(paramMarginLayoutParams);
    }
    
    public boolean isMarginRelative(ViewGroup.MarginLayoutParams paramMarginLayoutParams)
    {
      return MarginLayoutParamsCompatJellybeanMr1.isMarginRelative(paramMarginLayoutParams);
    }
    
    public void resolveLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      MarginLayoutParamsCompatJellybeanMr1.resolveLayoutDirection(paramMarginLayoutParams, paramInt);
    }
    
    public void setLayoutDirection(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      MarginLayoutParamsCompatJellybeanMr1.setLayoutDirection(paramMarginLayoutParams, paramInt);
    }
    
    public void setMarginEnd(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      MarginLayoutParamsCompatJellybeanMr1.setMarginEnd(paramMarginLayoutParams, paramInt);
    }
    
    public void setMarginStart(ViewGroup.MarginLayoutParams paramMarginLayoutParams, int paramInt)
    {
      MarginLayoutParamsCompatJellybeanMr1.setMarginStart(paramMarginLayoutParams, paramInt);
    }
  }
}
