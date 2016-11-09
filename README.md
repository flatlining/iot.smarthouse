# IoT Smart House

A simple project that showcases the use of [Hana Cloud Platform](https://account.hanatrial.ondemand.com/) service for [Internet of Things](https://hcp.sap.com/capabilities/iot.html) conecting to a [ESP3266](https://espressif.com/en/products/hardware/esp8266ex/overview) board using the [mqtt](http://mqtt.org/) protocol.

## Requirements

### Knowledge

- For the **Internet**
  - [HCP](https://open.sap.com/courses/hanacloud1)
  - HTML
  - JavaScript
  - GIT
- For the **Things**
  - Programming language / programming logic
  - Arduino or related prototyping platforms
  - C++ knowledge is a plus (ba dum tssshhh)
  - Eletronic knowledge is nice but not required

### Tools

- App development can be done with HCP [Web IDE](https://hcp.sap.com/capabilities/devops/web-ide.html) or any local editor like [Atom](https://atom.io/)
- Although the ESP8266 development was done using  [PlatformIO](http://platformio.org/), is also possible to use the [Arduino IDE](https://www.arduino.cc/en/Main/Software) with little work 

## Tutorial

#### Cheat Sheet

During the deployment of the solution, some customization with your personal data will be required. to make it easy to remember values that need to be customized is recomender to copy-paste the following cheat sheet:

Variable | Example | Your Values
---------|---------|------------
hcpAccount | p123456trial |
hcpUser | p123456 |
hcpPassword | 654321 |
iotSrvMessageTypeHumidity | f7a21c819057c93f4ae2 |
iotSrvMessageTypeTemperature | 3e379b643794dfa2fc6d |
iotSrvMessageTypeLedControl | d417504b02b488b1c74b |
iotSrvDeviceId | b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
iotSrvDeviceToken | a2bR9YGwUVFZyeuMpaKwBpZpzbSrsJd |
msgSrvMqttDataTopic | iot/data/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
msgSrvMqttPushTopic | iot/push/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
msgSrvHumidityEndpoint | T_IOT_F7A21C819057C93F4AE2 |
msgSrvTemperatureEndpoint | T_IOT_3E379B643794DFA2FC6D |
wifiSsid | MyHomeInternet |
wifiPassword | mySuperSTRONGP4ssw0rd |
mqttServer | iot.eclipse.org |
mqttServerPort | 1883 |
mqttClientName | my-iot-sensor |

### Create a HCP account

First you need to [Sign up for an free trial account on SAP HANA Cloud Platform](http://go.sap.com/developer/tutorials/hcp-create-trial-account.html), this is where the app will be hosted, the device registeres and the messages handled.

If you would like to know more about HCP check one of the online courses at [OpenSAP](https://open.sap.com/courses).

## References

* [SAP HANA Cloud Platform Internet of Things Services](https://help.hana.ondemand.com/iot/frameset.htm)
* [Consuming Internet of Things Services](https://help.hana.ondemand.com/webide_hat/frameset.htm?8270730208e74b2d91b39a5eaa7315c8.html)
  * [Configuring Destinations for the Message Management Service and Remote Device Management Service](https://help.hana.ondemand.com/webide_hat/frameset.htm?86424e00177142e99a8d50ad99706233.html)
  * [Inject the Internet of Things library into your project](https://help.hana.ondemand.com/webide_hat/frameset.htm?44ad459c32124afc8f10e6436f239622.html)
