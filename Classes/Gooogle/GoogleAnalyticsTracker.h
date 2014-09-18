//
//  GoogleAnalyticsTracker.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/09/17.
//
//

class GoogleAnalyticsTracker
{
public:
    
    /**GoogleAnalyticsへのデータ送信処理を初期化します。*/
    static void setup();
    
    /**
     GoogleAnalyticsにスクリーントラッキング情報を送信します。
     
     @param screenName スクリーン名。
     */
    static void sendAppView(const char* screenName);
    
    /**
     GoogleAnalyticsにイベントトラッキング情報を送信します。
     
     @param category イベントカテゴリ。
     @param action イベントアクション。
     @param label イベントラベル。
     @param value
     */
    static void sendEvent(const char* category,
                          const char* action,
                          const char* label,
                          int value);
    
    static void sendScreen(const char* screenName);
};