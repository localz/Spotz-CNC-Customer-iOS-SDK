//
//  SpotzCNCNotification.h
//  SpotzCNCCustomerSDK
//
//  Created by Melvin Artemas on 29/10/20.
//  Copyright © 2020 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCNotification : NSObject
@property (nonatomic, strong) NSString * _Nonnull requestIdentifier;
@property (nonatomic, strong) NSString * _Nullable title;
@property (nonatomic, strong) NSString * _Nonnull body;
@property (nonatomic, strong) NSDictionary * _Nullable userInfo;
@property (nonatomic, strong) NSString * _Nullable actionIdentifier;
@property (nonatomic, strong) NSString * _Nullable categoryIdentifier;

- (SpotzCNCNotification * _Nonnull)initWithRequestId:(NSString * _Nonnull)requestIdentifier;
- (SpotzCNCNotification * _Nonnull)initWithRequestId:(NSString * _Nonnull)requestIdentifier title:(NSString * _Nullable)title body:(NSString * _Nonnull)body;

@end
