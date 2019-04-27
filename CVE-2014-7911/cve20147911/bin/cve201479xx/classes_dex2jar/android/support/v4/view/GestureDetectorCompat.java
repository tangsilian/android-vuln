package android.support.v4.view;

import android.content.Context;
import android.os.Build.VERSION;
import android.os.Handler;
import android.os.Message;
import android.view.GestureDetector;
import android.view.GestureDetector.OnDoubleTapListener;
import android.view.GestureDetector.OnGestureListener;
import android.view.MotionEvent;
import android.view.VelocityTracker;
import android.view.ViewConfiguration;

public class GestureDetectorCompat
{
  private final GestureDetectorCompatImpl mImpl;
  
  public GestureDetectorCompat(Context paramContext, GestureDetector.OnGestureListener paramOnGestureListener)
  {
    this(paramContext, paramOnGestureListener, null);
  }
  
  public GestureDetectorCompat(Context paramContext, GestureDetector.OnGestureListener paramOnGestureListener, Handler paramHandler)
  {
    if (Build.VERSION.SDK_INT > 17)
    {
      this.mImpl = new GestureDetectorCompatImplJellybeanMr2(paramContext, paramOnGestureListener, paramHandler);
      return;
    }
    this.mImpl = new GestureDetectorCompatImplBase(paramContext, paramOnGestureListener, paramHandler);
  }
  
  public boolean isLongpressEnabled()
  {
    return this.mImpl.isLongpressEnabled();
  }
  
  public boolean onTouchEvent(MotionEvent paramMotionEvent)
  {
    return this.mImpl.onTouchEvent(paramMotionEvent);
  }
  
  public void setIsLongpressEnabled(boolean paramBoolean)
  {
    this.mImpl.setIsLongpressEnabled(paramBoolean);
  }
  
  public void setOnDoubleTapListener(GestureDetector.OnDoubleTapListener paramOnDoubleTapListener)
  {
    this.mImpl.setOnDoubleTapListener(paramOnDoubleTapListener);
  }
  
  static abstract interface GestureDetectorCompatImpl
  {
    public abstract boolean isLongpressEnabled();
    
    public abstract boolean onTouchEvent(MotionEvent paramMotionEvent);
    
    public abstract void setIsLongpressEnabled(boolean paramBoolean);
    
    public abstract void setOnDoubleTapListener(GestureDetector.OnDoubleTapListener paramOnDoubleTapListener);
  }
  
  static class GestureDetectorCompatImplBase
    implements GestureDetectorCompat.GestureDetectorCompatImpl
  {
    private static final int DOUBLE_TAP_TIMEOUT = ViewConfiguration.getDoubleTapTimeout();
    private static final int LONGPRESS_TIMEOUT = ;
    private static final int LONG_PRESS = 2;
    private static final int SHOW_PRESS = 1;
    private static final int TAP = 3;
    private static final int TAP_TIMEOUT = ViewConfiguration.getTapTimeout();
    private boolean mAlwaysInBiggerTapRegion;
    private boolean mAlwaysInTapRegion;
    private MotionEvent mCurrentDownEvent;
    private boolean mDeferConfirmSingleTap;
    private GestureDetector.OnDoubleTapListener mDoubleTapListener;
    private int mDoubleTapSlopSquare;
    private float mDownFocusX;
    private float mDownFocusY;
    private final Handler mHandler;
    private boolean mInLongPress;
    private boolean mIsDoubleTapping;
    private boolean mIsLongpressEnabled;
    private float mLastFocusX;
    private float mLastFocusY;
    private final GestureDetector.OnGestureListener mListener;
    private int mMaximumFlingVelocity;
    private int mMinimumFlingVelocity;
    private MotionEvent mPreviousUpEvent;
    private boolean mStillDown;
    private int mTouchSlopSquare;
    private VelocityTracker mVelocityTracker;
    
    public GestureDetectorCompatImplBase(Context paramContext, GestureDetector.OnGestureListener paramOnGestureListener, Handler paramHandler)
    {
      if (paramHandler != null) {}
      for (this.mHandler = new GestureHandler(paramHandler);; this.mHandler = new GestureHandler())
      {
        this.mListener = paramOnGestureListener;
        if ((paramOnGestureListener instanceof GestureDetector.OnDoubleTapListener)) {
          setOnDoubleTapListener((GestureDetector.OnDoubleTapListener)paramOnGestureListener);
        }
        init(paramContext);
        return;
      }
    }
    
    private void cancel()
    {
      this.mHandler.removeMessages(1);
      this.mHandler.removeMessages(2);
      this.mHandler.removeMessages(3);
      this.mVelocityTracker.recycle();
      this.mVelocityTracker = null;
      this.mIsDoubleTapping = false;
      this.mStillDown = false;
      this.mAlwaysInTapRegion = false;
      this.mAlwaysInBiggerTapRegion = false;
      this.mDeferConfirmSingleTap = false;
      if (this.mInLongPress) {
        this.mInLongPress = false;
      }
    }
    
    private void cancelTaps()
    {
      this.mHandler.removeMessages(1);
      this.mHandler.removeMessages(2);
      this.mHandler.removeMessages(3);
      this.mIsDoubleTapping = false;
      this.mAlwaysInTapRegion = false;
      this.mAlwaysInBiggerTapRegion = false;
      this.mDeferConfirmSingleTap = false;
      if (this.mInLongPress) {
        this.mInLongPress = false;
      }
    }
    
    private void dispatchLongPress()
    {
      this.mHandler.removeMessages(3);
      this.mDeferConfirmSingleTap = false;
      this.mInLongPress = true;
      this.mListener.onLongPress(this.mCurrentDownEvent);
    }
    
    private void init(Context paramContext)
    {
      if (paramContext == null) {
        throw new IllegalArgumentException("Context must not be null");
      }
      if (this.mListener == null) {
        throw new IllegalArgumentException("OnGestureListener must not be null");
      }
      this.mIsLongpressEnabled = true;
      ViewConfiguration localViewConfiguration = ViewConfiguration.get(paramContext);
      int i = localViewConfiguration.getScaledTouchSlop();
      int j = localViewConfiguration.getScaledDoubleTapSlop();
      this.mMinimumFlingVelocity = localViewConfiguration.getScaledMinimumFlingVelocity();
      this.mMaximumFlingVelocity = localViewConfiguration.getScaledMaximumFlingVelocity();
      this.mTouchSlopSquare = (i * i);
      this.mDoubleTapSlopSquare = (j * j);
    }
    
    private boolean isConsideredDoubleTap(MotionEvent paramMotionEvent1, MotionEvent paramMotionEvent2, MotionEvent paramMotionEvent3)
    {
      if (!this.mAlwaysInBiggerTapRegion) {}
      int i;
      int j;
      do
      {
        do
        {
          return false;
        } while (paramMotionEvent3.getEventTime() - paramMotionEvent2.getEventTime() > DOUBLE_TAP_TIMEOUT);
        i = (int)paramMotionEvent1.getX() - (int)paramMotionEvent3.getX();
        j = (int)paramMotionEvent1.getY() - (int)paramMotionEvent3.getY();
      } while (i * i + j * j >= this.mDoubleTapSlopSquare);
      return true;
    }
    
    public boolean isLongpressEnabled()
    {
      return this.mIsLongpressEnabled;
    }
    
    public boolean onTouchEvent(MotionEvent paramMotionEvent)
    {
      int i = paramMotionEvent.getAction();
      if (this.mVelocityTracker == null) {
        this.mVelocityTracker = VelocityTracker.obtain();
      }
      this.mVelocityTracker.addMovement(paramMotionEvent);
      int j;
      int k;
      label49:
      float f1;
      float f2;
      int m;
      int n;
      if ((i & 0xFF) == 6)
      {
        j = 1;
        if (j == 0) {
          break label89;
        }
        k = MotionEventCompat.getActionIndex(paramMotionEvent);
        f1 = 0.0F;
        f2 = 0.0F;
        m = MotionEventCompat.getPointerCount(paramMotionEvent);
        n = 0;
        label64:
        if (n >= m) {
          break label120;
        }
        if (k != n) {
          break label95;
        }
      }
      for (;;)
      {
        n++;
        break label64;
        j = 0;
        break;
        label89:
        k = -1;
        break label49;
        label95:
        f1 += MotionEventCompat.getX(paramMotionEvent, n);
        f2 += MotionEventCompat.getY(paramMotionEvent, n);
      }
      label120:
      int i1;
      float f3;
      float f4;
      int i2;
      boolean bool1;
      if (j != 0)
      {
        i1 = m - 1;
        f3 = f1 / i1;
        f4 = f2 / i1;
        i2 = i & 0xFF;
        bool1 = false;
      }
      switch (i2)
      {
      case 4: 
      default: 
      case 5: 
      case 6: 
      case 0: 
      case 2: 
        float f7;
        float f8;
        boolean bool6;
        do
        {
          int i6;
          do
          {
            boolean bool4;
            do
            {
              int i8;
              float f9;
              float f10;
              int i10;
              int i11;
              do
              {
                return bool1;
                i1 = m;
                break;
                this.mLastFocusX = f3;
                this.mDownFocusX = f3;
                this.mLastFocusY = f4;
                this.mDownFocusY = f4;
                cancelTaps();
                return false;
                this.mLastFocusX = f3;
                this.mDownFocusX = f3;
                this.mLastFocusY = f4;
                this.mDownFocusY = f4;
                this.mVelocityTracker.computeCurrentVelocity(1000, this.mMaximumFlingVelocity);
                i8 = MotionEventCompat.getActionIndex(paramMotionEvent);
                int i9 = MotionEventCompat.getPointerId(paramMotionEvent, i8);
                f9 = VelocityTrackerCompat.getXVelocity(this.mVelocityTracker, i9);
                f10 = VelocityTrackerCompat.getYVelocity(this.mVelocityTracker, i9);
                i10 = 0;
                i11 = i10;
                bool1 = false;
              } while (i11 >= m);
              if (i10 == i8) {}
              int i12;
              do
              {
                i10++;
                break;
                i12 = MotionEventCompat.getPointerId(paramMotionEvent, i10);
              } while (f9 * VelocityTrackerCompat.getXVelocity(this.mVelocityTracker, i12) + f10 * VelocityTrackerCompat.getYVelocity(this.mVelocityTracker, i12) >= 0.0F);
              this.mVelocityTracker.clear();
              return false;
              GestureDetector.OnDoubleTapListener localOnDoubleTapListener = this.mDoubleTapListener;
              boolean bool7 = false;
              if (localOnDoubleTapListener != null)
              {
                boolean bool8 = this.mHandler.hasMessages(3);
                if (bool8) {
                  this.mHandler.removeMessages(3);
                }
                if ((this.mCurrentDownEvent == null) || (this.mPreviousUpEvent == null) || (!bool8) || (!isConsideredDoubleTap(this.mCurrentDownEvent, this.mPreviousUpEvent, paramMotionEvent))) {
                  break label644;
                }
                this.mIsDoubleTapping = true;
              }
              for (bool7 = false | this.mDoubleTapListener.onDoubleTap(this.mCurrentDownEvent) | this.mDoubleTapListener.onDoubleTapEvent(paramMotionEvent);; bool7 = false)
              {
                this.mLastFocusX = f3;
                this.mDownFocusX = f3;
                this.mLastFocusY = f4;
                this.mDownFocusY = f4;
                if (this.mCurrentDownEvent != null) {
                  this.mCurrentDownEvent.recycle();
                }
                this.mCurrentDownEvent = MotionEvent.obtain(paramMotionEvent);
                this.mAlwaysInTapRegion = true;
                this.mAlwaysInBiggerTapRegion = true;
                this.mStillDown = true;
                this.mInLongPress = false;
                this.mDeferConfirmSingleTap = false;
                if (this.mIsLongpressEnabled)
                {
                  this.mHandler.removeMessages(2);
                  this.mHandler.sendEmptyMessageAtTime(2, this.mCurrentDownEvent.getDownTime() + TAP_TIMEOUT + LONGPRESS_TIMEOUT);
                }
                this.mHandler.sendEmptyMessageAtTime(1, this.mCurrentDownEvent.getDownTime() + TAP_TIMEOUT);
                return bool7 | this.mListener.onDown(paramMotionEvent);
                this.mHandler.sendEmptyMessageDelayed(3, DOUBLE_TAP_TIMEOUT);
              }
              bool4 = this.mInLongPress;
              bool1 = false;
            } while (bool4);
            f7 = this.mLastFocusX - f3;
            f8 = this.mLastFocusY - f4;
            if (this.mIsDoubleTapping) {
              return false | this.mDoubleTapListener.onDoubleTapEvent(paramMotionEvent);
            }
            if (!this.mAlwaysInTapRegion) {
              break label849;
            }
            int i4 = (int)(f3 - this.mDownFocusX);
            int i5 = (int)(f4 - this.mDownFocusY);
            i6 = i4 * i4 + i5 * i5;
            int i7 = this.mTouchSlopSquare;
            bool1 = false;
            if (i6 > i7)
            {
              bool1 = this.mListener.onScroll(this.mCurrentDownEvent, paramMotionEvent, f7, f8);
              this.mLastFocusX = f3;
              this.mLastFocusY = f4;
              this.mAlwaysInTapRegion = false;
              this.mHandler.removeMessages(3);
              this.mHandler.removeMessages(1);
              this.mHandler.removeMessages(2);
            }
          } while (i6 <= this.mTouchSlopSquare);
          this.mAlwaysInBiggerTapRegion = false;
          return bool1;
          if (Math.abs(f7) >= 1.0F) {
            break label876;
          }
          bool6 = Math.abs(f8) < 1.0F;
          bool1 = false;
        } while (bool6);
        boolean bool5 = this.mListener.onScroll(this.mCurrentDownEvent, paramMotionEvent, f7, f8);
        this.mLastFocusX = f3;
        this.mLastFocusY = f4;
        return bool5;
      case 1: 
        label644:
        label849:
        label876:
        this.mStillDown = false;
        MotionEvent localMotionEvent = MotionEvent.obtain(paramMotionEvent);
        boolean bool2;
        if (this.mIsDoubleTapping) {
          bool2 = false | this.mDoubleTapListener.onDoubleTapEvent(paramMotionEvent);
        }
        for (;;)
        {
          if (this.mPreviousUpEvent != null) {
            this.mPreviousUpEvent.recycle();
          }
          this.mPreviousUpEvent = localMotionEvent;
          if (this.mVelocityTracker != null)
          {
            this.mVelocityTracker.recycle();
            this.mVelocityTracker = null;
          }
          this.mIsDoubleTapping = false;
          this.mDeferConfirmSingleTap = false;
          this.mHandler.removeMessages(1);
          this.mHandler.removeMessages(2);
          return bool2;
          if (this.mInLongPress)
          {
            this.mHandler.removeMessages(3);
            this.mInLongPress = false;
            bool2 = false;
          }
          else if (this.mAlwaysInTapRegion)
          {
            bool2 = this.mListener.onSingleTapUp(paramMotionEvent);
            if ((this.mDeferConfirmSingleTap) && (this.mDoubleTapListener != null)) {
              this.mDoubleTapListener.onSingleTapConfirmed(paramMotionEvent);
            }
          }
          else
          {
            VelocityTracker localVelocityTracker = this.mVelocityTracker;
            int i3 = MotionEventCompat.getPointerId(paramMotionEvent, 0);
            localVelocityTracker.computeCurrentVelocity(1000, this.mMaximumFlingVelocity);
            float f5 = VelocityTrackerCompat.getYVelocity(localVelocityTracker, i3);
            float f6 = VelocityTrackerCompat.getXVelocity(localVelocityTracker, i3);
            if (Math.abs(f5) <= this.mMinimumFlingVelocity)
            {
              boolean bool3 = Math.abs(f6) < this.mMinimumFlingVelocity;
              bool2 = false;
              if (!bool3) {}
            }
            else
            {
              bool2 = this.mListener.onFling(this.mCurrentDownEvent, paramMotionEvent, f6, f5);
            }
          }
        }
      }
      cancel();
      return false;
    }
    
    public void setIsLongpressEnabled(boolean paramBoolean)
    {
      this.mIsLongpressEnabled = paramBoolean;
    }
    
    public void setOnDoubleTapListener(GestureDetector.OnDoubleTapListener paramOnDoubleTapListener)
    {
      this.mDoubleTapListener = paramOnDoubleTapListener;
    }
    
    private class GestureHandler
      extends Handler
    {
      GestureHandler() {}
      
      GestureHandler(Handler paramHandler)
      {
        super();
      }
      
      public void handleMessage(Message paramMessage)
      {
        switch (paramMessage.what)
        {
        default: 
          throw new RuntimeException("Unknown message " + paramMessage);
        case 1: 
          GestureDetectorCompat.GestureDetectorCompatImplBase.this.mListener.onShowPress(GestureDetectorCompat.GestureDetectorCompatImplBase.this.mCurrentDownEvent);
        }
        do
        {
          return;
          GestureDetectorCompat.GestureDetectorCompatImplBase.this.dispatchLongPress();
          return;
        } while (GestureDetectorCompat.GestureDetectorCompatImplBase.this.mDoubleTapListener == null);
        if (!GestureDetectorCompat.GestureDetectorCompatImplBase.this.mStillDown)
        {
          GestureDetectorCompat.GestureDetectorCompatImplBase.this.mDoubleTapListener.onSingleTapConfirmed(GestureDetectorCompat.GestureDetectorCompatImplBase.this.mCurrentDownEvent);
          return;
        }
        GestureDetectorCompat.GestureDetectorCompatImplBase.access$502(GestureDetectorCompat.GestureDetectorCompatImplBase.this, true);
      }
    }
  }
  
  static class GestureDetectorCompatImplJellybeanMr2
    implements GestureDetectorCompat.GestureDetectorCompatImpl
  {
    private final GestureDetector mDetector;
    
    public GestureDetectorCompatImplJellybeanMr2(Context paramContext, GestureDetector.OnGestureListener paramOnGestureListener, Handler paramHandler)
    {
      this.mDetector = new GestureDetector(paramContext, paramOnGestureListener, paramHandler);
    }
    
    public boolean isLongpressEnabled()
    {
      return this.mDetector.isLongpressEnabled();
    }
    
    public boolean onTouchEvent(MotionEvent paramMotionEvent)
    {
      return this.mDetector.onTouchEvent(paramMotionEvent);
    }
    
    public void setIsLongpressEnabled(boolean paramBoolean)
    {
      this.mDetector.setIsLongpressEnabled(paramBoolean);
    }
    
    public void setOnDoubleTapListener(GestureDetector.OnDoubleTapListener paramOnDoubleTapListener)
    {
      this.mDetector.setOnDoubleTapListener(paramOnDoubleTapListener);
    }
  }
}
