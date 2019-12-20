Pod::Spec.new do |s|

	s.name	= 'SpotzCNCCustomerSDK'
	s.summary = 'SpotzCNCCustomerSDK'

	s.version = '1.11.1'
	s.platform = :ios,'9.0'
	s.ios.deployment_target = '9.0'

	s.homepage = 'http://www.localz.com'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2019 Localz Pty Ltd.
			LICENSE
	}
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.source = { :git => 'https://github.com/localz',
		 		 :tag => s.version }

	s.requires_arc = true
	s.static_framework = true
	s.swift_version = '5.1'
	s.requires_arc = true
	s.pod_target_xcconfig = {
		'SWIFT_VERSION' => '5.1',
		'FRAMEWORK_SERCH_PATHS' => '$(inherited)',
		'DEFINES_MODULE' => 'YES',
		'CLANG_ENABLE_MODULES' => 'YES',
		'SWIFT_OBJC_INTERFACE_HEADER_NAME' => 'SpotzCNCCustomerSDK-Swift.h'
	}
	
	s.source_files  =  'SpotzCNCSDK/SpotzCNCCustomerSDK.framework/Headers/*.{swift,h}', 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.preserve_paths = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework/*'
	s.vendored_frameworks = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.frameworks = 'CoreLocation','CoreBluetooth'

	s.dependency 'SpotzSDK', '~> 3.2.8.1'
	s.dependency 'LocalzPushSDK'
end
