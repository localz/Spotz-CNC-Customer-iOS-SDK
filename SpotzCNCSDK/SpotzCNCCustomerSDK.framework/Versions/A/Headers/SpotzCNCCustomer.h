//
//  SpotzCNCCustomer.h
//  SpotzCNCCustomer
//
//  Created by Daniel Sykes-Turner on 21/08/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCNCCustomer : NSObject<NSCoding>
/** @brief Identifer for the customer */
@property (nonatomic, readonly, strong) NSString *customerId;
/** @brief Title of the customer */
@property (nonatomic, readonly, strong) NSString *title;
/** @brief Firstname of the customer */
@property (nonatomic, readonly, strong) NSString *firstName;
/** @brief Lastname of the customer */
@property (nonatomic, readonly, strong) NSString *lastName;
/** @brief Username of the customer created when registered first time */
@property (nonatomic, readonly, strong) NSString *username;
/** @brief If customer registration is verified */
@property (nonatomic, readwrite) BOOL isVerified;

/**
 * Method to initialise Customer data
 * @param data Data required to initialise customer
 * @param username Username of the customer used while registering
 * @return SpotzCNCCustomer object
 */
- (SpotzCNCCustomer *)initWithData:(NSDictionary *)data username:(NSString *)username;

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
