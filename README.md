# IoT Smart House

A simple project that showcases the use of [Hana Cloud Platform](https://account.hanatrial.ondemand.com/) service for [Internet of Things](https://hcp.sap.com/capabilities/iot.html) connecting to a [ESP3266](https://espressif.com/en/products/hardware/esp8266ex/overview) board using the [mqtt](http://mqtt.org/) protocol.

## Reinnovate

The reinnovate presentations can be found on the `/doc/` root folder.

## Contribute

If you want to contribute by adding features or fixing bugs feel free to create a [pull resquest](https://github.com/flatlining/iot.smarthouse/pulls) or open an [issue](https://github.com/flatlining/iot.smarthouse/issues).

## Structure

- /iotsmarthouseapp/: HTML application for SAP HCP
  - /doc/: app specific documentation, e.g.: required destination files
- /iotsmarthouseesp/: Firmware for esp8266ex
  - /doc/: firmware specific documentation, e.g.: board layout & ESP8266 pinout

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

During the deployment of the solution, some customization with your personal data will be required. to make it easy to remember values that need to be customized is recommended to copy-paste the following cheat sheet:

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
mqttServer | iot.eclipse.org |
mqttServerPort | 1883 |
mqttClientName | my-iot-sensor |
msgSrvMqttDataTopic | iot/data/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
msgSrvMqttPushTopic | iot/push/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
msgSrvHumidityEndpoint | T_IOT_F7A21C819057C93F4AE2 |
msgSrvTemperatureEndpoint | T_IOT_3E379B643794DFA2FC6D |
wifiSsid | MyHomeInternet |
wifiPassword | mySuperSTRONGP4ssw0rd |

### Create a HCP account

First you need to [Sign up for an free trial account on SAP HANA Cloud Platform](http://go.sap.com/developer/tutorials/hcp-create-trial-account.html), this is where the app will be hosted, the device registered and the messages handled.

If you would like to know more about HCP check one of the online courses at [OpenSAP](https://open.sap.com/courses).

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
hcpAccount | p123456trial |
hcpUser | p123456 |
hcpPassword | 654321 |

### Configure Internet of Thing Services

Now you have to configure [SAP HANA Cloud Platform Internet of Things Services](https://help.hana.ondemand.com/iot/), for that, first [enable the service](https://help.hana.ondemand.com/iot/frameset.htm?53ad6006e50f4b0ca02402daa6da5bb5.html) itself, then [assign the required role](https://help.hana.ondemand.com/iot/frameset.htm?c8532bcf28754b248dec71a518463865.html) to your user.

### Deploy a new device to IoT Services

You can customize and create net devices by [accessing the Internet of Things Services Cockpit](https://help.hana.ondemand.com/iot/frameset.htm?72c3de34c79544358c9b97824b6ad7e9.html).

#### Message Types

The first step is to [create the message types](https://help.hana.ondemand.com/iot/frameset.htm?a7bf661819bc415d87bee5818e763fad.html) your device will be able to send / receive. We will need three for temperature, humidity and led control.

Use the following values for each message type:

- Name: Temperature (°C)
  - Fields:
    - Position 1:
      - Name: temperature
      - Type: float
- Name: Humidity (%)
  - Fields:
    - Position 1:
      - Name: humidity
      - Type: float
- Name: Toggle Light
  - Fields:
    - Position 1:
      - Name: lightId
      - Type: integer

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
iotSrvMessageTypeHumidity | f7a21c819057c93f4ae2 |
iotSrvMessageTypeTemperature | 3e379b643794dfa2fc6d |
iotSrvMessageTypeLedControl | d417504b02b488b1c74b |

#### Device Types

To use the message types you have to [create a device type](https://help.hana.ondemand.com/iot/frameset.htm?5b3d7177333b4f3080779d1f5a31d649.html), this is a template that later you will use to create an actual device in the IoT Services.

Use the following values for the device type:

- Name: Smart House Controller
  - Message Types:
    - Message Type: Temperature (°C)
      - Direction: From Device
    - Message Type: Temperature (°C)
      - Direction: From Device
    - Message Type: Toggle Light
      - Direction: To Device

#### Devices

Finally, you need to [create a device](https://help.hana.ondemand.com/iot/frameset.htm?89d3a1b8128a4875b579803d360e580c.html) based on the Device Type.

Use the following values for the device:

**Important!** You will only have access to the device token in the moment you create it, so make sure to take note (or you will have to generate a new one).

- Name: use your creativity!
  - Device Type: Smart House Controller

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
iotSrvDeviceId | b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
iotSrvDeviceToken | a2bR9YGwUVFZyeuMpaKwBpZpzbSrsJd |

### Configure Message Management Service (MMS)

To receive and store the messages transmitted by the device you will need to [deploy the Message Management Service](https://help.hana.ondemand.com/iot/frameset.htm?989ec8c379684ae696561822843cdc9e.html).

### Configure MMS as a MQTT client

To send and receive messages from the device using the MQTT protocol you will need to configure the MMS as a MQTT client and connect it to a MQTT broker. You can use the public-free-to-use broker provided by the Eclipse Foundation, just keep in mind that any person that knows your topics can subscribe and publish to them.

To configure the [MQTT over TCP](https://help.hana.ondemand.com/iot/frameset.htm?a9764708d68b43e59c823218d1aa6346.html), open the **Configure Message Management Service** tile and enter the following values:

Key | Value
----|------
mms.mqtt.broker_url | tcp://iot.eclipse.org:1883
mms.mqtt.enable | on

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
mqttServer | iot.eclipse.org |
mqttServerPort | 1883 |
mqttClientName | my-iot-sensor |

#### MQTT topics

Open the tile **Messaging through MQTT over TCP/SSL** on the MMS Cockpit, paste the previously noted *iotSrvDeviceId* on the **Device ID** input field.

And take note of the **Topic** of the **Publish Message** section and **Push Topic** of the **Subscribe Message** section.

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
msgSrvMqttDataTopic | iot/data/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |
msgSrvMqttPushTopic | iot/push/iotmmsp123456trial/v1/b3da17f6-8e41-48e4-8540-9bfe5124f7ec |

### OData Service and Endpoint

To findout your MMS service endpoint open the tile **Display stored messages** and then click on **OData API** button you can check on the popup your service metadata url.

By open the *$metadata* url you can check all the tables available on the service, each table is related to a Message Type on the IoT Service.

Keep in mind that each table is only created once the first message to it's message type arrive, so unless you have [posted something](https://help.hana.ondemand.com/iot/frameset.htm?8e1c277be0cd4854943a15f86188aaec.html) to your previously created Message Types no table will be displayed for them. Luckily the naming convention for table is **T\_IOT_[MESSAGE_TYPE_ID_IN_UPPERCASE]**, so if your Message Type ID is *f7a21c819057c93f4ae2* the related table will be *T\_IOT_T_IOT_F7A21C819057C93F4AE2*, using this rules is easy do infer your endpoints.

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
msgSrvHumidityEndpoint | T_IOT_F7A21C819057C93F4AE2 |
msgSrvTemperatureEndpoint | T_IOT_3E379B643794DFA2FC6D |

### Wi-Fi Information

For Wi-Fi you will only need the name of the netword(ssid) and the password to connect, as if you were connecting with a computer.

You can know fill on your cheat sheet:

Variable | Example | Your Values
---------|---------|------------
wifiSsid | MyHomeInternet |
wifiPassword | mySuperSTRONGP4ssw0rd |

### Customizing App code and ESP8266 firmware

At this point you should have you **cheat sheet* filled, now you only need to replace the placeholders in both the app (*iotsmarthouseapp* folder) and the firmware (*iotsmarthouseesp* folder).

All placeholders use the pattern **&lt;TODO:placeHolderName&gt;**, so simply use the **Search in Directory** function of [Atom](https://atom.io/) to search and replace each variable on the cheat sheet, e.g.: search for &lt;TODO:wifiSsid&gt; and replace it with *MyHomeInternet*.

### Deployment

#### App code to HCP

It's not on the scope of this tutorial to tech how to deploy a HTML application to HCP, you can check the [official documentation](https://sapui5.hana.ondemand.com/) for help.

##### Destinations

For the app to access both MMS and IoT Services information, is required to add both destinations to your HCP.

You can find the destination files to import in the `/doc/` folder of the `/iotsmarthouseesp/` project, just make sure to replace the placeholders with the correct values.

Refer to the official documentation on how to [configure](https://help.hana.ondemand.com/help/60735ad11d8a488c83537cdcfb257135.html) and [import](https://help.hana.ondemand.com/help/frameset.htm?a2550c3fcf2b430f94f99072677bf9ec.html) destinations.

#### Firmware to ESP8266

It's not on the scope of this tutorial to tech how to upload a firmware to the ESP8266, you can check the [Arduino documentation](https://www.arduino.cc/en/Main/Howto) for help

### Conclusion

You must now have a working IoT application work, and by accessing you app url you must be able to see Temperature and Humidity logs as well as control the led via web.

## References

* [SAP HANA Cloud Platform Internet of Things Services](https://help.hana.ondemand.com/iot/frameset.htm)
* [Consuming Internet of Things Services](https://help.hana.ondemand.com/webide_hat/frameset.htm?8270730208e74b2d91b39a5eaa7315c8.html)
  * [Configuring Destinations for the Message Management Service and Remote Device Management Service](https://help.hana.ondemand.com/webide_hat/frameset.htm?86424e00177142e99a8d50ad99706233.html)
  * [Inject the Internet of Things library into your project](https://help.hana.ondemand.com/webide_hat/frameset.htm?44ad459c32124afc8f10e6436f239622.html)
