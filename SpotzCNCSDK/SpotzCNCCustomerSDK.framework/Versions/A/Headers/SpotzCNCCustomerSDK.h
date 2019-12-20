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
+ (SpotzCNCCustomerSDK *)shared;

/**
 * Initialises and configures the SDK with an appId, spotzAppKey, and cncAppKey from the Spotz Console.
 * @param appId The application identifier from the Spotz Console
 * @param spotzAppKey The application key from the Spotz Console
 * @param cncAppKey The Collections application key from the Spotz Console
 * @param delegate The delegate which should receive events with updates from the SDK
 * @param dataSource The data source which should provide additional to the SDK
 * @param options The initialisation options which can be provided to tweak the SDK on startup
 */
+ (void)initWithAppId:(NSString *)appId spotzAppKey:(NSString *)spotzAppKey cncAppKey:(NSString *)cncAppKey delegate:(id)delegate dataSource:(id)dataSource options:(NSDictionary *)options;

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
- (SpotzCNCCustomer *)currentCustomer;

/**
 * Checks whether customer has verified their email. This can be turned on/off via Localz’s CNC console
 */
- (void)verifyCustomer;

/**
 * Checks whether an order can be checked in.
 * @param order Order object to check
 * @return true if order can be checked in, false if not
 */
- (BOOL)canCheckInOrder:(SpotzCNCOrder *)order;

/**
 * Registers a customer with email address as their username. The customer must verify their email before they can be used. Then use verifyCustomer method to verify locally once they have been verified.
 * @param email Email address to verify
 * @param otherParameters Parameters to configure email registration
 * @param completion Returns error if any, nil if successful
 */
- (void)registerCustomerWithEmail:(NSString *)email otherParameters:(NSDictionary *)otherParameters completion:(void(^)(NSError *error))completion;

/**
 * Registers a customer with a username and password. This will create a username/password entry in the system. This needs to be enabled via Localz’s configuration dashboard
 * @param username Username to login
 * @param password Password to register
 * @param otherParameters Parameters to configure email registration
 * @param completion Returns error if any, nil if successful
 */
- (void)registerCustomerWithUsername:(NSString *)username password:(NSString *)password otherParameters:(NSDictionary *)otherParameters completion:(void(^)(NSError *error))completion;

/**
 * Logs user in using a username and password.
 * @param email Username/email to login
 * @param password Password to register
 * @param completion Returns error if any, nil if successful
 */
- (void)loginCustomerWithUsername:(NSString *)email password:(NSString *)password completion:(void(^)(NSError *error))completion;

/**
 * Logs user out and returns status
 * @param success completion block to execute when successful
 * @param failure completion block to execute when failed
 */
- (void)logoutCustomerWithSuccess:(void(^)(void))success failure:(void(^)(NSError *error))failure;

/**
 * Check if user at the right location/store/site and retrieves latest orders
 * @param completion callback which returns list of orders (nil of none) or error if any
 */
- (void)checkLocationAndRetrieveOrdersWithCompletion:(void(^)(NSArray *orders, NSError *error))completion;

/**
 * Retrieves non-completed orders and checks customer location - if recheck is true - to trigger any checkin event
 * @param recheck Set to true to recheck location of customer
 * @param completion Completion block with returns orders (nil if none) or error if any
 */
- (void)getCustomerNonCompletedOrdersSpotRecheck:(BOOL)recheck completion:(void(^)(NSArray *orders, NSError *error))completion;

/**
 * Checks in order which will trigger a checkin event and notify attendants at the order’s store. Please note that this will checkin orders that may be available to checkin for the customer.
 * @param order Order to checkin
 * @param force Forces checkin and ignore order validation
 * @param completion Completion block which returns the number of orders successfully checked in and/or error if any
 */
- (void)checkinOrder:(SpotzCNCOrder *)order force:(BOOL)force completion:(void(^)(NSNumber *numOrdersCheckedIn, NSError *error))completion;

/**
 * Checks in one order only.
 * @param order Order to checkin
 * @param force Forces checkin and ignore order validation
 * @param completion Completion block which returns the number of orders successfully checked in and/or error if any
 */
- (void)checkinOneOrder:(SpotzCNCOrder *)order force:(BOOL)force completion:(void(^)(NSNumber *numOrdersCheckedIn, NSError *error))completion;

/**
 * Updates order attribute
 * @param attribute Attribute to update
 * @param order Order to update
 * @param completion Completion block which returns error if any
 */
- (void)updateOrderAttribute:(NSString *)attribute forOrder:(SpotzCNCOrder *)order completion:(void(^)(NSError *error))completion;

/**
 * Stores feedback with the following input.
 * @param feedbackComment Free text of the comment
 * @param responsiveness Responsiveness rating
 * @param friendliness Friendliness of service rating
 * @param usefulness Usefulness of service rating
 * @param satisfaction Satisfaction of service rating
 * @param orderNumber Order number the feedback belongs to
 * @param completion Completion block which returns error if any
 */
- (void)giveFeedbackComment:(NSString *)feedbackComment responsiveness:(NSNumber *)responsiveness friendliness:(NSNumber *)friendliness usefulness:(NSNumber *)usefulness satisfaction:(NSNumber *)satisfaction orderNumber:(NSString *)orderNumber completion:(void(^)(NSError *error))completion;

/**
 * Creates an order with the provided parameters, with allowAutoCheckin and allowCheckinPending defaulted to false
 */
- (void)createOrderWithBranchId:(NSString *)branchId orderNumber:(NSString *)orderNumber date:(NSDate *)date deliveryName:(NSString *)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber *)amount pickupStartDate:(NSDate *)pickupStartDate pickupEndDate:(NSDate *)pickupEndDate selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)attributes completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion;

/**
 * @deprecated
 */
- (void)createOrderWithBranchId:(NSString *)branchId orderNumber:(NSString *)orderNumber orderDate:(NSDate *)orderDate deliveryName:(NSString *)deliveryName orderStatus:(SpotzCNCOrderStatus)status orderAmount:(NSString *)orderAmount pickupStart:(NSDate *)pickupStart pickupEnd:(NSDate *)pickupEnd selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)specific completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion __deprecated_msg("orderAmount is no longer supporting NSString class. Use alternative createOrderWithBranchId: instead.");

/**
 * Creates an order with the provided parameters
 */
- (void)createOrderWithBranchId:(NSString *)branchId orderNumber:(NSString *)orderNumber date:(NSDate *)date deliveryName:(NSString *)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber *)amount pickupStartDate:(NSDate *)pickupStartDate pickupEndDate:(NSDate *)pickupEndDate selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)attributes allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion;

/**
 * @deprecated Use createOrderWithBranchId:orderNumber:date:deliveryName:status:amount:pickupStartDate:pickupEndDate:selectedPickupId:totalItems:attributes:allowCheckinPending:allowAutoCheckin
 */
- (void)createOrderWithBranchId:(NSString *)branchId orderNumber:(NSString *)orderNumber orderDate:(NSDate *)orderDate deliveryName:(NSString *)deliveryName orderStatus:(SpotzCNCOrderStatus)status orderAmount:(NSString *)orderAmount pickupStart:(NSDate *)pickupStart pickupEnd:(NSDate *)pickupEnd selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)specific allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion __deprecated_msg("orderAmount is no longer supporting NSString class. Use alternative createOrderWithBranchId: instead.");

/**
 * Creates a new order for the given branchId
 * @param order Order object to create
 * @param branchId Branch ID to create for
 * @param completion Completion block which returns the created order or error if any
 */
 - (void)createOrder:(SpotzCNCOrder *)order branchId:(NSString *)branchId completion:(void(^)(SpotzCNCOrder *order,NSError *error))completion;
 
/**
 * Deletes order with the given order number
 * @param orderNumber order number to delete
 * @param completion block which returns error if any
 */
- (void)deleteOrderNumber:(NSString *)orderNumber completion:(void(^)(NSError *error))completion;

/**
 * Adds a comment to an order
 * @param orderNumber The order number to add the comment to
 * @param orderStatus This can be either SpotzCNCOrderStatusNotReady, SpotzCNCOrderStatusPendingPicked, SpotzCNCOrderStatusPendingPacked, SpotzCNCOrderStatusReady. If specified, comments only will be added to order if it is in that status
 * @param comments The comment to add to the order
 * @param completion Completion block which returns error if any
 */
- (void)addCommentsToOrder:(NSString *)orderNumber orderStatus:(SpotzCNCOrderStatus)orderStatus comments:(NSString *)comments completion:(void(^)(NSError *error))completion;

/**
 * Adds a comment to an order
 * @param orderNumber The order number to add the comment to
 * @param comments The comment to add to the order
 * @param completion Completion block which returns error if any
 */
- (void)addCommentsToOrder:(NSString *)orderNumber comments:(NSString *)comments completion:(void(^)(NSError *error))completion;

// Push Configuration

/**
 * Push notification registration with the given device token from Apple.
 * @param deviceToken The device token received from Apple
 */
- (void)applicationDidRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/**
 * Handles the failure of remote notification registration
 * @param error Error object from Apple
 */
- (void)applicationDidFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

/**
 * Registers the user notification settings
 * @param userNotificationSettings The notification settings for the app
 */
- (void)applicationDidRegisterUserNotificationSettings:(UIUserNotificationSettings *)userNotificationSettings;

/**
 * Handler for local notification action
 * @param identifier The identifier associated with the custom action. This string corresponds to the identifier from the UILocalNotificationAction object that was used to configure the action in the local notification
 * @param notification The location notification object that was triggered
 * @param completionHandler The block to execute when you are finished performing the specified action. You must call this block at the end of your method
 */
- (void)applicationHandleActionWithIdentifier:(NSString *)identifier forLocalNotification:(UILocalNotification *)notification completionHandler:(void (^)(void))completionHandler;

/**
 * Handler to process user notification to a delivered notification
 * @param response The user’s response to the notification
 * @param completionHandler The completion block to execute when you have finished processing the user’s response
 */
- (void)userNotificationCenterDidReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)(void))completionHandler API_AVAILABLE(ios(10.0));

/**
 * Handler for remote notification
 * @param userInfo Dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data
 * @param state Runtime state of the app
 */
- (void)applicationDidReceiveRemoteNotification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state;

/**
 * Handler for remote notification to download data
 * @param userInfo Dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data
 * @param state Runtime state of the app
 * @param completionHandler Completion block to execute when the download operation is complete
 */
- (void)applicationDidReceiveRemoteNotification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

/**
 * Handler for push notification action
 * @param identifier Identifier associated with the custom action
 * @param userInfo Dictionary that contains information related to the remote notification
 * @param state Runtime state of the app
 * @param handler Completion block to execute once the method is finished
 */
- (void)applicationDidReceiveActionWithIdentifier:(NSString *)identifier notification:(NSDictionary *)userInfo applicationState:(UIApplicationState)state completionHandler:(void (^)(void)) handler;


/**
 * Handler to perform any data fetch in the background
 * @param completionHandler Completion block to execute when the download operation is complete
 */
- (void)applicationPerformFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

/**
 * Returns true if device is inside a spot with the given site ID
 * @param siteId Site identifier for the site
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL)isInsideSpotAtSiteId:(NSString *)siteId;

/**
 * Check if the retail store where the order is placed is open so customer can be notified.
 * @return true if store is open
 */
- (BOOL)isTimeToNotifyForOrder:(SpotzCNCOrder *)order;

/**
 * Check if CNC service(configured location, beacons and geofences) has started
 * @return true if SpotzCNC service has started
 */
- (BOOL)isSpotzCNCStarted;

/**
 *  Present a local notification with customised content
 *  @param notification The notification object for customising the request id, text, action type, user info, etc
 */
- (void)presentLocalNotification:(SpotzCNCNotification *)notification;

/**
 * Presents Local Notification with customised message.
 * @param requestId Unique Id. If non-unique, then the last notification will be overwritten
 * @param message Customised message to be shown to the user
 * @param userInfo Any information to be passed into the local notification. Ex: orderNumber. This is optional
 * @param categoryIdentifier Category identifer required for UNMutableNotificationContent. This can be nil and is optional as this is set already by the SDK. See https://localz.github.io/spotz-cnc-sdk-docs/?objective_c#2-local-notifications for example on how to implement it.
 */
- (void)presentLocalNotificationWithRequestId:(NSString *)requestId message:(NSString *)message userInfo:(NSDictionary *)userInfo categoryIdentifier:(NSString *)categoryIdentifier __deprecated_msg("Please use presentLocalNotification: instead");

/**
 * Returns the most recent order for which feedback has been requested by push notification (configured in the Spotz Console).
 * @return order number for which feedback is requested
 */
- (NSString *)feedbackRequired;

/**
 * @deprecated This method is deprecated and should no longer be used.
 */
- (NSString *)assetsBaseURLForEnv:(NSString *)env ssl:(BOOL)ssl __deprecated_msg("This method is deprecated and should no longer be used");

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

@end
