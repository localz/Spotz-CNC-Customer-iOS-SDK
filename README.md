# Spotz-CNC-Customer-iOS-SDK (Click &amp; Collect)


## Adding the Spotz CNC Customer SDK framework to your project

Just add the following lines to your Podfile:
```
pod 'SpotzCNCCustomerSDK', :git => 'https://github.com/localz/Spotz-CNC-Customer-iOS-SDK.git',:branch=>'1.2_beta'
pod 'SpotzSDK', :git=>'https://github.com/localz/Spotz3-iOS-SDK',:branch=>'3.1.0.7_beta'
pod 'SpotzPushSDK', :git => 'https://github.com/localz/Spotz-Push-iOS-SDK'
```

## How to use the SDK


**Currently only devices that support Bluetooth Low Energy (iPhone 4s or above, running iOS 8 or later) are able to make use of the SpotzCNCCustomerSDK.**

There are only 3 actions to implement before using the click and collect SDK - **configure, initialize, and start services!**

*Refer to the sample app code for a working implementation of the SDK.*


**1. Set authorization message**

For iOS 8 or later, please add the following key to Info.plist with a message that will be presented to the user when they first start the app.
```
NSLocationAlwaysUsageDescription
```

**2. Initialize the Spotz CNC Customer SDK**

Import the SpotzCNCCustomerSDK header into the AppDelegate, then in the didFinishLaunchingWithOptions method add the following:

Swift
```
SpotzCNCCustomerSDK.initWithAppId("<Enter your spotz app ID here>", spotzAppKey: "<Enter your spotz client key here>", cncAppKey: "<Enter your cnc client key here>", delegate: self, dataSource: self, options: nil)
```

Objective-C
```
[SpotzCNCCustomerSDK initWithAppId:@"<Enter your spotz app ID here>" spotzAppKey:@"<Enter your spotz client key here>" cncAppKey:@"<Enter your cnc client key here>" delegate:self dataSource:self options:nil];
```

If initialization is successful, it will call the spotzCNCSDKInitSuccessful delegate method. Otherwise it will call the spotzCNCSDKInitFailed: delegate method.

**3. Start services**

Swift
```
func spotzCNCSDKInitSuccessful() {
    
    SpotzCNCCustomerSDK.shared().startSpotzCNC()
}
    
func spotzCNCSDKInitFailed(error: NSError!) {
    
    print("SpotzCNCCustomerSDK init failed with error \(error)")
}
```

Objective-C
```
- (void)spotzCNCSDKInitSuccessful {
    
    [[SpotzCNCCustomerSDK shared] startSpotzCNC];
}

- (void)spotzCNCSDKInitFailed:(NSError *)error {
    
    NSLog(@"SpotzCNCCustomerSDK init failed with error %@", error);
}
```

**4. GO! (a few basic methods)**

**4.1 Register a new customer**

Swift
```
let email = "customeremail@localz.com"
        
SpotzCNCCustomerSDK.shared().registerCustomerWithEmail(email, otherParameters: nil) { (error:NSError!) -> Void in

    if (error == nil) {
        print("Registered! Click email verification link to start using CNC")
    } else {
        print("Failed to register email \(email) with error \(error)")
    }
}
```

Objective-C
```
NSString *email = @"customeremail@localz.com";
    
[[SpotzCNCCustomerSDK shared] registerCustomerWithEmail:email otherParameters:nil completion:^(NSError *error) {

    if (!error) {
        NSLog(@"Registered! Click email verification link to start using CNC");
    } else {
        NSLog(@"Failed to register email %@ with error %@", email, error);
    }
}];
```

**4.2 Get all non-completed orders for a customer**
Swift
```
SpotzCNCCustomerSDK.shared().getCustomerNonCompletedOrdersSpotRecheck(false) { (orders:[AnyObject]!, error:NSError!) -> Void in

    if (error == nil) {
        // Do something with the customer's orders
    } else {
        print("Failed to get orders with error \(error)")
    }
}
```

Objective-C
```
[[SpotzCNCCustomerSDK shared] getCustomerNonCompletedOrdersSpotRecheck:false completion:^(NSArray *orders, NSError *error) {

    if (!error) {
        // Do something with the customer's orders
    } else {
        NSLog(@"Failed to get orders with error %@", error);
    }
}];
```

**4.3 Check-in a customer order**
Swift
```
let order:SpotzCNCOrder! = /*get the selected order from a list*/ as! SpotzCNCOrder
        
SpotzCNCCustomerSDK.shared().checkinOrder(order, force: true) { (numOrdersCheckedIn:NSNumber!, error:NSError!) -> Void in

    if (error == nil) {
        if (numOrdersCheckedIn.intValue > 1) {
            print("Order (\(order.orderNumber)) and \(numOrdersCheckedIn) others checked in!")
        } else {
            print("Order (\(order.orderNumber)) checked in!")
        }
    } else {
        print("Failed to check in order \(order.orderNumber) with error \(error)")
    }
}
```

Objective-C
```
SpotzCNCOrder *order = /*get the selected order from a list*/;
    
[[SpotzCNCCustomerSDK shared] checkinOrder:order force:true completion:^(NSNumber *numOrdersCheckedIn, NSError *error) {

    if (!error) {
        if (numOrdersCheckedIn.intValue > 1) {
            NSLog(@"Order (%@) and %i others checked in!", order.orderNumber, numOrdersCheckedIn.intValue-1);
        } else {
            NSLog(@"Order (%@) checked in!", order.orderNumber);
        }
    } else {
        NSLog(@"Failed to check in order %@ with %@", order.orderNumber, error);
    }
}];
```
**4.4 Create an order**
Swift
```
let order = SpotzCNCOrder(data: ["orderNumber":"000000000", "name":"Order ONE", "selectedPickupId":"001"])
let customerId = SpotzCNCCustomerSDK.shared().currentCustomer().customerId
let branchId = "100"

SpotzCNCCustomerSDK.shared().createOrder(order, branchId: branchId, customerId: customerId) { (error) -> Void in
    if let error = error {
        print("Failed to create order with error \(error)")
        return
    }
    
    print("Order created")
}
```

Objective-C
```
SpotzCNCOrder *order = [SpotzCNCOrder initWithData:@{@"orderNumber":@"000000000", @"name":@"Order ONE", @"selectedPickupId":@"001"}];
NSString *customerId = [[SpotzCNCCustomerSDK shared] currentCustomer].customerId;
NSString *branchId = @"100";

[[SpotzCNCCustomerSDK shared] createOrder:order branchId:branchId customerId:customerId completion:^(NSError *error) {
    if (!error) {
        NSLog(@"Order created");
    } else {
        NSLog(@"Failed to create order with error %@", error);
    }
}];
```

## Contribution

For bugs, feature requests, or other questions, [file an issue](https://github.com/localz/Spotz-CNC-Customer-iOS-SDK/issues/new).

## License

Copyright 2016 Localz Pty Ltd
