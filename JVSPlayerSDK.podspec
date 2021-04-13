Pod::Spec.new do |spec|

  spec.name         = "JVSPlayerSDK"
  spec.version      = "1.0.0"
  spec.summary      = "云视通开放平台SDK"
  spec.description  = "云视通开放平台SDK,开发者可以用SDK开发APP"
  spec.homepage     = "https://github.com/Jovision-SDK/JVSPlayerSDK"
  spec.license      = { :type => "MIT", :file => "LICENSE" } 
  spec.author       = { "zhangxiaodong" => "zhangxiaodong@jovision.com" }
  spec.platform     = :ios, "10.0"  
  spec.source       = { :git => "https://github.com/Jovision-SDK/JVSPlayerSDK.git", :tag => spec.version.to_s }
  spec.frameworks   = 'CoreLocation', 'CoreAudio', 'CoreVideo', 'CoreMedia', 'CFNetwork', 'VideoToolbox', 'AudioToolbox', 'AVFoundation','OpenGLES','MediaAccessibility','MediaPlayer'
  spec.libraries    = "z"
  spec.vendored_frameworks = 'JDE05.framework','JVSPlayerSDK.framework'

end
