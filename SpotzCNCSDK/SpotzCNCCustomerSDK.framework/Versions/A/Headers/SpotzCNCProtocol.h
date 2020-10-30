//
//  SpotzCNCProtocol.h
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 18/10/18.
//  Copyright © 2018 Localz Pty Ltd. All rights reserved.
//

// Forward class delcarations for SpotzCNCNotification requires seperate importing befoore it can be used
//  (Objective-C)
//      #import <SpotzCNCCustomerSDK/SpotzCNCCustomerSDK.h>
//      #import <SpotzCNCCustomerSDK/SpotzCNCCustomerSDK-Swift.h>
//  (Swift)
//      #import <SpotzCNCCustomerSDK/SpotzCNCCustomerSDK.h> (bridging header)
//      import SpotzCNCCustomerSDK
// Dependencies
#import <SpotzSDK/SpotzSDK.h>
// Models
#import <SpotzCNCCustomerSDK/SpotzCNCNotification.h>
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
- (void)spotzCNCSDKInitFailed:(NSError *_Nullable)error;

@optional

/**
 * Return true to record activity for spot
 * @param spot SpotzData object that was triggered
 * @param activity SpotzCNCActivityType type that was triggered
 * @param order Order object that this event was related to
 * @return Return true to record. Default is false.
 */
- (BOOL)spotzCNCSDKShouldRecordActivityForSpot:(SpotzData *_Nullable)spot activity:(SpotzCNCActivityType)activity order:(SpotzCNCOrder *_Nullable)order;

/**
 * Called when SDK receives a customer registration confirmation from the Localz server
 */
- (void)spotzCNCSDKConfirmedCustomerRegistration;

/**
 * Called when details of non-completed have been updated.
 * @param orders contains all non-completed orders with their updated status (including non-updated orders)
 */
- (void)spotzCNCSDKUpdateOrders:(NSArray<SpotzCNCOrder *> *_Nullable)orders;

/**
 * Called when update is received via remote push notification. This method is useful when you want to know when to refresh the UI..
 * NOTE: SpotzCNCNotificationStatusReady is always sent when order is ready, however SpotzCNCNotificationStatusAcknowledged and SpotzCNCNotificationStatusFeedback is only sent when the order was acknowledged from this device.
 * In the later case you can force refetch the order when they open the app or go to the oder list screen.
 * @param statusUpdate the status of SpotzCNCNotificationStatus will be passed into this
 */
- (void)spotzCNCUpdateReceivedWithStatus:(SpotzCNCNotificationStatus)statusUpdate;

/**
 * Called when update is received via remote push notification. This method is useful when you want to know when to refresh the UI..
 * NOTE: SpotzCNCNotificationStatusReady is always sent when order is ready, however SpotzCNCNotificationStatusAcknowledged and SpotzCNCNotificationStatusFeedback is only sent when the order was acknowledged from this device.
 * In the later case you can force refetch the order when they open the app or go to the oder list screen.
 * @param statusUpdate the status of SpotzCNCNotificationStatus will be passed into this
 * @param order The order that is related to this update. This may be null if there was a delay between push and receiving the notification (ie order may have progressed and/or closed)
 */
- (void)spotzCNCUpdateReceivedWithStatus:(SpotzCNCNotificationStatus)statusUpdate order:(SpotzCNCOrder *_Nullable)order;

/**
 * Called when order has been completed
 * @param order Order object this event belongs to
 */
- (void)spotzCNCSDKCompletedOrderPickup:(SpotzCNCOrder *_Nonnull)order;

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
- (void)spotzCNCSDKNotificationDidSelectActionAtIndex:(int)index order:(SpotzCNCOrder *_Nullable)order;

@end

@protocol SpotzCNCCustomerSDKManagerDataSource <NSObject>
@optional

/**
 * The delegate to provide custom push notification message for when customer entering a store/site area which has an order ready for checkin
 * @param store The store object that customer entered
 * @param order The related order object that was triggered by this event
 * @return Return custom message to be presented in the push notification
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenEnteringStore:(SpotzCNCLocationStore * _Nonnull)store order:(SpotzCNCOrder * _Nonnull)order;

/**
 * This is called during spot events, e.g. enter/exit Spot. The event information is in the SpotzData object. You can return additional information that will be stored in the event log.
 * @param spot SpotzData object that contains the event information
 * @return List of key:value to be stored on the server as part of the event record. Default is nil.
 */
- (NSDictionary *_Nullable)spotzCNCSDKRecordActivityAttributesForSpot:(SpotzData *_Nullable)spot;

/**
 * Return true to use the custom category
 * @param order Order object that this category will be presented for
 * @return Return true to enable custom category. Default is false.
 */
- (BOOL)spotzCNCSDKNotificationMessagePresentCheckinOptionsForOrder:(SpotzCNCOrder *_Nonnull)order;

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
- (NSString *_Nullable)spotzCNCSDKNotificationActionTitleForIndex:(int)index;

/**
 *  This is called when the user enters a site's region (such as a geofence or beacon) while the app is asleep or inactive.
 *  It gives the app a chance to display a notification to the user based on the site.
 *  NOTE: The data source method `spotzCNCSDKNotificationWhenCheckinginOrder:error` will take precedence if it can be called.
 *  @param site The site that as just been entered into by the user
 *  @return A SpotzCNCNotification object which will be displayed to the user.
 */
- (SpotzCNCNotification * _Nullable)spotzCNCSDKNotificationOnSiteEntry:(SpotzSiteDetails * _Nonnull)site;

/**
 *  This is called when an order is checked in by a notification's "check-in" button, or automatically due to a geofence/beacon trigger while the app is asleep or inactive.
 *  It gives the app a chance to display a notification to the user based on the order checked in.
 *  If the order check in fails then the app can also display a notification based on the error which occured to the user and ask them to check in using the app instead.
 *  @param order The order which has just been checked in.
 *  @param error The error in the case that the order check in fails.
 *  @return A SpotzCNCNotification object which will be displayed to the user.
 */
- (SpotzCNCNotification * _Nullable)spotzCNCSDKNotificationWhenCheckinginOrder:(SpotzCNCOrder * _Nullable)order error:(NSError * _Nullable)error;

#pragma mark Deprecated delegates

/**
 * The custom message to display when order is checked in while app is in the background. This delegate is deprecated. Use the spotzCNCSDKNotificationWhenCheckingInOrder:error: delegate instead.
 * @param order Order object to checkin
 * @return Return custom message to be presented in the push notification
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder * _Nullable)order;

/**
 * The custom message to display when order is cannot be checked in while app is in the background. This delegate is deprecated. Use the spotzCNCSDKNotificationWhenCheckingInOrder:error: delegate instead.
 * @param order Order object to checkin
 * @param error Error object containing reason of why order cannot be checked in
 * @return Return custom message to be presented in the push notification.
 */
- (NSString * _Nullable)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder * _Nullable)order error:(NSError * _Nullable)error;

@end

#endif /* SpotzCNCProtocol_h */
