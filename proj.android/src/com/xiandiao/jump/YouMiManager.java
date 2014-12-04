package com.xiandiao.jump;

import net.youmi.android.AdManager;
import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.banner.AdViewListener;
import net.youmi.android.offers.OffersManager;
import net.youmi.android.offers.OffersWallDialogListener;
import net.youmi.android.offers.PointsChangeNotify;
import net.youmi.android.offers.PointsManager;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;

import org.cocos2dx.cpp.AppActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;

public class YouMiManager implements PointsChangeNotify {
	
	// 以下常量为各种功能的标识，值随意起
	private final static int SHOW_SPOT_AD = 100;
	private final static int SHOW_BANNER = 102;
	private final static int HIDE_BANNER = 103;

	private final static int SHOW_OFFER_WALL = 200;
	private final static int SHOW_OFFER_WALL_DIALOG = 201;
	
	private static AppActivity content;
	private AdView mBannerView;
	private LinearLayout mBannerLayout;
	private static Handler handler;
	
	public YouMiManager(AppActivity activity) {
		content = activity;
	}

	public void init(){
		AdManager.getInstance(content).init("4bab86630bbf80a7", "451a4f3fe73c639b", true);
		AdManager.getInstance(content).setEnableDebugLog(true);
		AdManager.getInstance(content).setUserDataCollect(true);
		SpotManager.getInstance(content).checkPermission(content);
		OffersManager.getInstance(content).onAppLaunch();
		PointsManager.getInstance(content).registerNotify(this);
		
		this.initHandler();
		
		this.initSport();
		this.initAdView();
	}
	
	public void initSport(){
		SpotManager.getInstance(content).setShowInterval(10);
		SpotManager.getInstance(content).setSpotOrientation(
				SpotManager.ORIENTATION_PORTRAIT);
		SpotManager.getInstance(content).loadSpotAds();

	}
	
	public void initAdView(){
		showBanner();
	}
	
	public void showBanner(){
		sendMsgToHandler(SHOW_BANNER);
	}
	
	public void hideBanner(){
		sendMsgToHandler(HIDE_BANNER);
	}
	
	public void showOffersWall(){
		sendMsgToHandler(SHOW_OFFER_WALL);
	}
	
	public void showOffersWallDialog(int width, int height){
		sendMsgToHandler(SHOW_OFFER_WALL_DIALOG);
	}
	
	/**
	 * 关闭插屏广告
	 */
	public boolean closeSpotAd() {
		return SpotManager.getInstance(content).disMiss(true);
	}
	
	public void showSpotAds(){
		sendMsgToHandler(SHOW_SPOT_AD);
	}
	
	/**
	 * 获取有米积分 
	 * @return
	 */
	public static int queryPoints(){
		int points = PointsManager.getInstance(content).queryPoints();
		return points;
	}
	
	/**
	 * 扣除积分
	 * @param amount
	 * @return
	 */
	public static boolean spendPoints(int amount){
		boolean isSuccess = PointsManager.getInstance(content).spendPoints(amount);
		return isSuccess;
	}
	
	/**
	 * 增加积分
	 * @param amount
	 * @return
	 */
	public static boolean awardPoints(int amount){
		// 积分墙配置检查（没有使用“通过 Receiver来获取积分订单”功能）：
		boolean flag = OffersManager.getInstance(content).checkOffersAdConfig();
		System.out.println("flag:" + flag);
		// 积分墙配置检查（使用“通过Receiver来获取积分订单”功能）：
		/*flag = OffersManager.getInstance(content).checkOffersAdConfig(true);
		System.out.println("flag:" + flag);*/
		boolean isSuccess = PointsManager.getInstance(content).awardPoints(amount);
		return isSuccess;
	}
	
	private class YouMiAdViewListener implements AdViewListener{
		@Override
		public void onSwitchedAd(AdView arg0) {
			content.adsResultCallback(0);
		}
		@Override
		public void onReceivedAd(AdView arg0) {
			content.adsResultCallback(1);
		}
		@Override
		public void onFailedToReceivedAd(AdView arg0) {
			content.adsResultCallback(2);
		}
	}
	
	public void onBackPressed(){
		SpotManager.getInstance(content).disMiss(true);
	}
	
	public void onStop() {
		SpotManager.getInstance(content).disMiss(false);
	}
	
	public void onDestroy(){
		PointsManager.getInstance(content).unRegisterNotify(this);
		SpotManager.getInstance(content).unregisterSceenReceiver();
		OffersManager.getInstance(content).onAppExit();
	}
	
	private synchronized static void sendMsgToHandler(int type) {
		Message msg = handler.obtainMessage();
		msg.what = type;
		msg.sendToTarget();
	}
	
	@SuppressLint("HandlerLeak")
	private void initHandler(){
		handler = new Handler(){
			@Override
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case SHOW_SPOT_AD:
					SpotManager.getInstance(content).showSpotAds(
							content, new SpotDialogListener() {
								@Override
								public void onShowSuccess() {
									content.adsResultCallback(3);
								}
								@Override
								public void onShowFailed() {
									content.adsResultCallback(4);
								}
								@Override
								public void onSpotClosed() {
									content.adsResultCallback(5);
								}

							});
					break;
				case SHOW_BANNER:
					if( mBannerView == null){
						mBannerView = new AdView(content, AdSize.FIT_SCREEN);
						mBannerView.setAdListener(new YouMiAdViewListener());
						
						// 创建布局来承载广告条
						if (mBannerLayout == null) {
							mBannerLayout = new LinearLayout(content);
							mBannerLayout.setLayoutParams(new LinearLayout.LayoutParams(
									LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
							mBannerLayout.addView(mBannerView);
						}
						// 采用WindowManager来进行
						WindowManager mWindowManager = (WindowManager) content.getSystemService(
								Context.WINDOW_SERVICE);
						WindowManager.LayoutParams mWmParams = new WindowManager.LayoutParams();
						mWmParams.flags = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL
								| WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
						mWmParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
						mWmParams.width = WindowManager.LayoutParams.MATCH_PARENT;
						mWmParams.alpha = 1.0F;
						mWmParams.format = 1;
						mWmParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为：在右下角展示广告条条
						mWindowManager.addView(mBannerLayout, mWmParams);
					}
					break;
				case HIDE_BANNER:
					if (mBannerLayout != null) {
						((WindowManager) content.getSystemService(Context.WINDOW_SERVICE))
								.removeView(mBannerLayout);
						mBannerLayout = null;
						mBannerView = null;
					}
					break;
				case SHOW_OFFER_WALL:
					OffersManager.getInstance(content).showOffersWall();
					break;
				case SHOW_OFFER_WALL_DIALOG:
					OffersManager.getInstance(content).showOffersWallDialog(
							content, new OffersWallDialogListener() {
								@Override
								public void onDialogClose() {
									content.adsResultCallback(6);
								}
							});
					break;
				}
				super.handleMessage(msg);
			}
		};
	}
	
	private native int pointsBalanceChange(int points);

	@Override
	public void onPointBalanceChange(int pointsBalance) {
		this.pointsBalanceChange(pointsBalance);
	}
}
