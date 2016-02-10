//
//  ViewController.swift
//  SpotzCNCCustomer-Sample-Swift
//
//  Created by Daniel Sykes-Turner on 10/02/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource {
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var txtEmailAddress: UITextField!
    @IBOutlet weak var lblLoggedInUser: UILabel!
    @IBOutlet weak var btnCheckInOrder: UIButton!
    @IBOutlet weak var btnGetOrders: UIButton!
    
    var orders: NSMutableArray! = NSMutableArray()

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.refreshUserDetail()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func refreshUserDetail() {
        
        // Check if the customer is logged in and has verified their email
        if let customer = SpotzCNCCustomerSDK.shared().currentCustomer() {
            if customer.isVerified {
                self.lblLoggedInUser.text = customer.username
            } else {
                // The customer has an unverified email. They must first click a verify link emailed to them
                self.lblLoggedInUser.text = "\(customer.username) (unverified)"
            }
            
            self.btnCheckInOrder.hidden = false
            self.btnGetOrders.hidden = false
        } else {
            self.lblLoggedInUser.text = ""
            
            self.btnCheckInOrder.hidden = true
            self.btnGetOrders.hidden = true
        }
        
        self.tableView.reloadData()
    }
    
    // MARK: - SpotzCNCCustomerSDK calls
    
    @IBAction func btnRegisterTapped(sender: AnyObject?) {
        
        if self.txtEmailAddress.text == "" {return}
        
        let email = self.txtEmailAddress.text
        
        MBProgressHUD.showHUDAddedTo(self.view, animated: true)
        SpotzCNCCustomerSDK.shared().registerCustomerWithEmail(email, otherParameters: nil) { (error:NSError!) -> Void in
            MBProgressHUD.hideAllHUDsForView(self.view, animated: true)
            
            if (error == nil) {
                self.refreshUserDetail()
            } else {
                print("Failed to register email \(email) with error \(error)")
            }
        }
    }
    
    @IBAction func btnGetOrdersTapped(sender: AnyObject?) {
        
        self.txtEmailAddress.resignFirstResponder()
        
        MBProgressHUD.showHUDAddedTo(self.view, animated: true)
        SpotzCNCCustomerSDK.shared().getCustomerNonCompletedOrdersSpotRecheck(false) { (orders:[AnyObject]!, error:NSError!) -> Void in
            MBProgressHUD.hideAllHUDsForView(self.view, animated: true)
            
            if (error == nil) {
                self.orders = NSMutableArray(array: orders)
                self.tableView.reloadData()
            } else {
                print("Failed to get orders with error \(error)")
            }
        }
    }
    
    @IBAction func btnCheckinOrderTapped(sender: AnyObject?) {
        
        if (self.orders.count == 0) {return}
        
        // Check-in the newest order we have. If there is more than one order ready to be checked in for this customer, then any other orders for them will be checked in too.
        // This works in real life as all orders should be brought out to the customer if they are collecting at the counter. If they still don't want to collect all orders, these can be reset in the spotz cnc console.
        
        self.txtEmailAddress.resignFirstResponder()
        let firstOrder:SpotzCNCOrder! = self.orders.firstObject as! SpotzCNCOrder
        
        MBProgressHUD.showHUDAddedTo(self.view, animated: true)
        SpotzCNCCustomerSDK.shared().checkinOrder(firstOrder, force: true) { (numOrdersCheckedIn:NSNumber!, error:NSError!) -> Void in
            MBProgressHUD.hideAllHUDsForView(self.view, animated: true)
            
            if (error == nil) {
                if (numOrdersCheckedIn.intValue > 1) {
                    print("Order (\(firstOrder.orderNumber)) and \(numOrdersCheckedIn) others checked in!")
                } else {
                    print("Order (\(firstOrder.orderNumber)) checked in!")
                }
                
                // Now refresh the orders array
                self.btnGetOrdersTapped(nil)
            } else {
                print("Failed to check in order \(firstOrder.orderNumber) with error \(error)")
            }
        }
    }
    
    // MARK: - UITableViewDataSource
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCellWithIdentifier("cell")
        if (cell == nil) {
            cell = UITableViewCell(style: UITableViewCellStyle.Default, reuseIdentifier: "cell")
        }
        
        let order:SpotzCNCOrder! = self.orders[indexPath.row] as! SpotzCNCOrder
        var status:NSString! = ""
        switch order.orderStatus {
        case SpotzCNCOrderStatusCompleted:
            status = "Completed";
            break
        case SpotzCNCOrderStatusNotified:
            status = "Attendant Notified"
            break
        case SpotzCNCOrderStatusNotReady:
            status = "Not Ready"
            break
        case SpotzCNCOrderStatusReady:
            status = "Ready"
            break
        default:
            status = "Unknown"
            break
        }
        cell?.textLabel!.text = "Order \(order.orderNumber) - \(status)"
        
        return cell!
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        return self.orders.count
    }
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        
        return 1
    }
}

