//
//  SpotzCNCClientSDK.h
//  SpotzCNCClientSDK
//
//  Created by Daniel Sykes-Turner on 19/08/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "SpotzCNCCustomer.h"
#import "SpotzCNCOrder.h"
#import "SpotzCNCLocationStorePickup.h"
#import "SpotzCNCLocationStore.h"
#import "SpotzCNCCustomerConstants.h"
#import "SpotzCNCError.h"

typedef enum {
    SpotzCNCLocationServicesNotDetermined = 0,
    SpotzCNCLocationServicesOn,
    SpotzCNCLocationServicesOff
} SpotzCNCLocationServices;

@protocol SpotzCNCCustomerSDKManagerDelegate <NSObject>
- (void)spotzCNCSDKInitSuccessful;
- (void)spotzCNCSDKInitFailed:(NSError *)error;
- (void)spotzCNCSDKFailed:(NSError *)error;
- (void)spotzCNCSDKConfirmedCustomerRegistration;
- (void)spotzCNCSDKUpdateOrders:(NSArray *)orders;
- (void)spotzCNCSDKCompletedOrderPickup:(SpotzCNCOrder *)order;
- (void)spotzCNCSDKBluetoothStateChanged:(BOOL)enabled;
- (void)spotzCNCSDKLocationServicesStateChanged:(BOOL)enabled;
- (void)spotzCNCSDKSetupCompleted;
@end

@protocol SpotzCNCCustomerSDKManagerDataSource <NSObject>
- (NSString *)spotzCNCSDKNotificationMessageWhenEnteringStore:(SpotzCNCLocationStore *)store;
- (NSString *)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder *)order;
@optional
- (BOOL)spotzCNCSDKNotificationMessagePresentCheckinOptionsForOrder:(SpotzCNCOrder *)order;
@end

@interface SpotzCNCCustomerSDK : NSObject

// SDK Setup
+ (SpotzCNCCustomerSDK *)shared;
- (void)setupWithProjectId:(NSString *)projectId spotzProjectKey:(NSString *)spotzProjectKey cncProjectKey:(NSString *)cncProjectKey delegate:(id)delegate dataSource:(id)dataSource options:(NSDictionary *)options;

// SDK Usage
- (void) startSpotzCNC;
- (void) stopSpotzCNC;

- (SpotzCNCCustomer *)currentCustomer;
- (void) verifyCustomer;
- (BOOL)canCheckInOrder:(SpotzCNCOrder *)order;
- (void)registerCustomerWithEmail:(NSString *)email otherParameters:(NSDictionary *)otherParameters completion:(void(^)(NSError *error))completion;
- (void)registerCustomerWithUsername:(NSString *)email password:(NSString *)password completion:(void(^)(NSError *error))completion;
- (void)checkLocationAndRetrieveOrdersWithCompletion:(void(^)(NSArray *orders, NSError *error))completion;
- (void)getCustomerNonCompletedOrdersSpotRecheck:(BOOL)recheck completion:(void(^)(NSArray *orders, NSError *error))completion;
- (void)checkinOrder:(SpotzCNCOrder *)order completion:(void(^)(NSNumber *numOrdersCheckedIn, NSError *error))completion;
- (void)giveFeedbackComment:(NSString *)feedbackComment responsiveness:(NSNumber *)responsiveness friendliness:(NSNumber *)friendliness usefulness:(NSNumber *)usefulness satisfaction:(NSNumber *)satisfaction orderNumber:(NSString *)orderNumber completion:(void(^)(NSError *error))completion;

// Push Configuration
- (void)applicationDidRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
- (void)applicationDidFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
- (void)applicationDidRegisterUserNotificationSettings:(UIUserNotificationSettings *)userNotificationSettings;
- (void)applicationHandleActionWithIdentifier:(NSString *)identifier forLocalNotification:(UILocalNotification *)notification completionHandler:(void (^)())completionHandler;

// Push Usage
- (void)applicationDidReceiveRemoteNotification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state;
- (void)applicationDidReceiveRemoteNotification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;
- (void)applicationDidReceiveActionWithIdentifier:(NSString *)identifier notification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state completionHandler:(void (^)()) handler;

- (BOOL)isInsideSpotAtSiteId:(NSString *)siteId;
- (BOOL) isTimeToNotifyForOrder:(SpotzCNCOrder *)order;

- (void)deregisterCustomer;

- (NSString *) feedbackRequired;

- (NSString *) assetsBaseURLForEnv:(NSString *)env ssl:(BOOL)ssl;

- (SpotzCNCLocationServices) checkLocationServicesStatus;
- (void) promptLocationServices;
- (void) startNotificationServices;

@end