Pod::Spec.new do |spec|

  spec.name         = "JVSOpenSDK"
  spec.version      = "3.0.0"
  spec.summary      = "云视通开放平台SDK"
  spec.description  = "云视通开放平台SDK,开发者可以用SDK开发APP"
  spec.homepage     = "https://github.com/Jovision-SDK/JVSPlayerSDK"
  spec.license      = { :type => "MIT", :file => "LICENSE" } 
  spec.author       = { "zhangxiaodong" => "zhangxiaodong@jovision.com" }
  spec.platform     = :ios, "8.0"  
  spec.source       = { :git => "https://github.com/Jovision-SDK/JVSPlayerSDK.git", :tag => spec.version.to_s }
  spec.frameworks   = 'CFNetwork',  'AudioToolbox', 'AVFoundation','OpenGLES','ExternalAccessory','MediaPlayer'
  spec.libraries    = "c","c++"
  spec.vendored_frameworks = 'JVSPlayerSDK.framework'
  spec.user_target_xcconfig =   {'OTHER_LDFLAGS' => ['-lObjC','-all_load']}
  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

end