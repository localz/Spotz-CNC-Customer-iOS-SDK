//
//  SpotzCNCLocationStorePickup.h
//  SpotzCNCLocationStorePickup
//
//  Created by Daniel Sykes-Turner on 4/09/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCLocationStorePickup : NSObject
/** @brief Pick up ID of the store */
@property (nonatomic, readonly, strong) NSString *pickupId;
/** @brief Name of the pickup location */
@property (nonatomic, readonly, strong) NSString *name;
/** @brief Description of the pickup location */
@property (nonatomic, readonly, strong) NSString *desc;
/** @brief URL of an image that can explain better to customers how to find the pickup location (in case store address is not sufficient) */
@property (nonatomic, readonly, strong) NSString *imgUrl;
@property (nonatomic, readonly) BOOL isDefault;
@property (nonatomic, readonly, strong) NSArray *closestSpotIds;

- (SpotzCNCLocationStorePickup *)initWithData:(NSDictionary *)data;

@end
