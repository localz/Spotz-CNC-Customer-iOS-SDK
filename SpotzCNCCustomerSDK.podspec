Pod::Spec.new do |s|

	s.name	= 'SpotzCNCCustomerSDK'
	s.summary = 'SpotzCNCCustomerSDK'

	s.version = '4.2.2'
	s.platform = :ios,'10.0'
	s.ios.deployment_target = '10.0'

	s.homepage = 'http://www.localz.com'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2021 Localz Pty Ltd.
			LICENSE
	}
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.source = { :git => 'https://github.com/localz',
		 		 :tag => s.version }

	s.swift_version = '5.1'
	s.vendored_frameworks = 'SpotzCNCSDK/SpotzCNCCustomerSDK.framework'
	s.frameworks = 'CoreLocation','CoreBluetooth'

	s.dependency 'SpotzSDK', '~> 4.0.2'
	s.dependency 'LocalzPushSDK', '~>4.0.1'
end
