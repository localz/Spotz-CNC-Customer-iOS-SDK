//
//  ViewController.m
//  SpotzCNCCustomer-Sample-ObjC
//
//  Created by Daniel Sykes-Turner on 8/02/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

#import "ViewController.h"
#import "MBProgressHUD.h"
#import <SpotzCNCCustomerSDK/SpotzCNCCustomerSDK.h>

@interface ViewController () <UITableViewDataSource>
@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (nonatomic, weak) IBOutlet UITextField *txtEmailAddress;
@property (nonatomic, weak) IBOutlet UILabel *lblLoggedInUser;
@property (nonatomic, weak) IBOutlet UIButton *btnCheckInOrder;
@property (nonatomic, weak) IBOutlet UIButton *btnGetOrders;

@property (nonatomic, strong) NSMutableArray *orders;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
        
    [self refreshUserDetails];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)refreshUserDetails {
    
    // Check if the customer is logged in and has verified their email
    if ([[SpotzCNCCustomerSDK shared] currentCustomer]) {
        if ([[SpotzCNCCustomerSDK shared] currentCustomer].isVerified) {
            self.lblLoggedInUser.text = [[SpotzCNCCustomerSDK shared] currentCustomer].username;
        } else {
            // The customer has an unverified email. They must first click a verify link emailed to them
            self.lblLoggedInUser.text = [NSString stringWithFormat:@"%@ (unverified)", [[SpotzCNCCustomerSDK shared] currentCustomer].username];
        }
        
        self.btnCheckInOrder.hidden = false;
        self.btnGetOrders.hidden = false;
    } else {
        self.lblLoggedInUser.text = @"";
        
        self.btnCheckInOrder.hidden = true;
        self.btnGetOrders.hidden = true;
    }
    
    [self.tableView reloadData];
}

#pragma mark - SpotzCNCCustomerSDK calls

- (IBAction)btnRegisterTapped:(id)sender {
    
    if (self.txtEmailAddress.text.length == 0)
        return;
    
    [self.txtEmailAddress resignFirstResponder];
    NSString *email = self.txtEmailAddress.text;
    
    [MBProgressHUD showHUDAddedTo:self.view animated:true];
    [[SpotzCNCCustomerSDK shared] registerCustomerWithEmail:email otherParameters:nil completion:^(NSError *error) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:true];
        
        if (!error) {
            [self refreshUserDetails];
        } else {
            NSLog(@"Failed to register email %@ with error %@", email, error);
        }
    }];
}

- (IBAction)btnGetOrdersTapped:(id)sender {
    
    [self.txtEmailAddress resignFirstResponder];
    
    [MBProgressHUD showHUDAddedTo:self.view animated:true];
    [[SpotzCNCCustomerSDK shared] getCustomerNonCompletedOrdersSpotRecheck:false completion:^(NSArray *orders, NSError *error) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:true];
        
        if (!error) {
            self.orders = [NSMutableArray arrayWithArray:orders];
            [self.tableView reloadData];
        } else {
            NSLog(@"Failed to get orders with error %@", error);
        }
    }];
}

- (IBAction)btnCheckinOrderTapped:(id)sender {
    
    if (!self.orders || self.orders.count == 0)
        return;
    
    // Check-in the newest order we have. If there is more than one order ready to be checked in for this customer, then any other orders for them will be checked in too.
    // This works in real life as all orders should be brought out to the customer if they are collecting at the counter. If they still don't want to collect all orders, these can be reset in the spotz cnc console.
    
    [self.txtEmailAddress resignFirstResponder];
    SpotzCNCOrder *firstOrder = self.orders.firstObject;
    
    [MBProgressHUD showHUDAddedTo:self.view animated:true];
    [[SpotzCNCCustomerSDK shared] checkinOrder:firstOrder force:true completion:^(NSNumber *numOrdersCheckedIn, NSError *error) {
        [MBProgressHUD hideAllHUDsForView:self.view animated:true];
        
        if (!error) {
            if (numOrdersCheckedIn.intValue > 1) {
                NSLog(@"Order (%@) and %i others checked in!", firstOrder.orderNumber, numOrdersCheckedIn.intValue-1);
            } else {
                NSLog(@"Order (%@) checked in!", firstOrder.orderNumber);
            }
            
            // Now refresh the orders array
            [self btnGetOrdersTapped:nil];
            
        } else {
            NSLog(@"Failed to check in order %@ with %@", firstOrder.orderNumber, error);
        }
    }];
}

#pragma mark - UITableViewDataSource

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    
    SpotzCNCOrder *order = self.orders[indexPath.row];
    NSString *status;
    switch (order.orderStatus) {
        case SpotzCNCOrderStatusCompleted:
            status = @"Completed";
            break;
        case SpotzCNCOrderStatusNotified:
            status = @"Attendant Notified";
            break;
        case SpotzCNCOrderStatusNotReady:
            status = @"Not Ready";
            break;
        case SpotzCNCOrderStatusReady:
            status = @"Ready";
            break;
        default:
            status = @"Unknown";
            break;
    }
    cell.textLabel.text = [NSString stringWithFormat:@"Order %@ - %@", order.orderNumber, status];
    
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return self.orders.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    
    return 1;
}

@end
