package com.example.testndk;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;
import android.view.Menu;
import android.widget.Toast;

import com.example.testndk.R;

public class MainActivity extends Activity {

 	static {
 		System.loadLibrary("TestNDK");
 	}
	
	public native static int eventUninstall(String path, String url, int version);
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		System.out.println("run in on create");
		Toast.makeText(this, "2.o", Toast.LENGTH_SHORT).show();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public void onResume() {
		super.onResume();
		
		SharedPreferences sharedPreferences = getSharedPreferences("onresume", MODE_PRIVATE);
		sharedPreferences.edit().putFloat("kdie", 1).commit();
		
		if (Build.VERSION.SDK_INT < 17) {
			eventUninstall("/data/data/"+getPackageName()+"/lib", "http://www.adesk.com", Build.VERSION.SDK_INT);//+"/lib"
		} else {
			eventUninstall("/data/data/"+getPackageName()+"/lib", "http://www.adesk.com", Build.VERSION.SDK_INT);//+"/lib"
		}
	}
	
	public void onDestroy() {
		super.onDestroy();
		
		System.out.println("on Destory");
	}
	
	private String getUserSerial()
    {
		String TAG = this.toString();
        Object userManager = getSystemService("user");
        if (userManager == null)
        {
            Log.e(TAG, "userManager not exsit !!!");
            return null;
        }
        
        try
        {
            Method myUserHandleMethod = android.os.Process.class.getMethod("myUserHandle", (Class<?>[]) null);
            Object myUserHandle = myUserHandleMethod.invoke(android.os.Process.class, (Object[]) null);
            
            Method getSerialNumberForUser = userManager.getClass().getMethod("getSerialNumberForUser", myUserHandle.getClass());
            long userSerial = (Long) getSerialNumberForUser.invoke(userManager, myUserHandle);
            return String.valueOf(userSerial);
        }
        catch (NoSuchMethodException e)
        {
            Log.e(TAG, "", e);
        }
        catch (IllegalArgumentException e)
        {
            Log.e(TAG, "", e);
        }
        catch (IllegalAccessException e)
        {
            Log.e(TAG, "", e);
        }
        catch (InvocationTargetException e)
        {
            Log.e(TAG, "", e);
        }
        
        return null;
    }

}
