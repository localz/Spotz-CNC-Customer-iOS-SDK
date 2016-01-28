Pod::Spec.new do |s|
	s.name	= 'SpotzCNCCustomerSDK-Device'
	s.platform = :ios,'8.0'
	s.license = 'Commercial License'
	s.version = '3.1.0.1'
	s.summary = 'SpotzCNCCustomerSDK'
	s.homepage = 'http://www.localz.com'
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.requires_arc = true
	s.ios.deployment_target = '8.0'
	s.source_files  = 'Device/SpotzCNCCustomerSDK.framework', 'Device/SpotzCNCCustomerSDK/**/*.{h,m}'
	s.public_header_files = 'Device/SpotzCNCCustomerSDK/**/*.h'
	s.vendored_frameworks = 'Device/SpotzCNCCustomerSDK.framework'
	s.frameworks = 'CoreLocation','CoreBluetooth'
end
