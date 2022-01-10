//
//  SpotzCNCAttendant.h
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 21/08/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCAttendant : NSObject<NSCoding>
/** @brief First name of the attendant */
@property (nonatomic, readonly, strong) NSString *firstName;
/** @brief Last name of the attendant */
@property (nonatomic, readonly, strong) NSString *lastName;
/** @brief Avatar URL of the attendant */
@property (nonatomic, readonly, strong) NSString *avatarUrl;

/**
 * Method to initialise Attendant data
 * @param data Data required to initialise attendant
 * @return SpotzCNCAttendant object
 */
- (SpotzCNCAttendant *)initWithData:(NSDictionary *)data;

/**
 * Encodes the given receiver with archiver
 * @param encoder An archiver object
 */
- (void)encodeWithCoder:(NSCoder *)encoder;

/**
 * Returns an object initialized from data in a given unarchiver.
 * @param decoder An unarchiver object
 */
- (id)initWithCoder:(NSCoder *)decoder;
@end
