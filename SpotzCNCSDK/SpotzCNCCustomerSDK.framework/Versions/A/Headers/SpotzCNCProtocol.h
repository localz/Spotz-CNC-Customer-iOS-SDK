//
//  SpotzCNCProtocol.h
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 18/10/18.
//  Copyright © 2018 Localz Pty Ltd. All rights reserved.
//

// Forward class delcarations for this header
// You will still need to import them seperately before use
@class SpotzCNCNotification;
@class SpotzData;
@class SpotzSiteDetails;

// Models
#import <SpotzCNCCustomerSDK/SpotzCNCCustomer.h>
#import <SpotzCNCCustomerSDK/SpotzCNCLocationStore.h>
#import <SpotzCNCCustomerSDK/SpotzCNCLocationStorePickup.h>
#import <SpotzCNCCustomerSDK/SpotzCNCOrder.h>
#import <SpotzCNCCustomerSDK/SpotzCNCAttendant.h>
// Networking
#import <SpotzCNCCustomerSDK/SpotzCNCError.h>
// Tools
#import <SpotzCNCCustomerSDK/SpotzCNCCustomerConstants.h>

#ifndef SpotzCNCProtocol_h
#define SpotzCNCProtocol_h

@protocol SpotzCNCCustomerSDKManagerDelegate <NSObject>

/**
 * Called when SDK is successfully initialised
 */
- (void)spotzCNCSDKInitSuccessful;

/**
 * Called when SDK init returns an error
 * @param error Error object returned by the init
 */
- (void)spotzCNCSDKInitFailed:(NSError *)error;

@optional

/**
 * Return true to record activity for spot
 * @param spot SpotzData object that was triggered
 * @param activity SpotzCNCActivityType type that was triggered
 * @param order Order object that this event was related to
 * @return Return true to record. Default is false.
 */
- (BOOL)spotzCNCSDKShouldRecordActivityForSpot:(SpotzData *)spot activity:(SpotzCNCActivityType)activity order:(SpotzCNCOrder *)order;

/**
 * Called when SDK receives a customer registration confirmation from the Localz server
 */
- (void)spotzCNCSDKConfirmedCustomerRegistration;

/**
 * Called when details of non-completed have been updated.
 * @param orders Array of non-completed orders
 */
- (void)spotzCNCSDKUpdateOrders:(NSArray *)orders;

/**
 * Called when order has been completed
 * @param order Order object this event belongs to
 */
- (void)spotzCNCSDKCompletedOrderPickup:(SpotzCNCOrder *)order;

/**
 * Called when bluetooth state changed. Only relevant when beacon is used in the implementation.
 * @param enabled True if enabled, False if not
 */
- (void)spotzCNCSDKBluetoothStateChanged:(BOOL)enabled;

/**
 * Called when location services permission state changed.
 * @param enabled True if enabled, False if not
 */
- (void)spotzCNCSDKLocationServicesStateChanged:(BOOL)enabled;

/**
 * Called when one of the push notification’s actions is selected
 * @param index Index of the action
 * @param order Order object that this action is related to
 */
- (void)spotzCNCSDKNotificationDidSelectActionAtIndex:(int)index order:(SpotzCNCOrder *)order;

@end

@protocol SpotzCNCCustomerSDKManagerDataSource <NSObject>
@optional

/**
 * The delegate to provide custom push notification message for when customer entering a store/site area which has an order ready for checkin
 * @param store The store object that customer entered
 * @param order The related order object that was triggered by this event
 * @return Return custom message to be presented in the push notification
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenEnteringStore:(SpotzCNCLocationStore * _Nonnull)store order:(SpotzCNCOrder * _Nonnull)order __deprecated_msg("Please use spotzCNCSDKNotificationOnSiteEntry:order instead");

/**
 * The custom message to display when order is checked in while app is in the background.
 * @param order Order object to checkin
 * @return Return custom message to be presented in the push notification
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder * _Nullable)order __deprecated_msg("Please use spotzCNCSDKNotificationWhenCheckingInOrder:error instead");

/**
 * The custom message to display when order is cannot be checked in while app is in the background.
 * @note If implemented, this method will take preference over spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:
 * @param order Order object to checkin
 * @param error Error object containing reason of why order cannot be checked in
 * @return Return custom message to be presented in the push notification.
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder * _Nullable)order error:(NSError * _Nullable)error __deprecated_msg("Please use spotzCNCSDKNotifiationWhenCheckingInOrder:error instead");

/**
 * This is called during spot events, e.g. enter/exit Spot. The event information is in the SpotzData object. You can return additional information that will be stored in the event log.
 * @param spot SpotzData object that contains the event information
 * @return List of key:value to be stored on the server as part of the event record. Default is nil.
 */
- (NSDictionary *)spotzCNCSDKRecordActivityAttributesForSpot:(SpotzData *)spot;

/**
 * Return true to use the custom category
 * @param order Order object that this category will be presented for
 * @return Return true to enable custom category. Default is false.
 */
- (BOOL)spotzCNCSDKNotificationMessagePresentCheckinOptionsForOrder:(SpotzCNCOrder *)order;

/**
 * This is called when the CNC SDK is initialised as the SDK needs to set the number of custom actions required for local notifications. This is optional. If not set, the default actions `checkInNow` and `checkInLater` will kick in.
 * @return int value specifying the number of actions
 */
- (int)spotzCNCSDKNotificationNumberOfActions;

/**
 * This is called when the CNC SDK is initialised as the SDK needs to set the titles for subsequent action for a local notification.
 * This is optional. If not set, default titles set as part of `options` dictionary in CNC initialisation will be used.
 * @param index The button index of a local notification for which the title needs to be set
 * @return String value to be associated with the local notification buttons
 */
- (NSString *)spotzCNCSDKNotificationActionTitleForIndex:(int)index;

/**
 *  This is called when the user enters a site's region (such as a geofence or beacon) while the app is asleep or inactive.
 *  It gives the app a chance to display a notification to the user based on the site and the order (if provided).
 *  NOTE: The data source method `spotzCNCSDKNotificationWhenCheckingInOrder:error` will take precedence if it can be called.
 *  @param site The site that as just been entered into by the user
 *  @param order An order for the site which is ready to be collected. If no orders can be collected then this will be nil.
 *  @return A SpotzCNCNotification object which will be displayed to the user.
 */
- (SpotzCNCNotification * _Nullable)spotzCNCSDKNotificationOnSiteEntry:(SpotzSiteDetails * _Nonnull)site order:(SpotzCNCOrder * _Nullable)order;

/**
 *  This is called when an order is checked in by a notification's "check-in" button, or automatically due to a geofence/beacon trigger while the app is asleep or inactive.
 *  It gives the app a chance to display a notification to the user based on the order checked in.
 *  If the order check in fails then the app can also display a notification based on the error which occured to the user and ask them to check in using the app instead.
 *  @param order The order which has just been checked in.
 *  @param error The error in the case that the order check in fails.
 *  @return A SpotzCNCNotification object which will be displayed to the user.
 */
- (SpotzCNCNotification * _Nullable)spotzCNCSDKNotificationWhenCheckingInOrder:(SpotzCNCOrder * _Nullable)order error:(NSError * _Nullable)error;

@end

#endif /* SpotzCNCProtocol_h */