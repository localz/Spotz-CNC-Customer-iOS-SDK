//
//  AppDelegate.m
//  SpotzCNCCustomer-Sample-ObjC
//
//  Created by Daniel Sykes-Turner on 8/02/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import <SpotzCNCCustomerSDK/SpotzCNCCustomerSDK.h>

@interface AppDelegate () <SpotzCNCCustomerSDKManagerDelegate, SpotzCNCCustomerSDKManagerDataSource>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    [MBProgressHUD showHUDAddedTo:self.window.rootViewController.view animated:true];
    
//    [SpotzCNCCustomerSDK initWithAppId:@"<Enter your spotz app ID here>" spotzAppKey:@"<Enter your spotz client key here>" cncAppKey:@"<Enter your cnc client key here>" delegate:self dataSource:self options:nil];
    
    [SpotzCNCCustomerSDK initWithAppId:@"pHekL3teP73ydSj8syEGK8K7i0b5Pd48GBfv6000" spotzAppKey:@"RbCyyI8uM50QDuBNWSSSxDRRvwMKFWzs1vdkL5vl" cncAppKey:@"GtT4rHKuGHkNnyT8Frs7j7wetSsCzzDcUgcs4c1u" delegate:self dataSource:self options:@{@"env":@"dev"}];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


#pragma mark - SpotzCNCCustomerSDKDelegate

- (void)spotzCNCSDKInitSuccessful {
    
    [MBProgressHUD hideAllHUDsForView:self.window.rootViewController.view animated:true];
    
    [[SpotzCNCCustomerSDK shared] startSpotzCNC];
}

- (void)spotzCNCSDKInitFailed:(NSError *)error {
    
    NSLog(@"SpotzCNCCustomerSDK init failed with error %@", error);
}


- (void)spotzCNCSDKConfirmedCustomerRegistration {
    
    NSLog(@"Customer verified!");
    
    // now the customer can use click & collect!
}

- (void)spotzCNCSDKCompletedOrderPickup:(SpotzCNCOrder *)order {
    
    NSLog(@"Order (%@) has been picked up!", order.orderNumber);
    
    // update the current order/order list if necessary
}

- (void)spotzCNCSDKUpdateOrders:(NSArray *)orders {
    
    NSLog(@"%i orders have just changed", (int)orders.count);
    
    // update the current order/order list if necessary
}


#pragma mark - SpotzCNCCustomerSDKDataSource

- (NSString *)spotzCNCSDKNotificationMessageWhenEnteringStore:(SpotzCNCLocationStore *)store {

    return @"Welcome to MyStore! Ask any of our friendly staff for help";
}

- (NSString *)spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground:(SpotzCNCOrder *)order {
    
    return [NSString stringWithFormat:@"Your order (%@) has been checked in!", order.orderNumber];
}

@end
