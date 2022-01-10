//
//  SpotzCNCError.h
//  SpotzCNCError
//
//  Created by Melvin Artemas on 30/04/2014.
//  Copyright (c) 2014 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SpotzCNCErrorDomain @"SpotzCNCSDKDomain"

@interface SpotzCNCError : NSObject
/**
 * Handler for SpotzCNCSDKDomain errors with error code
 * @param code The error code for error
 * @param userInfo The userInfo dictionary for the error. userInfo may be nil
 * @return NSError object for SpotzCNCSDKDomain
 */
+ (NSError *)errorWithCode:(int)code userInfo:(NSDictionary *)userInfo;

/**
 * Handler for SpotzCNCSDKDomain errors with response
 * @param response The metadata associated with the response to a URL load request
 * @param data The userInfo dictionary for the error. userInfo may be nil
 * @return NSError object for SpotzCNCSDKDomain
 */
+ (NSError *)errorWithResponse:(NSURLResponse *)response data:(NSDictionary *)data;

/**
 * Handler for SpotzCNCDSDKDomain error invalid response from server
 * @return NSError object for SpotzCNCSDKDomain
 */
+ (NSError *)invalidResponseFromServer;

/**
 * Handler for SpotzCNCSDKDomain error not found
 * @return NSError object for SpotzCNCSDKDomain
 */
+ (NSError *)notFound;
@end
