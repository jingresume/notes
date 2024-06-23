# DTS

## 节点

### 节点属性

+ compatible : 包含该属性的节点，linux内核会为其生成platform_device结构体
+ 利用platform_device和platform_driver分离硬件配置和软件代码

dtb -> device_node -> platform_device
