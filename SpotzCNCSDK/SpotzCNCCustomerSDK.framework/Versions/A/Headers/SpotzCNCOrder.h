//
//  SpotzCNCOrder.h
//  SpotzCNCOrder
//
//  Created by Daniel Sykes-Turner on 4/09/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SpotzCNCLocationStorePickup.h"
#import "SpotzCNCLocationStore.h"
#import "SpotzCNCAttendant.h"

typedef enum {
    /** @brief Orders in this status not visible to customer SDK */
    SpotzCNCOrderStatusCompleted = 1,
    /** @brief Order status when order is not yet ready to be collected by customer */
    SpotzCNCOrderStatusNotReady,
    /** @brief Order status when order is READY to be collected by customer */
    SpotzCNCOrderStatusReady,
    /** @brief Order was checked in by customer, but not yet acknowledged by attendant */
    SpotzCNCOrderStatusNotified,
    /** @brief Order was checked in by customer and was acknowledged by attendant */
    SpotzCNCOrderStatusAssigned,
    /** @brief Order status when order is not yet ready to be collected by customer, but picking of order is completed. */
    SpotzCNCOrderStatusPendingPicked,
    /** @brief Order status when order is not yet ready to be collected by customer, but packing of order is completed. */
    SpotzCNCOrderStatusPendingPacked,
    /** @brief Orders in this status not visible to customer SDK. */
    SpotzCNCOrderStatusHandover,
    /** @brief Orders in this status not visible to customer SDK. */
    SpotzCNCOrderStatusFailedComplete,
    /** @brief Orders in this status not visible to customer SDK. */
    SpotzCNCOrderStatusDeleted
} SpotzCNCOrderStatus;

@interface SpotzCNCOrder : NSObject<NSCoding>
/** @brief orderStatus */
@property (nonatomic, readonly) SpotzCNCOrderStatus orderStatus;
/** @brief Name of the customer */
@property (nonatomic, readonly, strong) NSString * _Nullable deliveryName;
/** @brief Total amount of the order */
@property (nonatomic, readonly, strong) NSNumber * _Nullable orderAmount;
/** @brief Date of the order */
@property (nonatomic, readonly, strong) NSDate * _Nullable orderDate;
/** @brief Order number, unique per project */
@property (nonatomic, readonly, strong) NSString * _Nonnull orderNumber;
/** @brief Start time of pickup window */
@property (nonatomic, readonly, strong) NSDate * _Nullable pickupStart;
/** @brief End time fo pickup window */
@property (nonatomic, readonly, strong) NSDate * _Nullable pickupEnd;
/** @brief Pickup ID, for example "CC", "DT", "XP" */
@property (nonatomic, readonly, strong) NSString * _Nullable selectedPickupId;
/** @brief Number of items in the order */
@property (nonatomic, readonly, strong) NSNumber * _Nullable totalItems;
/** @brief Attributes of the order, key-value pairs */
@property (nonatomic, readonly, strong) NSDictionary * _Nullable specific;
/** @brief Whether customer should be allowed to check-in if SpotzCNCOrderStatusNotReady */
@property (nonatomic, readonly) BOOL isAllowingCheckinPendingOrders;
/** @brief Whether order should be automatically checked in (without customer confirmation) when customer enters site of the location. */
@property (nonatomic, readonly) BOOL isAllowingAutoCheckinOnSiteEntry;
/** @brief Details of the store to which the order belongs */
@property (nonatomic, readonly, strong) SpotzCNCLocationStore * _Nullable store;
/** @brief Details of attendant who acknowledged order */
@property (nonatomic, readonly, strong) SpotzCNCAttendant * _Nullable attendant;
/** @brief Proximity triggers that can be set on the order, are used to let attendant know the exact position of the customer, for example "Bay 1" */
@property (nonatomic, readonly, strong) NSArray * _Nullable proximityTriggers;

/**
 * Initialise Order data
 */
- (SpotzCNCOrder * _Nonnull)initWithData:(NSDictionary * _Nonnull)data;

- (SpotzCNCOrder * _Nonnull)initWithOrderNumber:(NSString * _Nonnull)number date:(NSDate * _Nullable)date deliveryName:(NSString * _Nullable)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber * _Nullable)amount pickupStartDate:(NSDate * _Nullable)start pickupEndDate:(NSDate * _Nullable)end selectedPickupId:(NSString * _Nullable)pickupId totalItems:(NSNumber * _Nullable)totalItems attributes:(NSDictionary * _Nullable)attributes allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin;

/**
 * Whether an order is within the pickup window. NOTE: This is not store opening hours check!
 * @return true if order is within pick up window
 */
- (BOOL) isWithinPickupWindow;

/**
 * This checks whether the store is open
 * @return true if store is open
 */
- (BOOL) isTimeToNotify;

/**
 * Converts the order status to a string
 * @return string representation of the order status
 */
- (NSString * _Nonnull)orderStatusString;

/**
 * Class function converts the order status to a string
 * @return string representation of the order status
 */
+ (NSString * _Nonnull)orderStatusString:(SpotzCNCOrderStatus)orderStatus;

@end
