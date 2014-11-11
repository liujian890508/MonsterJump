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

import net.youmi.android.AdManager;
import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.banner.AdViewListener;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;
import cn.sharesdk.ShareSDKUtils;

public class AppActivity extends Cocos2dxActivity {
	
	private static AppActivity _instance;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		_instance = this;
		
		this.initShareSDK();
		this.initAdManager();
	}
	
	public static AppActivity getInstance(){
		return _instance;
	}
	
	private void initAdManager(){
		AdManager.getInstance(this).init("4bab86630bbf80a7", "451a4f3fe73c639b", true);
		AdManager.getInstance(this).setEnableDebugLog(true);
		AdManager.getInstance(this).setUserDataCollect(true);
		SpotManager.getInstance(this).checkPermission(this);
		
		FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.FILL_PARENT,
				FrameLayout.LayoutParams.WRAP_CONTENT);
		// 设置广告条的悬浮位置
		layoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为右下角
		// 实例化广告条
		AdView adView = new AdView(this, AdSize.FIT_SCREEN);
		this.addContentView(adView, layoutParams);
		// 监听广告条接口
		adView.setAdListener(new AdViewListener() {
			@Override
			public void onSwitchedAd(AdView arg0) {
				Log.i("YoumiAdDemo", "广告条切换");
			}
			@Override
			public void onReceivedAd(AdView arg0) {
				Log.i("YoumiAdDemo", "请求广告成功");
			}
			@Override
			public void onFailedToReceivedAd(AdView arg0) {
				Log.i("YoumiAdDemo", "请求广告失败");
			}
		});
		
		// 加载插播资源
		SpotManager.getInstance(this).loadSpotAds();
		SpotManager.getInstance(this).setShowInterval(20);// 设置20秒的显示时间间隔
		SpotManager.getInstance(this).setSpotOrientation(
				SpotManager.ORIENTATION_PORTRAIT);
	}
	
	public void showSpotAds(){
		// 展示插播广告，可以不调用loadSpot独立使用
		if(SpotManager.getInstance(this).checkLoadComplete()){
			SpotManager.getInstance(AppActivity.this).showSpotAds(
					AppActivity.this, new SpotDialogListener() {
						@Override
						public void onShowSuccess() {
							Log.i("YoumiAdDemo", "展示成功");
						}
						@Override
						public void onShowFailed() {
							Log.i("YoumiAdDemo", "展示失败");
						}
						@Override
						public void onSpotClosed() {
							Log.e("YoumiAdDemo", "插屏关闭");
						}
					}); // //
		}
		// 可以根据需要设置Theme，如下调用，如果无特殊需求，直接调用上方的接口即可
		// SpotManager.getInstance(YoumiAdDemo.this).showSpotAds(YoumiAdDemo.this,
		// android.R.style.Theme_Translucent_NoTitleBar);
		// //
	}
	
	private void initShareSDK(){
		ShareSDKUtils.prepare();
	}
	
	@Override
	public void onBackPressed() {
		// 如果有需要，可以点击后退关闭插播广告。
		if (!SpotManager.getInstance(AppActivity.this).disMiss(true)) {
			super.onBackPressed();
		}
	}
	
	@Override
	protected void onStop() {
		// 如果不调用此方法，则按home键的时候会出现图标无法显示的情况。
		SpotManager.getInstance(AppActivity.this).disMiss(false);
		super.onStop();
	}
	
	@Override
	protected void onDestroy() {
		SpotManager.getInstance(this).unregisterSceenReceiver();
		super.onDestroy();
	}
}
