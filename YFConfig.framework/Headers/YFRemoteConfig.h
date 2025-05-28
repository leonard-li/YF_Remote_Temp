//
//  YFRemoteConfig.h
//  YFData
//
//  Created by leonard.li on 2023/1/6.
//  Copyright © 2023 yifants. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Indicates whether updated data was successfully fetched.
typedef NS_ENUM(NSInteger, YFRemoteConfigFetchStatus) {
    /// Config has never been fetched.
    YFRemoteConfigFetchStatusNoFetchYet,
    /// Config fetch succeeded.
    YFRemoteConfigFetchStatusSuccess,
    /// Config fetch failed.
    YFRemoteConfigFetchStatusFailure,
    /// Config fetch was throttled.
    YFRemoteConfigFetchStatusThrottled,
};

/// Indicates whether ActiveStatus in the local data .
typedef NS_ENUM(NSInteger, YFRemoteConfigActiveStatus) {
    YFRemoteConfigActiveStatus_None,
    YFRemoteConfigActiveStatus_Ready,
    YFRemoteConfigActiveStatus_Active,
    YFRemoteConfigActiveStatus_Expiration
};

typedef void (^YFRemoteConfigFetchCompletion)(YFRemoteConfigFetchStatus status, NSError *_Nullable error);

typedef void (^YFRemoteConfigActivateCompletion)(NSError *_Nullable error);

@protocol YFRemoteConfigDelegate<NSObject>

@optional
/**
 *  @brief 获取服务器的网络请求的回调
 *  @param status see YFRemoteConfigFetchStatus
 *  @param error 错误信息
 *  @param userInfo  该回调的扩展信息
 *  @note  调用函数触发此回调
 *         fetchWithCompletionHandler
 *         fetchAndActivateWithCompletionHandler
 */
-(void)remoteConfigFetched:(YFRemoteConfigFetchStatus)status
                           error:(nullable NSError*)error
                        userInfo:(nullable id)userInfo;

/**
 *  @brief 远程配置被激活的回调
 *  @param status see YFRemoteConfigActiveStatus
 *  @param error 错误信息
 *  @param userInfo  该回调的扩展信息
 *  @note  调用函数触发此回调
 *         fetchAndActivateWithCompletionHandler
 *         activateWithCompletionHandler
 */
-(void)remoteConfigActivated:(YFRemoteConfigActiveStatus)status
                       error:(nullable NSError*)error
                    userInfo:(nullable id)userInfo;

/**
 *  @brief 配置已经准备就绪
 *  @param status see YFRemoteConfigActiveStatus
 *  @param error 错误信息
 *  @param userInfo  该回调的扩展信息
 *  @note  调用函数触发此回调
 *         fetchWithCompletionHandler
 */
-(void)remoteConfigReady:(YFRemoteConfigActiveStatus)status
                   error:(nullable NSError*)error
                userInfo:(nullable id)userInfo;

@end

/**================================================================**/
@interface YFRemoteConfigSettings : NSObject

/// Indicates the default value in seconds to set for the minimum interval that needs to elapse
/// before a fetch request can again be made to the Remote Config backend. After a fetch request to
/// the backend has succeeded, no additional fetch requests to the backend will be allowed until the
/// minimum fetch interval expires.
/// @note 目前没用，保留字段
@property(nonatomic, assign) NSTimeInterval minimumFetchInterval;
/// Indicates the default value in seconds to abandon a pending fetch request made to the backend.
/// This value is set for outgoing requests as the timeoutIntervalForRequest as well as the
/// timeoutIntervalForResource on the NSURLSession's configuration.
/// @note 目前没用，保留字段
@property(nonatomic, assign) NSTimeInterval fetchTimeout;
///active after fetch config
///获取远程配置后，是否激活
@property(nonatomic, assign) BOOL activateAfterFetch;

///自定义属性
@property(nonatomic, strong) NSDictionary *customProps;

@end

/**================================================================**/
@interface YFRemoteConfig : NSObject

@property(nonatomic, weak) id<YFRemoteConfigDelegate> remoteConfigDelegate;

@property(nonatomic, readwrite, strong) YFRemoteConfigSettings *configSettings;

#pragma mark - init
/**
 *  @brief 远程配置单例
 *  @param delegate  see YFRemoteConfigDelegate
 *  @note 用户初始化时候，
 先调用 remoteConfigWithDelegate:(id<YFRemoteConfigDelegate>)delegate，可以保证上次ready的数据可以回调给用户。
 */
+ (YFRemoteConfig *)remoteConfigWithDelegate:(nullable id<YFRemoteConfigDelegate>)delegate
                          withConfigSettings:(nullable YFRemoteConfigSettings*)configSettings;

+ (YFRemoteConfig *)remoteConfig;

#pragma mark - activate
/**
 *  @brief 激活本地配置
 *  @param completionHandler 回调
 */
+ (void)activateWithCompletionHandler:(nullable YFRemoteConfigActivateCompletion)completionHandler;

#pragma mark - Get Config
/**
 *  @brief 获取配置信息
 *  @param key 对应的key
 *  @note 获取配置的优先顺序，远程配置->Defaults
 */
+ (nullable id)configValueForKey:(nullable NSString *)key;

/**
 *  @brief 获取运营参数
 *  @param key 对应的key
 */
+ (nullable id)optValueForKey:(nullable NSString *)key;

#pragma mark - Defaults
/**
 *  @brief 设置本地默认配置
 *  @param defaults 对应的本地配置
 */
+ (void)setDefaults:(nullable NSDictionary<NSString *, NSObject *> *)defaults;

/**
 *  @brief 设置本地默认配置
 *  @param fileName 包含本地配置的plist文件
 */
+ (void)setDefaultsFromPlistFileName:(nullable NSString *)fileName;

@end

NS_ASSUME_NONNULL_END
