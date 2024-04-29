
Pod::Spec.new do |spec|

  spec.name         = "YF_Remote_Temp"
  spec.version      = "1.1.9"
  spec.summary      = "在线参数"

  spec.description  = <<-DESC
  iOS在线参数功能库
                   DESC

  spec.homepage     = "https://github.com/leonard-li/YF_Remote_Temp.git"


  spec.license      = { :type => "MIT", :file => "LICENSE" }

  spec.author             = { "leonard.li" => "495145872@qq.com" }

  spec.ios.deployment_target = "9.0"

  spec.source       = { :git => "https://github.com/leonard-li/YF_Remote_Temp.git", :tag => spec.version }

  spec.vendored_frameworks = 'YFConfig.framework'

  spec.requires_arc = true
  spec.resource_bundles = {
    'YF_RemoteResources' => ['Resources/PrivacyInfo.xcprivacy']
  }

  spec.dependency "YF_DataAcqu", '>= 5.2.1'

end
