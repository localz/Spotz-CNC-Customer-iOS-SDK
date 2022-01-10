//
//  LocalzDriverGeoJson.h
//  LocalzDriverSDK
//
//  Created by Rashmi Sivaramareddy on 11/7/18.
//  Copyright © 2018 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface SpotzCNCGeoJson : NSObject<NSCoding>

@property (nonatomic, readonly, strong) NSArray *coordinates;
@property (nonatomic, readonly, strong) NSString *type __deprecated_msg("'type' is no longer in use.");

- (instancetype) initWithData:(NSDictionary *)data;

- (NSDictionary *) toJSON;
@end

