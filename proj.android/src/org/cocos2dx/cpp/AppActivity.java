/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import cn.sharesdk.ShareSDKUtils;

import com.xiandiao.jump.GoogleBilling;
import com.xiandiao.jump.Util;
import com.xiandiao.jump.YouMiManager;

public class AppActivity extends Cocos2dxActivity {
	
	private static AppActivity _instance;
	private static YouMiManager _youMiManager;
	private static Util _util;
	private GoogleBilling _googleBilling;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		_instance = this;
		_youMiManager = new YouMiManager(this);
		_youMiManager.init();
		_util = new Util(this);
		_util.init();
		
		//_googleBilling = new GoogleBilling(this);
		
		this.initShareSDK();
	}
	
	public static Object getInstance(){
		return _instance;
	}
	
	public static Object getYouMiManager(){
		return _youMiManager;
	}
	
	private void initShareSDK(){
		ShareSDKUtils.prepare();
	}
	
	public native void adsResultCallback(int resultCode);
	
	@Override
	public void onBackPressed() {
		super.onBackPressed();
		_youMiManager.onBackPressed();
	}
	
	@Override
	protected void onStop() {
		super.onStop();
		_youMiManager.onStop();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		_youMiManager.onDestroy();
	}
}
