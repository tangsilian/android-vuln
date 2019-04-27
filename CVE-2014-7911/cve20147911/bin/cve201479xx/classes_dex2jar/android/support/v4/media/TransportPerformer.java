package android.support.v4.media;

import android.os.SystemClock;
import android.view.KeyEvent;

public abstract class TransportPerformer
{
  static final int AUDIOFOCUS_GAIN = 1;
  static final int AUDIOFOCUS_GAIN_TRANSIENT = 2;
  static final int AUDIOFOCUS_GAIN_TRANSIENT_MAY_DUCK = 3;
  static final int AUDIOFOCUS_LOSS = -1;
  static final int AUDIOFOCUS_LOSS_TRANSIENT = -2;
  static final int AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK = -3;
  
  public TransportPerformer() {}
  
  public void onAudioFocusChange(int paramInt)
  {
    int i = 0;
    switch (paramInt)
    {
    }
    for (;;)
    {
      if (i != 0)
      {
        long l = SystemClock.uptimeMillis();
        onMediaButtonDown(i, new KeyEvent(l, l, 0, i, 0));
        onMediaButtonUp(i, new KeyEvent(l, l, 1, i, 0));
      }
      return;
      i = 127;
    }
  }
  
  public int onGetBufferPercentage()
  {
    return 100;
  }
  
  public abstract long onGetCurrentPosition();
  
  public abstract long onGetDuration();
  
  public int onGetTransportControlFlags()
  {
    return 60;
  }
  
  public abstract boolean onIsPlaying();
  
  public boolean onMediaButtonDown(int paramInt, KeyEvent paramKeyEvent)
  {
    switch (paramInt)
    {
    default: 
      return true;
    case 126: 
      onStart();
      return true;
    case 127: 
      onPause();
      return true;
    case 86: 
      onStop();
      return true;
    }
    if (onIsPlaying())
    {
      onPause();
      return true;
    }
    onStart();
    return true;
  }
  
  public boolean onMediaButtonUp(int paramInt, KeyEvent paramKeyEvent)
  {
    return true;
  }
  
  public abstract void onPause();
  
  public abstract void onSeekTo(long paramLong);
  
  public abstract void onStart();
  
  public abstract void onStop();
}
