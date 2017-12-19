Pod::Spec.new do |s|
	s.name	= 'SpotzCNCCustomerSDK'
	s.platform = :ios,'7.0'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2017 Localz Pty Ltd.
			LICENSE
	}
	s.version = '1.8.1'
	s.summary = 'SpotzCNCCustomerSDK'
	s.homepage = 'http://www.localz.com'
	s.author = { 
		'Localz Pty Ltd' => 'info@localz.com' 
	}
	s.requires_arc = true
	s.ios.deployment_target = '7.0'
	s.xcconfig = { 
		'FRAMEWORK_SERCH_PATHS' => '$(inherited)' 
	}
	s.source = {:git=>'https://github.com/localz'}
	s.source_files  = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework', 'SpotzCNCSDK/SpotzCNCCustomerSDK/**/*.{h,m}'
	s.preserve_paths = 'SpotzCNCCustomerSDK.framework'
	s.vendored_frameworks = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.frameworks = 'CoreLocation','CoreBluetooth'

	# Please also include:
	#s.dependency 'https://github.com/localz/Spotz3-iOS-SDK'
	#s.dependency 'https://github.com/localz/SpotzPushSDK'
end
