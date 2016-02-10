//
//  SpotzCNCCustomer.h
//  SpotzCNCCustomer
//
//  Created by Daniel Sykes-Turner on 21/08/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCCustomer : NSObject
@property (nonatomic, readonly, strong) NSString *customerId;
@property (nonatomic, readonly, strong) NSString *title;
@property (nonatomic, readonly, strong) NSString *firstName;
@property (nonatomic, readonly, strong) NSString *lastName;
@property (nonatomic, readonly, strong) NSString *username;
@property (nonatomic, readwrite) BOOL isVerified;

- (SpotzCNCCustomer *)initWithData:(NSDictionary *)data username:(NSString *)username;

- (void)encodeWithCoder:(NSCoder *)encoder;
- (id)initWithCoder:(NSCoder *)decoder;
@end
