//
//  SpotzCNCCustomerConstants.h
//  SpotzCNCCustomerConstants
//
//  Created by Melvin Artemas on 29/09/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
#import <Foundation/Foundation.h>

// Notification of network status
extern NSString * const SPOTZ_CNC_NETWORK_NOTIFICATION;
// Error code for CNC
extern int const EProjectDisabled;

typedef enum {
    /** @brief Location services not determined */
    SpotzCNCLocationServicesNotDetermined = 0,
    /** @brief Location services are on always or when in use */
    SpotzCNCLocationServicesOn,
    /** @brief Location services not enabled */
    SpotzCNCLocationServicesOff
} SpotzCNCLocationServices;

typedef enum {
    /** @brief Activity type when device enters a site */
    SpotzCNCActivityTypeEnter,
    /** @brief Activity type when device exits a site */
    SpotzCNCActivityTypeExit
} SpotzCNCActivityType;
