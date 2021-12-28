# esp32_servos_mqtt
Controlling Servos with a Esp-wroom-32 via MQTT with an Android Client

Added two files, first is the schematic for the connection with ESP-WROOM-32, the PSU and the four servos, second is 
the Arduino IDE file you upload to the ESP32.

For the MQTT Broker/Server I used Mosquitto in Ubuntu 20.04LTS Desktop (this can be installed in a RBPi or any other OS)
https://mosquitto.org/download/

You can Subscribe to topics in your own server using "localhost" as the direction of the MQTT Broker/Server 
and send messages to the topic using also "localhost" as the direction of the MQTT Broker/Server, the ESP32 will 
receive these messages without further interaction, just make sure you use the same topic specified in the ESP32 
code.

For the Android App I was going to write down an App but for testing sakes I just downloaded a client from the 
Play Store (certainly theres a MQTT client in iOS) "MQTT Dash" which you can download from here 
https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=es_MX&gl=US 
pretty sure you can use any of your choice, but this is the one I'm using in the video.
