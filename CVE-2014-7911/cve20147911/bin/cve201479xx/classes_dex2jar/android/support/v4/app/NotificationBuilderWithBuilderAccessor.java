package android.support.v4.app;

import android.app.Notification.Builder;

abstract interface NotificationBuilderWithBuilderAccessor
{
  public abstract Notification.Builder getBuilder();
}
