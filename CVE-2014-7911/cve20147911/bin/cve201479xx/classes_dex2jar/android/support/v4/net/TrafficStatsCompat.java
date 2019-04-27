package android.support.v4.net;

import android.os.Build.VERSION;
import java.net.Socket;
import java.net.SocketException;

public class TrafficStatsCompat
{
  private static final TrafficStatsCompatImpl IMPL = new BaseTrafficStatsCompatImpl();
  
  static
  {
    if (Build.VERSION.SDK_INT >= 14)
    {
      IMPL = new IcsTrafficStatsCompatImpl();
      return;
    }
  }
  
  public TrafficStatsCompat() {}
  
  public static void clearThreadStatsTag()
  {
    IMPL.clearThreadStatsTag();
  }
  
  public static int getThreadStatsTag()
  {
    return IMPL.getThreadStatsTag();
  }
  
  public static void incrementOperationCount(int paramInt)
  {
    IMPL.incrementOperationCount(paramInt);
  }
  
  public static void incrementOperationCount(int paramInt1, int paramInt2)
  {
    IMPL.incrementOperationCount(paramInt1, paramInt2);
  }
  
  public static void setThreadStatsTag(int paramInt)
  {
    IMPL.setThreadStatsTag(paramInt);
  }
  
  public static void tagSocket(Socket paramSocket)
    throws SocketException
  {
    IMPL.tagSocket(paramSocket);
  }
  
  public static void untagSocket(Socket paramSocket)
    throws SocketException
  {
    IMPL.untagSocket(paramSocket);
  }
  
  static class BaseTrafficStatsCompatImpl
    implements TrafficStatsCompat.TrafficStatsCompatImpl
  {
    private ThreadLocal<SocketTags> mThreadSocketTags = new ThreadLocal()
    {
      protected TrafficStatsCompat.BaseTrafficStatsCompatImpl.SocketTags initialValue()
      {
        return new TrafficStatsCompat.BaseTrafficStatsCompatImpl.SocketTags(null);
      }
    };
    
    BaseTrafficStatsCompatImpl() {}
    
    public void clearThreadStatsTag()
    {
      ((SocketTags)this.mThreadSocketTags.get()).statsTag = -1;
    }
    
    public int getThreadStatsTag()
    {
      return ((SocketTags)this.mThreadSocketTags.get()).statsTag;
    }
    
    public void incrementOperationCount(int paramInt) {}
    
    public void incrementOperationCount(int paramInt1, int paramInt2) {}
    
    public void setThreadStatsTag(int paramInt)
    {
      ((SocketTags)this.mThreadSocketTags.get()).statsTag = paramInt;
    }
    
    public void tagSocket(Socket paramSocket) {}
    
    public void untagSocket(Socket paramSocket) {}
    
    private static class SocketTags
    {
      public int statsTag = -1;
      
      private SocketTags() {}
    }
  }
  
  static class IcsTrafficStatsCompatImpl
    implements TrafficStatsCompat.TrafficStatsCompatImpl
  {
    IcsTrafficStatsCompatImpl() {}
    
    public void clearThreadStatsTag() {}
    
    public int getThreadStatsTag()
    {
      return TrafficStatsCompatIcs.getThreadStatsTag();
    }
    
    public void incrementOperationCount(int paramInt)
    {
      TrafficStatsCompatIcs.incrementOperationCount(paramInt);
    }
    
    public void incrementOperationCount(int paramInt1, int paramInt2)
    {
      TrafficStatsCompatIcs.incrementOperationCount(paramInt1, paramInt2);
    }
    
    public void setThreadStatsTag(int paramInt)
    {
      TrafficStatsCompatIcs.setThreadStatsTag(paramInt);
    }
    
    public void tagSocket(Socket paramSocket)
      throws SocketException
    {
      TrafficStatsCompatIcs.tagSocket(paramSocket);
    }
    
    public void untagSocket(Socket paramSocket)
      throws SocketException
    {
      TrafficStatsCompatIcs.untagSocket(paramSocket);
    }
  }
  
  static abstract interface TrafficStatsCompatImpl
  {
    public abstract void clearThreadStatsTag();
    
    public abstract int getThreadStatsTag();
    
    public abstract void incrementOperationCount(int paramInt);
    
    public abstract void incrementOperationCount(int paramInt1, int paramInt2);
    
    public abstract void setThreadStatsTag(int paramInt);
    
    public abstract void tagSocket(Socket paramSocket)
      throws SocketException;
    
    public abstract void untagSocket(Socket paramSocket)
      throws SocketException;
  }
}
