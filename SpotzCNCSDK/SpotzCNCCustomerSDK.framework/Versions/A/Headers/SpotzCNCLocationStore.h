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
@property (nonatomic, readonly, strong) NSString *identifier;
@property (nonatomic, readonly, strong) NSString *name;
@property (nonatomic, readonly, strong) NSString *defaultPickupId;
@property (nonatomic, readonly, strong) NSArray *workingHours;
@property (nonatomic, readonly, strong) NSNumber *latitude;
@property (nonatomic, readonly, strong) NSNumber *longitude;
@property (nonatomic, readonly, strong) NSString *branchId;
@property (nonatomic, readonly, strong) NSString *locationId;
@property (nonatomic, readonly, strong) NSString *siteId;
@property (nonatomic, readonly, strong) NSString *address;
@property (nonatomic, readonly, strong) NSString *phone;
@property (nonatomic, readonly, strong) NSDictionary<NSString *,SpotzCNCLocationStorePickup *> *locationPickups;
@property (nonatomic, readonly, strong) NSString *timezone;
@property (nonatomic, readonly) BOOL serviceAvailable;
@property (nonatomic, readonly) BOOL storeOpen;

- (instancetype)initWithData:(NSDictionary *)data;
- (NSString *) defaultPickupLocationName;
@end
