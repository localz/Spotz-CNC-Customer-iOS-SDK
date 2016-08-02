//
//  AppDelegate.swift
//  SpotzCNCCustomer-Sample-Swift
//
//  Created by Daniel Sykes-Turner on 10/02/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, SpotzCNCCustomerSDKManagerDelegate, SpotzCNCCustomerSDKManagerDataSource {

    var window: UIWindow?


    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        // Override point for customization after application launch.
        
//        SpotzCNCCustomerSDK.initWithAppId("<Enter your spotz app ID here>", spotzAppKey: "<Enter your spotz client key here>", cncAppKey: "<Enter your cnc client key here>", delegate: self, dataSource: self, options: nil)
        
        SpotzCNCCustomerSDK.initWithAppId("pHekL3teP73ydSj8syEGK8K7i0b5Pd48GBfv6000", spotzAppKey: "RbCyyI8uM50QDuBNWSSSxDRRvwMKFWzs1vdkL5vl", cncAppKey: "GtT4rHKuGHkNnyT8Frs7j7wetSsCzzDcUgcs4c1u", delegate: self, dataSource: self, options: ["env":"dev"])
        
        return true
    }

    func applicationWillResignActive(application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }

    
    // MARK: - SpotzCNCCustomerSDKManagerDelegate
    
    func spotzCNCSDKInitSuccessful() {
        
        MBProgressHUD.hideAllHUDsForView(self.window?.rootViewController?.view, animated: true)
        
        SpotzCNCCustomerSDK.shared().startSpotzCNC()
    }
    
    func spotzCNCSDKInitFailed(error: NSError!) {
        
        print("SpotzCNCCustomerSDK init failed with error \(error)")
    }
    
    func spotzCNCSDKCompletedOrderPickup(order: SpotzCNCOrder!) {
        
        print("Order (\(order.orderNumber)) has been picked up!")
    }
    
    func spotzCNCSDKUpdateOrders(orders: [AnyObject]!) {
        
        print("\(orders.count) orders have just changed")
    }
    
    // MARK: - SpotzCNCCustomerSDKManagerDataSource
    
    func spotzCNCSDKNotificationMessageWhenEnteringStore(store: SpotzCNCLocationStore!) -> String! {
        
        return "Welcome to MyStore! Ask any of our friendly staff for help"
    }
    
    func spotzCNCSDKNotificationMessageWhenOrderCheckedInBackground(order: SpotzCNCOrder!) -> String! {
        
        return "Your order (\(order.orderNumber)) has been checked in!"
    }
}

