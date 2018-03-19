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
    SpotzCNCOrderStatusCompleted = 1,
    SpotzCNCOrderStatusNotReady,
    SpotzCNCOrderStatusReady,
    SpotzCNCOrderStatusNotified,
    SpotzCNCOrderStatusAssigned
} SpotzCNCOrderStatus;

@interface SpotzCNCOrder : NSObject<NSCoding>
@property (nonatomic, readonly) SpotzCNCOrderStatus orderStatus;
@property (nonatomic, readonly, strong) NSString *deliveryName;
@property (nonatomic, readonly, strong) NSNumber *orderAmount;
@property (nonatomic, readonly, strong) NSDate *orderDate;
@property (nonatomic, readonly, strong) NSString *orderNumber;
@property (nonatomic, readonly, strong) NSDate *pickupStart;
@property (nonatomic, readonly, strong) NSDate *pickupEnd;
@property (nonatomic, readonly, strong) NSString *selectedPickupId;
@property (nonatomic, readonly, strong) NSNumber *totalItems;
@property (nonatomic, readonly, strong) NSDictionary *specific;
@property (nonatomic, readonly) BOOL isAllowingCheckinPendingOrders;
@property (nonatomic, readonly) BOOL isAllowingAutoCheckinOnSiteEntry;
@property (nonatomic, readonly, strong) SpotzCNCLocationStore *store;
@property (nonatomic, readonly, strong) SpotzCNCAttendant *attendant;

- (SpotzCNCOrder *)initWithData:(NSDictionary *)data;
- (SpotzCNCOrder *)initWithOrderNumber:(NSString *)orderNumber orderDate:(NSDate *)orderDate deliveryName:(NSString *)deliveryName orderStatus:(SpotzCNCOrderStatus)status orderAmount:(NSString *)amount pickupStart:(NSDate *)pickupStart pickupDate:(NSDate *)pickupEnd selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)specific allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin __deprecated_msg("orderAmount is no longer supporting NSString class. Use alternative initWithOrderNumber: instead.");
- (SpotzCNCOrder *)initWithOrderNumber:(NSString *)number date:(NSDate *)date deliveryName:(NSString *)deliveryName status:(SpotzCNCOrderStatus)status amount:(NSNumber *)amount pickupStartDate:(NSDate *)start pickupEndDate:(NSDate *)end selectedPickupId:(NSString *)pickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)attributes allowCheckinPending:(BOOL)allowCheckinPending allowAutoCheckin:(BOOL)allowAutoCheckin;
- (BOOL) isWithinPickupWindow;
- (BOOL) isTimeToNotify;
@end
