//
//  SpotzCNCCustomer.h
//  SpotzCNCCustomer
//
//  Created by Daniel Sykes-Turner on 21/08/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCAttendant : NSObject<NSCoding>
@property (nonatomic, readonly, strong) NSString *firstName;
@property (nonatomic, readonly, strong) NSString *lastName;
@property (nonatomic, readonly, strong) NSString *avatarUrl;

- (SpotzCNCAttendant *)initWithData:(NSDictionary *)data;

- (void)encodeWithCoder:(NSCoder *)encoder;
- (id)initWithCoder:(NSCoder *)decoder;
@end
