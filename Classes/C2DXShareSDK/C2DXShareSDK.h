//
//  C2DXShareSDK.h
//  C2DXShareSDKSample
//
//  Created by 鍐�楦挎澃 on 13-12-17.
//
//

#ifndef __C2DXShareSDKSample__C2DXShareSDK__
#define __C2DXShareSDKSample__C2DXShareSDK__

#include <iostream>
#include "cocos2d.h"
#include "C2DXShareSDKTypeDef.h"

USING_NS_CC;

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	ShareSDK
         */
        class C2DXShareSDK
        {
        public:
            
            /**
             *	@brief	鍒濆鍖朣hareSDK
             *
             *	@param 	appKey 	搴旂敤Key
             *	@param 	useAppTrusteeship 	鏄惁浣跨敤搴旂敤淇℃伅鎵樼
             */
            static void open(const char *appKey, bool useAppTrusteeship);

            /**
             *	@brief	鍏抽棴ShareSDK
             */
            static void close();
            
            /**
             *	@brief	璁剧疆骞冲彴閰嶇疆淇℃伅
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *	@param 	configInfo 	閰嶇疆淇℃伅
             */
            static void setPlatformConfig(C2DXPlatType platType, CCDictionary *configInfo);
            
            /**
             *	@brief	鐢ㄦ埛鎺堟潈
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void authorize(C2DXPlatType platType, C2DXAuthResultEvent callback);
            
            /**
             *	@brief	鍙栨秷鐢ㄦ埛鎺堟潈
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             */
            static void cancelAuthorize(C2DXPlatType platType);

            /**
             *	@brief	鐢ㄦ埛鏄惁鎺堟潈
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *
             *	@return	true 宸叉巿鏉冿紝 false 灏氭湭鎺堟潈
             */
            static bool hasAutorized(C2DXPlatType platType);
            
            /**
             *	@brief	鑾峰彇鐢ㄦ埛淇℃伅
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void getUserInfo(C2DXPlatType platType, C2DXGetUserInfoResultEvent callback);

            /**
             *	@brief	鍒嗕韩鍐呭
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *	@param 	content 	鍒嗕韩鍐呭
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void shareContent(C2DXPlatType platType, Dictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	涓�敭鍒嗕韩鍐呭
             *
             *	@param 	platTypes 	骞冲彴绫诲瀷鍒楄〃
             *	@param 	content 	鍒嗕韩鍐呭
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void oneKeyShareContent(Array *platTypes, Dictionary *content, C2DXShareResultEvent callback);

            /**
             *	@brief	鏄剧ず鍒嗕韩鑿滃崟
             *
             *	@param 	platTypes 	骞冲彴绫诲瀷鍒楄〃
             *	@param 	content 	鍒嗕韩鍐呭
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void showShareMenu(Array *platTypes, Dictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	鏄剧ず鍒嗕韩鑿滃崟 
             *
             *	@param 	platTypes 	骞冲彴绫诲瀷鍒楄〃
             *	@param 	content 	鍒嗕韩鍐呭
             *	@param 	pt          寮瑰嚭鍒嗕韩鑿滃崟鐨勪綅缃紝浠呯敤浜庤缃甶Pad鍒嗕韩鑿滃崟寮瑰嚭
             *  @param  direction   寮瑰嚭鍒嗕韩鑿滃崟鎸囧悜锛屼粎鐢ㄤ簬璁剧疆iPad鍒嗕韩鑿滃崟寮瑰嚭
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void showShareMenu(Array *platTypes, Dictionary *content, Point pt, C2DXMenuArrowDirection direction, C2DXShareResultEvent callback);
            
            /**
             *	@brief	鏄剧ず鍒嗕韩瑙嗗浘
             *
             *	@param 	platType 	骞冲彴绫诲瀷
             *	@param 	content 	鍒嗕韩鍐呭
             *	@param 	callback 	鍥炶皟鏂规硶
             */
            static void showShareView(C2DXPlatType platType, Dictionary *content, C2DXShareResultEvent callback);

            /**
             * @brief 鏄剧ず涓�釜娑堟伅
             * @param msg 娑堟伅鍐呭
             */
            static void toast(const char *msg);
        };
    }
}

#endif /* defined(__C2DXShareSDKSample__C2DXShareSDK__) */
