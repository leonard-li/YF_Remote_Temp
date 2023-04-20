//
//  YFABTest.h
//  YFConfig
//
//  Created by 李强 on 2023/3/28.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol YFABTestDelegate<NSObject>

@optional
/**
 *  @brief 获取A/B测试回调
 *  @param error 错误信息
 */
-(void)abTestFetchedWithError:(nullable NSError*)error;
/**
 *  @brief A/B测试有更新会触发的回调
 */
-(void)abTestValueChanged:(BOOL)changed;

@end

@interface ABTestExperiment : NSObject

/// 试验参数名
@property (copy, nonatomic) NSString *paramName;
/// 默认值
@property (strong, nonatomic) id defaultValue;
/// 自定义属性
@property (strong, nonatomic) NSDictionary *properties;
/// 试验过期时间戳
@property (assign, nonatomic) NSTimeInterval timeoutInterval;
/// 试验版本
@property (assign, nonatomic) NSTimeInterval version;
/// 试验路径
@property (assign, nonatomic) NSString *path;
/// 是否启用
@property (assign, nonatomic) BOOL enable;
/// 是否命中
@property (assign, nonatomic) BOOL hit;

@end

@interface YFABTest : NSObject

@property(nonatomic, weak) id<YFABTestDelegate> abTestDelegate;

@property (class, nonatomic, readonly) YFABTest *sharedInstance;

+ (void)start:(nullable id<YFABTestDelegate>)delegate;

- (id)getABTestWithKey:(NSString *)key withDedault:(id)defaultValue;

- (void)trackWithProperties:(NSDictionary *)properties;

- (ABTestExperiment *)getABTestExperimentWithKey:(NSString *)key withDedault:(id)defaultValue;

@end

NS_ASSUME_NONNULL_END
