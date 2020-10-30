//
//  SpotzCNCCustomerSDK.h
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 29/01/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

#import <SpotzCNCCustomerSDK/SpotzCNCProtocol.h>

@interface SpotzCNCCustomerSDK : NSObject

/**
 * The shared instance for all SDK usage after initWithAppId:
 * @return shared SpotzCNCCustomerSDK is the current instance of the SDK
 */
+ (nonnull SpotzCNCCustomerSDK * )shared;

/**
 * Initialises and configures the SDK with an appId, spotzAppKey, and cncAppKey from the Spotz Console.
 * @param appId The application identifier from the Spotz Console
 * @param spotzAppKey The application key from the Spotz Console
 * @param cncAppKey The Collections application key from the Spotz Console
 * @param delegate The delegate which should receive events with updates from the SDK
 * @param dataSource The data source which should provide additional to the SDK
 * @param options The initialisation options which can be provided to tweak the SDK on startup
 */
+ (void)initWithAppId:(NSString * _Nonnull)appId spotzAppKey:(NSString * _Nonnull)spotzAppKey cncAppKey:(NSString * _Nonnull)cncAppKey delegate:(id _Nonnull)delegate dataSource:(id _Nullable)dataSource options:(NSDictionary * _Nullable)options;

+ (NSString * _Nonnull)sdkVersion;

// SDK Usage
/**
 * Start configured location, beacons and geofences. This needs to be called after successful initialisation of the SDK. See https://localz.github.io/spotz-cnc-sdk-docs/?objective_c#4-start-services for example on how to implement it.
 */
- (void)startSpotzCNC;

/**
 * Stops monitoring of location, beacons and geofences.
 */
- (void)stopSpotzCNC;

/**
 * Retrieves current customer information
 * @return customer object
 */
- (SpotzCNCCustomer * _Nullable)currentCustomer;

/**
 * Checks whether customer has verified their email. This can be turned on/off via Localz’s CNC console
 */
- (void)verifyCustomer;

/**
 * Checks whether an order can be checked in.
 * @param order Order object to check
 * @return true if order can be checked in, false if not
 */
- (BOOL)canCheckInOrder:(SpotzCNCOrder * _Nonnull)order;

/**
 * Registers a customer with email address as their username. The customer must verify their email before they can be used. Then use verifyCustomer method to verify locally once they have been verified.
 * @param email Email address to verify
 * @param otherParameters Parameters to configure email registration
 * @param completion Returns error if any, nil if successful
 */
- (void)registerCustomerWithEmail:(NSString * _Nonnull)email otherParameters:(NSDictionary * _Nullable)otherParameters completion:(void(^ _Nullable)(NSError * _Nullable error ))completion;

/**
 * Registers a customer with a username and password. This will create a username/password entry in the system. This needs to be enabled via Localz’s configuration dashboard
 * @param username Username to login
 * @param password Password to register
 * @param otherParameters Parameters to configure email registration
 * @param completion Returns error if any, nil if successful
 */
- (void)registerCustomerWithUsername:(NSString * _Nonnull)username password:(NSString * _Nonnull)password otherParameters:(NSDictionary * _Nullable)otherParameters completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Logs user in using a username and password.
 * @param email Username/email to login
 * @param password Password to register
 * @param completion Returns error if any, nil if successful
 */
- (void)loginCustomerWithUsername:(NSString * _Nonnull)email password:(NSString * _Nonnull)password completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Logs user out and returns status
 * @param success completion block to execute when successful
 * @param failure completion block to execute when failed
 */
- (void)logoutCustomerWithSuccess:(void(^ _Nullable)(void))success failure:(void(^ _Nullable)(NSError * _Nullable error))failure;

/**
 * Retrieves non-completed orders and checks customer location - if recheck is true - to trigger any checkin event
 * @param recheck Set to true to recheck location of customer. This will trigger the notification events which you can capture. You may want to set this to false if you only want to retrieve orders without triggering any notification events.
 * @param completion Completion block with returns orders (nil if none) or error if any
 */
- (void)retrieveOrdersWithRecheckLocation:(BOOL)recheck completion:(void(^ _Nullable)(NSArray<SpotzCNCOrder *> * _Nullable orders, NSError * _Nullable error))completion;

/**
 * Check if user at the right location/store/site and retrieves latest orders.
 * @param completion callback which returns list of orders (nil of none) or error if any
 */
- (void)checkLocationAndRetrieveOrdersWithCompletion:(void(^ _Nullable)(NSArray<SpotzCNCOrder *> * _Nullable orders, NSError * _Nullable error))completion DEPRECATED_MSG_ATTRIBUTE("Implement retrieveOrdersWithRecheckLocation:completion: instead");

/**
 * Retrieves non-completed orders and checks customer location - if recheck is true - to trigger any checkin event
 * @param recheck Set to true to recheck location of customer
 * @param completion Completion block with returns orders (nil if none) or error if any
 */
- (void)getCustomerNonCompletedOrdersSpotRecheck:(BOOL)recheck completion:(void(^ _Nullable)(NSArray<SpotzCNCOrder *> * _Nullable orders, NSError * _Nullable error))completion DEPRECATED_MSG_ATTRIBUTE("Implement retrieveOrdersWithRecheckLocation:completion: instead");

/**
 * Checks in order which will trigger a checkin event and notify attendants at the order’s store. Please note that this will checkin orders that may be available to checkin for the customer.
 * @param order Order to checkin
 * @param force Forces checkin and ignore order validation
 * @param completion Completion block which returns the number of orders successfully checked in and/or error if any
 */
- (void)checkinOrder:(SpotzCNCOrder * _Nonnull)order force:(BOOL)force completion:(void(^ _Nullable)(NSNumber * _Nullable numOrdersCheckedIn, NSError * _Nullable error))completion;

/**
 * Checks in one order only.
 * @param order Order to checkin
 * @param force Forces checkin and ignore order validation
 * @param completion Completion block which returns the number of orders successfully checked in and/or error if any
 */
- (void)checkinOneOrder:(SpotzCNCOrder * _Nonnull)order force:(BOOL)force completion:(void(^ _Nullable)(NSNumber * _Nullable numOrdersCheckedIn, NSError * _Nullable error))completion;

/**
 * Updates order attribute
 * @param attribute Attribute to update
 * @param order Order to update
 * @param completion Completion block which returns error if any
 */
- (void)updateOrderAttribute:(NSString * _Nonnull)attribute forOrder:(SpotzCNCOrder * _Nonnull)order completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Stores feedback with the following input.
 * @param feedbackComment Free text of the comment
 * @param responsiveness Responsiveness rating (1-5)
 * @param friendliness Friendliness of service rating (1-5)
 * @param usefulness Usefulness of service rating (1-5)
 * @param satisfaction Satisfaction of service rating (1-5)
 * @param orderNumber Order number the feedback belongs to
 * @param completion Completion block which returns error if any
 */
- (void)giveFeedbackComment:(NSString * _Nonnull)feedbackComment responsiveness:(NSNumber * _Nonnull)responsiveness friendliness:(NSNumber * _Nonnull)friendliness usefulness:(NSNumber * _Nonnull)usefulness satisfaction:(NSNumber * _Nonnull)satisfaction orderNumber:(NSString * _Nonnull)orderNumber completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Creates an order with the provided parameters, with allowAutoCheckin and allowCheckinPending defaulted to false
 */
- (void)createOrderWithBranchId:(NSString * _Nonnull)branchId orderNumber:(NSString * _Nonnull)orderNumber date:(NSDate * _Nullable)date deliveryName:(NSString * _Nullable)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber * _Nullable)amount pickupStartDate:(NSDate * _Nullable)pickupStartDate pickupEndDate:(NSDate * _Nullable)pickupEndDate selectedPickupId:(NSString * _Nullable)selectedPickupId totalItems:(NSNumber * _Nullable)totalItems attributes:(NSDictionary * _Nullable)attributes completion:(void(^ _Nullable)(SpotzCNCOrder * _Nullable order,NSError * _Nullable error))completion;

/**
 * Creates an order with the provided parameters
 */
- (void)createOrderWithBranchId:(NSString * _Nonnull)branchId orderNumber:(NSString * _Nonnull)orderNumber date:(NSDate * _Nullable)date deliveryName:(NSString * _Nullable)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber * _Nullable)amount pickupStartDate:(NSDate * _Nullable)pickupStartDate pickupEndDate:(NSDate * _Nullable)pickupEndDate selectedPickupId:(NSString * _Nullable)selectedPickupId totalItems:(NSNumber * _Nullable)totalItems attributes:(NSDictionary * _Nullable)attributes allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin completion:(void(^ _Nullable)(SpotzCNCOrder * _Nullable order,NSError * _Nullable error))completion;

/**
 * Creates a new order for the given branchId
 * @param order Order object to create
 * @param branchId Branch ID to create for
 * @param completion Completion block which returns the created order or error if any
 */
 - (void)createOrder:(SpotzCNCOrder * _Nonnull)order branchId:(NSString * _Nonnull)branchId completion:(void(^ _Nullable)(SpotzCNCOrder * _Nullable order,NSError * _Nullable error))completion;
 
/**
 * Deletes order with the given order number
 * @param orderNumber order number to delete
 * @param completion block which returns error if any
 */
- (void)deleteOrderNumber:(NSString * _Nonnull)orderNumber completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Adds a comment to an order
 * @param orderNumber The order number to add the comment to
 * @param orderStatus This can be either SpotzCNCOrderStatusNotReady, SpotzCNCOrderStatusPendingPicked, SpotzCNCOrderStatusPendingPacked, SpotzCNCOrderStatusReady. If specified, comments only will be added to order if it is in that status
 * @param comments The comment to add to the order
 * @param completion Completion block which returns error if any
 */
- (void)addCommentsToOrder:(NSString * _Nonnull)orderNumber orderStatus:(SpotzCNCOrderStatus)orderStatus comments:(NSString * _Nonnull)comments completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Adds a comment to an order
 * @param orderNumber The order number to add the comment to
 * @param comments The comment to add to the order
 * @param completion Completion block which returns error if any
 */
- (void)addCommentsToOrder:(NSString * _Nonnull)orderNumber comments:(NSString * _Nonnull)comments completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

// Push Configuration

/**
 * Push notification registration with the given device token from Apple.
 * @param deviceToken The device token received from Apple
 */
- (void)applicationDidRegisterForRemoteNotificationsWithDeviceToken:(NSData * _Nonnull)deviceToken;

/**
 * Handles the failure of remote notification registration
 * @param error Error object from Apple
 */
- (void)applicationDidFailToRegisterForRemoteNotificationsWithError:(NSError * _Nonnull)error;

/**
 * Handler to process user notification to a delivered notification
 * @param response The user’s response to the notification
 * @param completionHandler The completion block to execute when you have finished processing the user’s response
 */
- (void)userNotificationCenterDidReceiveNotificationResponse:(UNNotificationResponse * _Nonnull)response withCompletionHandler:(void (^ _Nullable)(void))completionHandler;

/**
 * Handler for remote notification to download data
 * @param userInfo Dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data
 * @param state Runtime state of the app
 * @param completionHandler Completion block to execute when the download operation is complete
 */
- (void)applicationDidReceiveRemoteNotification:(NSDictionary * _Nonnull)userInfo applicationState:(UIApplicationState)state fetchCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

/**
 * Handler to perform any data fetch in the background
 * @param completionHandler Completion block to execute when the download operation is complete
 */
- (void)applicationPerformFetchWithCompletionHandler:(void (^ _Nullable)(UIBackgroundFetchResult))completionHandler;

/**
 * Returns true if device is inside a spot with the given site ID
 * @param siteId Site identifier for the site
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL)isInsideSpotAtSiteId:(NSString * _Nonnull)siteId;

/**
 * Check if the retail store where the order is placed is open so customer can be notified.
 * @return true if store is open
 */
- (BOOL)isTimeToNotifyForOrder:(SpotzCNCOrder * _Nonnull)order;

/**
 * Check if CNC service(configured location, beacons and geofences) has started
 * @return true if SpotzCNC service has started
 */
- (BOOL)isSpotzCNCStarted;

/**
 *  Present a local notification with customised content
 *  @param notification The notification object for customising the request id, text, action type, user info, etc
 */
- (void)presentLocalNotification:(SpotzCNCNotification * _Nonnull)notification;

/**
 * Returns the most recent order for which feedback has been requested by push notification (configured in the Spotz Console).
 * @return order number for which feedback is requested
 */
- (NSString * _Nullable)feedbackRequired;

/**
 * Check if the user has given right location permissions.
 * @return SpotzCNCLocationServices (SpotzCNCLocationServicesNotDetermined, SpotzCNCLocationServicesOn, SpotzCNCLocationServicesOff based on the permissions given by the user.
 */
- (SpotzCNCLocationServices)checkLocationServicesStatus;

/**
 * Prompts user with a location request with the message given in the Info.plist
 */
- (void)promptLocationServices;

/**
 * Prompts user with a notification permission request. Call this method where it makes sense to show the request.
 */

- (void)startNotificationServices;

/*!
 * Request precise location with a purpose key. This is a wrapper to apple's requestTemporaryFullAccuracyAuth with additional checks to handle iOS backward compatibility. Please ensure purpose keys are set in the app prior to using this method.
 * @param purposeKey The purposeKey set in your info plist - see https://developer.apple.com/documentation/corelocation/cllocationmanager/3600217-requesttemporaryfullaccuracyauth for more information
 * @param completion The completion block to call with error if any. Will return error = nil if iOS < 14
 * @return true if already enabled or is iOS < 14, false if request is needed
 */
- (BOOL) requestPreciseLocationWitPurposeKey:(NSString * _Nonnull)purposeKey completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/*!
 * Check if precise location is enabled. Will always return true for < iOS14
 */
- (BOOL) isPreciseLocationEnabled;

@end

FOUNDATION_EXPORT double SpotzCNCCustomerSDKVersionNumber;
FOUNDATION_EXPORT const unsigned char SpotzCNCCustomerSDKVersionString[];
