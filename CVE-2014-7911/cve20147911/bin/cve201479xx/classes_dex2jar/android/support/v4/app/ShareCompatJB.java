package android.support.v4.app;

import android.text.Html;

class ShareCompatJB
{
  ShareCompatJB() {}
  
  public static String escapeHtml(CharSequence paramCharSequence)
  {
    return Html.escapeHtml(paramCharSequence);
  }
}
