package android.support.v4.view.accessibility;

import android.view.accessibility.AccessibilityNodeInfo;

class AccessibilityNodeInfoCompatJellybeanMr2
{
  AccessibilityNodeInfoCompatJellybeanMr2() {}
  
  public static String getViewIdResourceName(Object paramObject)
  {
    return ((AccessibilityNodeInfo)paramObject).getViewIdResourceName();
  }
  
  public static void setViewIdResourceName(Object paramObject, String paramString)
  {
    ((AccessibilityNodeInfo)paramObject).setViewIdResourceName(paramString);
  }
}
