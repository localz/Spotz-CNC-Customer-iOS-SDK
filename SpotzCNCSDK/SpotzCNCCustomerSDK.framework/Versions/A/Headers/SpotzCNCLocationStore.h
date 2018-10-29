//
//  SpotzCNCLocationStore.h
//  SpotzCNCLocationStore
//
//  Created by Melvin Artemas on 24/09/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SpotzCNCLocationStorePickup.h"

@interface SpotzCNCLocationStore : NSObject
/** @brief Deprecated ID of the store */
@property (nonatomic, readonly, strong) NSString *identifier __deprecated_msg("identifier is no longer used. Please use locationId as the identifier");
/** @brief Internal location ID */
@property (nonatomic, readonly, strong) NSString *locationId;
/** @brief Name of the Location, for example "Melbourne Store" */
@property (nonatomic, readonly, strong) NSString *name;
/** @brief Default Pick up ID of the store, for exampe "CC" */
@property (nonatomic, readonly, strong) NSString *defaultPickupId;
/** @brief Working hours of the store */
@property (nonatomic, readonly, strong) NSArray *workingHours;
/** @brief Latitude of the store */
@property (nonatomic, readonly, strong) NSNumber *latitude;
/** @brief Longitude of the store */
@property (nonatomic, readonly, strong) NSNumber *longitude;
/** @brief Branch ID of the store (also know as store number) */
@property (nonatomic, readonly, strong) NSString *branchId;
/** @brief Internal site ID */
@property (nonatomic, readonly, strong) NSString *siteId;
/** @brief Address of the location */
@property (nonatomic, readonly, strong) NSString *address;
/** @brief Contact phone number of the store */
@property (nonatomic, readonly, strong) NSString *phone;
/** @brief Details about the pickup location */
@property (nonatomic, readonly, strong) NSDictionary<NSString *,SpotzCNCLocationStorePickup *> *locationPickups;
/** @brief Timezone of the location, for example "Australia/Melbourne" */
@property (nonatomic, readonly, strong) NSString *timezone;
/** @brief Whether attendant has logged into attendant device at the store */
@property (nonatomic, readonly) BOOL serviceAvailable;
/** @brief Whether store is open at the moment */
@property (nonatomic, readonly) BOOL storeOpen;

- (instancetype)initWithData:(NSDictionary *)data;
- (NSString *) defaultPickupLocationName;
@end
