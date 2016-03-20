//
//  SpotzCNCCustomerSDK.h
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 29/01/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SpotzCNCCustomer.h"
#import "SpotzCNCOrder.h"
#import "SpotzCNCLocationStorePickup.h"
#import "SpotzCNCLocationStore.h"
#import "SpotzCNCCustomerConstants.h"
#import "SpotzCNCError.h"
#import <SpotzSDK/SpotzData.h>
#import <SpotzSDK/SpotzErrorType.h>

typedef enum {
    SpotzCNCLocationServicesNotDetermined = 0,
    SpotzCNCLocationServicesOn,
    SpotzCNCLocationServicesOff
} SpotzCNCLocationServices;

@protocol SpotzCNCCustomerSDKManagerDelegate <NSObject>
- (void)spotzCNCSDKInitSuccessful;
- (void)spotzCNCSDKInitFailed:(NSError *)error;
@optional
- (BOOL)spotzCNCSDKShouldRecordActivityForSpot:(SpotzData *)spot;
- (void)spotzCNCSDKConfirmedCustomerRegistration;
- (void)spotzCNCSDKUpdateOrders:(NSArray *)orders;
- (void)spotzCNCSDKCompletedOrderPickup:(SpotzCNCOrder *)order;
- (void)spotzCNCSDKBluetoothStateChanged:(BOOL)enabled;
- (void)spotzCNCSDKLocationServicesStateChanged:(BOOL)enabled;
@end

@protocol SpotzCNCCustomerSDKManagerDataSource <NSObject>
- (NSString *)spotzCNCSDKNotificationMessageWhenEnteringStore:(SpotzCNCLocationStore *)store;
- (NSString *)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder *)order;
@optional
- (NSDictionary *)spotzCNCSDKRecordActivityAttributesForSpot:(SpotzData *)spot;
- (BOOL)spotzCNCSDKNotificationMessagePresentCheckinOptionsForOrder:(SpotzCNCOrder *)order;
@end

@interface SpotzCNCCustomerSDK : NSObject

// SDK Setup
+ (SpotzCNCCustomerSDK *)shared;
+ (void)initWithAppId:(NSString *)appId spotzAppKey:(NSString *)spotzAppKey cncAppKey:(NSString *)cncAppKey delegate:(id)delegate dataSource:(id)dataSource options:(NSDictionary *)options;

// SDK Usage
- (void)startSpotzCNC;
- (void)stopSpotzCNC;

- (SpotzCNCCustomer *)currentCustomer;
- (void)verifyCustomer;
- (BOOL)canCheckInOrder:(SpotzCNCOrder *)order;
- (void)registerCustomerWithEmail:(NSString *)email otherParameters:(NSDictionary *)otherParameters completion:(void(^)(NSError *error))completion;
- (void)registerCustomerWithUsername:(NSString *)email password:(NSString *)password otherParameters:(NSDictionary *)otherParameters completion:(void(^)(NSError *error))completion;
- (void)loginCustomerWithUsername:(NSString *)email password:(NSString *)password completion:(void(^)(NSError *error))completion;
- (void)logoutCustomerWithSuccess:(void(^)())success failure:(void(^)(NSError *error))failure;

- (void)checkLocationAndRetrieveOrdersWithCompletion:(void(^)(NSArray *orders, NSError *error))completion;
- (void)getCustomerNonCompletedOrdersSpotRecheck:(BOOL)recheck completion:(void(^)(NSArray *orders, NSError *error))completion;
- (void)checkinOrder:(SpotzCNCOrder *)order force:(BOOL)force completion:(void(^)(NSNumber *numOrdersCheckedIn, NSError *error))completion;
- (void)checkinOneOrder:(SpotzCNCOrder *)order force:(BOOL)force completion:(void(^)(NSNumber *numOrdersCheckedIn, NSError *error))completion;
- (void)giveFeedbackComment:(NSString *)feedbackComment responsiveness:(NSNumber *)responsiveness friendliness:(NSNumber *)friendliness usefulness:(NSNumber *)usefulness satisfaction:(NSNumber *)satisfaction orderNumber:(NSString *)orderNumber completion:(void(^)(NSError *error))completion;
- (void)createOrderWithBranchId:(NSString *)branchId orderNumber:(NSString *)orderNumber orderDate:(NSDate *)orderDate deliveryName:(NSString *)deliveryName orderStatus:(SpotzCNCOrderStatus)status orderAmount:(NSString *)orderAmount pickupStart:(NSDate *)pickupStart pickupEnd:(NSDate *)pickupEnd selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)specific completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion;
- (void)createOrder:(SpotzCNCOrder *)order branchId:(NSString *)branchId completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion;
- (void)deleteOrderNumber:(NSString *)orderNumber completion:(void(^)(NSError *error))completion;

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
- (BOOL)isTimeToNotifyForOrder:(SpotzCNCOrder *)order;
- (BOOL)isSpotzCNCStarted;


- (NSString *)feedbackRequired;

- (NSString *)assetsBaseURLForEnv:(NSString *)env ssl:(BOOL)ssl;

- (SpotzCNCLocationServices)checkLocationServicesStatus;
- (void)promptLocationServices;
- (void)startNotificationServices;

@end