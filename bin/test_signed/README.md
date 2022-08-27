## Introduction

> Test signatures are for testing purposes only and cannot be used in normal environments. For the officially released version, please remember to sign it yourself. For companies without a signature, you can contact us to apply for a version with an enterprise signature.

For files in the current directory that are signed by the test signature, the driver can be loaded normally after the test mode is enabled.

## Enable test signing mode

In the **admin** command line, execute bcdedit /set testsigning on

After execution, **restart** will take effect.

------

## 说明

> 测试签名仅供测试，没法在正常环境使用。正式发布的版本，请记得自己签名，对于没有签名的企业，可以联系我们申请带企业签名版本。

当前目录下文件的通过测试签名签署的文件，在开启了测试模式后，驱动就可以正常加载。

## 开启测试签名模式

在**管理员**命令行下，执行  bcdedit /set testsigning on

执行后**重启**生效。





