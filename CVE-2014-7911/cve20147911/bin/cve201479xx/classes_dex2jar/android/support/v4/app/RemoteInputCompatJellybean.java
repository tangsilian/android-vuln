package android.support.v4.app;

import android.content.ClipData;
import android.content.ClipData.Item;
import android.content.ClipDescription;
import android.content.Intent;
import android.os.Bundle;

class RemoteInputCompatJellybean
{
  public static final String EXTRA_RESULTS_DATA = "android.remoteinput.resultsData";
  private static final String KEY_ALLOW_FREE_FORM_INPUT = "allowFreeFormInput";
  private static final String KEY_CHOICES = "choices";
  private static final String KEY_EXTRAS = "extras";
  private static final String KEY_LABEL = "label";
  private static final String KEY_RESULT_KEY = "resultKey";
  public static final String RESULTS_CLIP_LABEL = "android.remoteinput.results";
  
  RemoteInputCompatJellybean() {}
  
  static void addResultsToIntent(RemoteInputCompatBase.RemoteInput[] paramArrayOfRemoteInput, Intent paramIntent, Bundle paramBundle)
  {
    Bundle localBundle = new Bundle();
    int i = paramArrayOfRemoteInput.length;
    for (int j = 0; j < i; j++)
    {
      RemoteInputCompatBase.RemoteInput localRemoteInput = paramArrayOfRemoteInput[j];
      Object localObject = paramBundle.get(localRemoteInput.getResultKey());
      if ((localObject instanceof CharSequence)) {
        localBundle.putCharSequence(localRemoteInput.getResultKey(), (CharSequence)localObject);
      }
    }
    Intent localIntent = new Intent();
    localIntent.putExtra("android.remoteinput.resultsData", localBundle);
    paramIntent.setClipData(ClipData.newIntent("android.remoteinput.results", localIntent));
  }
  
  static RemoteInputCompatBase.RemoteInput fromBundle(Bundle paramBundle, RemoteInputCompatBase.RemoteInput.Factory paramFactory)
  {
    return paramFactory.build(paramBundle.getString("resultKey"), paramBundle.getCharSequence("label"), paramBundle.getCharSequenceArray("choices"), paramBundle.getBoolean("allowFreeFormInput"), paramBundle.getBundle("extras"));
  }
  
  static RemoteInputCompatBase.RemoteInput[] fromBundleArray(Bundle[] paramArrayOfBundle, RemoteInputCompatBase.RemoteInput.Factory paramFactory)
  {
    RemoteInputCompatBase.RemoteInput[] arrayOfRemoteInput;
    if (paramArrayOfBundle == null) {
      arrayOfRemoteInput = null;
    }
    for (;;)
    {
      return arrayOfRemoteInput;
      arrayOfRemoteInput = paramFactory.newArray(paramArrayOfBundle.length);
      for (int i = 0; i < paramArrayOfBundle.length; i++) {
        arrayOfRemoteInput[i] = fromBundle(paramArrayOfBundle[i], paramFactory);
      }
    }
  }
  
  static Bundle getResultsFromIntent(Intent paramIntent)
  {
    ClipData localClipData = paramIntent.getClipData();
    if (localClipData == null) {}
    ClipDescription localClipDescription;
    do
    {
      return null;
      localClipDescription = localClipData.getDescription();
    } while ((!localClipDescription.hasMimeType("text/vnd.android.intent")) || (!localClipDescription.getLabel().equals("android.remoteinput.results")));
    return (Bundle)localClipData.getItemAt(0).getIntent().getExtras().getParcelable("android.remoteinput.resultsData");
  }
  
  static Bundle toBundle(RemoteInputCompatBase.RemoteInput paramRemoteInput)
  {
    Bundle localBundle = new Bundle();
    localBundle.putString("resultKey", paramRemoteInput.getResultKey());
    localBundle.putCharSequence("label", paramRemoteInput.getLabel());
    localBundle.putCharSequenceArray("choices", paramRemoteInput.getChoices());
    localBundle.putBoolean("allowFreeFormInput", paramRemoteInput.getAllowFreeFormInput());
    localBundle.putBundle("extras", paramRemoteInput.getExtras());
    return localBundle;
  }
  
  static Bundle[] toBundleArray(RemoteInputCompatBase.RemoteInput[] paramArrayOfRemoteInput)
  {
    Bundle[] arrayOfBundle;
    if (paramArrayOfRemoteInput == null) {
      arrayOfBundle = null;
    }
    for (;;)
    {
      return arrayOfBundle;
      arrayOfBundle = new Bundle[paramArrayOfRemoteInput.length];
      for (int i = 0; i < paramArrayOfRemoteInput.length; i++) {
        arrayOfBundle[i] = toBundle(paramArrayOfRemoteInput[i]);
      }
    }
  }
}
