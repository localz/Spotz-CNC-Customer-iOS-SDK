//
//  ;
//  LocalzSolomeSDK
//
//  Created by Melvin Artemas on 30/04/2014.
//  Copyright (c) 2014 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpotzSDK/SpotzSDK.h>

#define SpotzCNCErrorDomain @"SpotzCNCSDKDomain"

@interface SpotzCNCError : NSObject
+ (NSError *)errorWithCode:(SpotzErrorType)code userInfo:(NSDictionary *)userInfo;
+ (NSError *)errorWithResponse:(NSURLResponse *)response data:(NSDictionary *)data;
+ (NSError *)invalidResponseFromServer;
+ (NSError *)notFound;
@end
