package android.support.v4.view;

import android.view.View;

public class ViewCompatKitKat
{
  public ViewCompatKitKat() {}
  
  public static int getAccessibilityLiveRegion(View paramView)
  {
    return paramView.getAccessibilityLiveRegion();
  }
  
  public static void setAccessibilityLiveRegion(View paramView, int paramInt)
  {
    paramView.setAccessibilityLiveRegion(paramInt);
  }
}
