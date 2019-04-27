package android.support.v4.view.accessibility;

import android.view.accessibility.AccessibilityRecord;

class AccessibilityRecordCompatIcsMr1
{
  AccessibilityRecordCompatIcsMr1() {}
  
  public static int getMaxScrollX(Object paramObject)
  {
    return ((AccessibilityRecord)paramObject).getMaxScrollX();
  }
  
  public static int getMaxScrollY(Object paramObject)
  {
    return ((AccessibilityRecord)paramObject).getMaxScrollY();
  }
  
  public static void setMaxScrollX(Object paramObject, int paramInt)
  {
    ((AccessibilityRecord)paramObject).setMaxScrollX(paramInt);
  }
  
  public static void setMaxScrollY(Object paramObject, int paramInt)
  {
    ((AccessibilityRecord)paramObject).setMaxScrollY(paramInt);
  }
}
