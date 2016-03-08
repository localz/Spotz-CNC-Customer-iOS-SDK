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
    SpotzCNCOrderStatusNotified
} SpotzCNCOrderStatus;

@interface SpotzCNCOrder : NSObject<NSCoding>
@property (nonatomic, readonly) SpotzCNCOrderStatus orderStatus;
@property (nonatomic, readonly, strong) NSString *deliveryName;
@property (nonatomic, readonly, strong) NSString *orderAmount;
@property (nonatomic, readonly, strong) NSDate *orderDate;
@property (nonatomic, readonly, strong) NSString *orderNumber;
@property (nonatomic, readonly, strong) NSDate *pickupStart;
@property (nonatomic, readonly, strong) NSDate *pickupEnd;
@property (nonatomic, readonly, strong) NSString *selectedPickupId;
@property (nonatomic, readonly, strong) NSNumber *totalItems;
@property (nonatomic, readonly, strong) NSDictionary *specific;
@property (nonatomic, readonly, strong) SpotzCNCLocationStore *store;
@property (nonatomic, readonly, strong) SpotzCNCAttendant *attendant;

- (SpotzCNCOrder *)initWithData:(NSDictionary *)data;
- (SpotzCNCOrder *)initWithOrderNumber:(NSString *)orderNumber orderDate:(NSDate *)orderDate deliveryName:(NSString *)deliveryName orderStatus:(SpotzCNCOrderStatus)status orderAmount:(NSString *)amount pickupStart:(NSDate *)pickupStart pickupDate:(NSDate *)pickupEnd selectedPickupId:(NSString *)selectedPickupId totalItems:(NSNumber *)totalItems attributes:(NSDictionary *)specific;
- (BOOL) isWithinPickupWindow;
- (BOOL) isTimeToNotify;
@end
