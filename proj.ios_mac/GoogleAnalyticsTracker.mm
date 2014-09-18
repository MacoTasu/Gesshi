//
//  GoogleAnalyticsTracker.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/09/17.
//
//

#include "GoogleAnalyticsTracker.h"
#include "GAI.h"
#include "GAIDictionaryBuilder.h"
#include "GAIFields.h"

// アプリのトラッキングIDを入れてください。
#define GA_TRACKING_ID  ("UA-41953821-3")

void GoogleAnalyticsTracker::setup()
{
    // GoogleAnalyticsを設定します。
    GAI* gai = [GAI sharedInstance];
    gai.trackUncaughtExceptions     = YES; // キャッチ不可な例外を自動送信します。
    gai.dispatchInterval            = 120; // 送信の時間間隔です。120秒。
    [[gai logger] setLogLevel:kGAILogLevelVerbose]; // ログのレベルを設定。
    [gai trackerWithTrackingId:[NSString stringWithUTF8String:GA_TRACKING_ID]]; // トラッキングIDを設定します。
}

void GoogleAnalyticsTracker::sendScreen(const char* screenName)
{
    GAI* gai = [GAI sharedInstance];
    
    // スクリーン名をパラメータに設定します。
    [gai.defaultTracker set:kGAIScreenName value:[NSString stringWithUTF8String:screenName]];
    NSMutableDictionary* appViewDict = [[GAIDictionaryBuilder createAppView] build];
    [gai.defaultTracker send:appViewDict];
}