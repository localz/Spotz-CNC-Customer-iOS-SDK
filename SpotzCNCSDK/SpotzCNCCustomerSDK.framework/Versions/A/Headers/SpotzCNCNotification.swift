//
//  SpotzCNCNotification.swift
//  SpotzCNCCustomerSDK
//
//  Created by Daniel Sykes-Turner on 16/10/18.
//  Copyright © 2018 Localz Pty Ltd. All rights reserved.
//

import UIKit

@objc public class SpotzCNCNotification: NSObject {

    @objc public var requestIdentifier: String
    
    @objc public var title: String?
    @objc public var body: String?
    @objc public var userInfo: [String:Any]?
    
    @objc public var actionIdentifier: String?
    @objc public var categoryIdentifier: String?
    
    @objc public init(withRequestId requestIdentifier: String) {
        
        self.requestIdentifier = requestIdentifier
        
        super.init()
    }
    
    @objc public init(withRequestId requestIdentifier: String, title: String?, body: String?) {
        
        self.requestIdentifier = requestIdentifier
        self.title = title
        self.body = body
        
        super.init()
    }
}
