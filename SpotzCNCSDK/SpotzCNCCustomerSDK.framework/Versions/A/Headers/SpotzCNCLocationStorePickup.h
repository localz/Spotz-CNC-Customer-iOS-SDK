//
//  SpotzCNCLocationStorePickup.h
//  SpotzCNCLocationStorePickup
//
//  Created by Daniel Sykes-Turner on 4/09/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCLocationStorePickup : NSObject
@property (nonatomic, readonly, strong) NSString *pickupId;
@property (nonatomic, readonly, strong) NSString *name;
@property (nonatomic, readonly, strong) NSString *desc;
@property (nonatomic, readonly, strong) NSString *imgUrl;
@property (nonatomic, readonly) BOOL isDefault;
@property (nonatomic, readonly, strong) NSArray *closestSpotIds;

- (SpotzCNCLocationStorePickup *)initWithData:(NSDictionary *)data;

@end
