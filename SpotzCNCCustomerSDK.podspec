Pod::Spec.new do |s|

	s.name	= 'SpotzCNCCustomerSDK'
	s.summary = 'SpotzCNCCustomerSDK'

	s.version = '1.9.1'
	s.platform = :ios,'8.0'
	s.ios.deployment_target = '8.0'

	s.homepage = 'http://www.localz.com'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2018 Localz Pty Ltd.
			LICENSE
	}
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.source = { :git => 'https://github.com/localz',
		 		 :tag => s.version }

	s.requires_arc = true
	s.static_framework = true
	s.swift_version = '4.2'
	s.requires_arc = true
	s.xcconfig = {
		'FRAMEWORK_SERCH_PATHS' => '$(inherited)',
		'DEFINES_MODULE' => 'YES',
		'CLANG_ENABLE_MODULES' => 'YES',
		'SWIFT_OBJC_INTERFACE_HEADER_NAME' => 'SpotzCNCCustomerSDK-Swift.h'
	}
	
	s.source_files  =  'SpotzCNCSDK/SpotzCNCCustomerSDK.framework/Headers/*.{swift,h}', 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.module_map = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework/Modules/module.modulemap'
	s.module_name = 'SpotzCNCCustomerSDK'

	s.preserve_paths = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework/*'
	s.vendored_frameworks = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.frameworks = 'CoreLocation','CoreBluetooth'

	# Please also include:
	 # 'https://github.com/localz/Spotz3-iOS-SDK'
	 # 'https://github.com/localz/SpotzPushSDK'
end
