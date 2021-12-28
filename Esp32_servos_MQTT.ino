#include <PubSubClient.h> //Library for MQTT communication

#include <ESP32Servo.h> //Library for Servo Controlling with ESP32 

#include <WiFi.h> //Library for connecting to WiFi network


const char* ssid = "Xamanek_1"; //your Wifi SSID here
const char* password = "Martinez1984"; //your Wifi password here

const char* mqtt_server = "192.168.1.209"; //ip address to your MQTT Server here

WiFiClient espClient; //
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

Servo servoBase, servo01, servo02, servo03; //Declare your servos variable here
int sB, s1, s2, s3; //these variables help me track the last Servor's position
int delayTimer = 10; //just a variable to set a timer globally for how long it takes to make a step in a given Servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Begin serial com

    WiFi.begin(ssid, password); //initiate our Wifi connection

    while ( WiFi.status() != WL_CONNECTED ) { //while the Wifi status is not connected we try every half second
      delay(500);
      Serial.println("Conectando a WiFi...");
    }

    Serial.println("Conectado a la red WIFI: "); //once it has been connected we print to serial monitor we had success
    Serial.println(ssid); //print to serial monitor the name of the network we are connected
    Serial.println(WiFi.localIP()); //print to serial the ip address given by the router to this device

    client.setServer(mqtt_server, 1883); //start communication with the MQTT Broker/Server
    client.setCallback(callback); //we begin to listen to messages from the MQTT Broker/Server

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    servoBase.setPeriodHertz(50); //We set the frequency of the Servo
    servoBase.attach(18, 500, 2400); //attach the pin, set the min and max for the servo
    servo01.attach(19, 500, 2400);
    servo02.attach(22, 500, 2400);
    servo03.attach(23, 500, 2400);

    servoBase.write(10); //Initialize the servo to 10 degrees
    sB = 10; //save the last know servo position
    servo01.write(10);
    s1 = 10;
    servo02.write(10);
    s2 = 10;
    servo03.write(10);
    s3 = 10;
}

void callback( char* topic, byte* message, unsigned int length ) {
  Serial.print("Mensaje recibido en topico: ");
  Serial.print(topic);
  Serial.print(". Mensaje: ");
  String mensaje; //Variable for storing the message in a String instead of a byte

  for ( int i = 0; i < length; i++ ) { //convert byte* message to string 
    Serial.print( (char)message[i] ); 
    mensaje += (char)message[i]; 
  }
  Serial.println();

  if ( String(topic) == "test01" )  { //check if the message received is the one of the four topics we are subscribed in the MQTT Broker
    
    Serial.println("topico TEST01");
    Serial.println(mensaje);
    if ( mensaje.toInt() > sB ) {
      Serial.println("El punto nuevo es mayor al punto actual y se aumentara");
      for ( int i = sB; i <= mensaje.toInt(); i++ ) {
        servoBase.write(i);
        delay(delayTimer);
      }
      sB = mensaje.toInt();
    } else if ( mensaje.toInt() < sB ) {
      Serial.println("El punto nuevo es menor al punto actual y se decrementara");
      for ( int i = sB; i >= mensaje.toInt(); i-- ) {
        servoBase.write(i);
        delay(delayTimer);
      }
      sB = mensaje.toInt();
    } else {
      Serial.println("El punto nuevo es igual al punto anterior");
      sB = mensaje.toInt();
    }
    
  } else if ( String(topic) == "test02" ) { //check if the message received is the one of the four topics we are subscribed in the MQTT Broker
    
    Serial.println("topico TEST02"); //print to serial name of the topic
    Serial.println(mensaje);  //print to serial the message we received
    if ( mensaje.toInt() > s1 ) { //if the message we received is an int and is larger than the last known servo position (stored in the variable s1)
      Serial.println("El punto nuevo es mayor al punto actual y se aumentara"); //we print to "new point is larger and we are going upwards"
      for ( int i = s1; i <= mensaje.toInt(); i++ ) { //proceed to start moving the servo from the last known position to the new one
        servo01.write(i); //send the new position to the servo
        delay(delayTimer); //delay for as much as is set at the begining of the code
      }
      s1 = mensaje.toInt(); //store the newest known servo position to its tracking variable
    } else if ( mensaje.toInt() < s1 ) { //if the message we received is an int and is smaller than the last known servo position (stored in the variable s1)
      Serial.println("El punto nuevo es menor al punto actual y se decrementara"); //We print "new point is smaller and we are going downwards"
      for ( int i = s1; i >= mensaje.toInt(); i-- ) { //proceed to start moving the servo from the last known position to the new one
        servo01.write(i); //send the new position to the servo
        delay(delayTimer); //delay for as much as is set at the begining of the code
      }
      s1 = mensaje.toInt(); //store the newest known servo position to its tracking variable
    } else {
      Serial.println("El punto nuevo es igual al punto anterior"); //if its not larger or fewer, then it should be equal and so we print "new point is equal to the last one" and do nothing
      s1 = mensaje.toInt(); //store the "newest" servo position
    }
    
  } else if ( String(topic) == "test03" ) { //check if the message received is the one of the four topics we are subscribed in the MQTT Broker
    
    Serial.println("topico TEST03");
    Serial.println(mensaje);
    if ( mensaje.toInt() > s2 ) {
      Serial.println("El punto nuevo es mayor al punto actual y se aumentara");
      for ( int i = s2; i <= mensaje.toInt(); i++ ) {
        servo02.write(i);
        delay(delayTimer);
      }
      s2 = mensaje.toInt();
    } else if ( mensaje.toInt() < s2 ) {
      Serial.println("El punto nuevo es menor al punto actual y se decrementara");
      for ( int i = s2; i >= mensaje.toInt(); i-- ) {
        servo02.write(i);
        delay(delayTimer);
      }
      s2 = mensaje.toInt();
    } else {
      Serial.println("El punto nuevo es igual al punto anterior");
      s2 = mensaje.toInt();
    }
    
  } else if ( String(topic) == "test04" ) { //check if the message received is the one of the four topics we are subscribed in the MQTT Broker

    Serial.println("topico TEST04");
    Serial.println(mensaje);
    if ( mensaje.toInt() > s3 ) {
      Serial.println("El punto nuevo es mayor al punto actual y se aumentara");
      for ( int i = s3; i <= mensaje.toInt(); i++ ) {
        servo03.write(i);
        delay(delayTimer);
      }
      s3 = mensaje.toInt();
    } else if ( mensaje.toInt() < s3 ) {
      Serial.println("El punto nuevo es menor al punto actual y se decrementara");
      for ( int i = s3; i >= mensaje.toInt(); i-- ) {
        servo03.write(i);
        delay(delayTimer);
      }
      s3 = mensaje.toInt();
    } else {
      Serial.println("El punto nuevo es igual al punto anterior");
      s3 = mensaje.toInt();
    }
    
  }

  //Dentro de este metodo van las diferentes "if" para controlar los pines/servos
}

void reconnect() {  //Check if we are connected to the MQTT Broker/Server and subscribe to the topics we are surveing
  while ( !client.connected() ) { //while it is not connected we try again every 5 seconds
    Serial.print("Attempting MQTT connection...");
    if ( client.connect("ESP32Client") ) { //being connection with the MQTT Broker/Server
      Serial.println("Conectado"); 
      client.subscribe("test01"); //Subscribe to this topic on the MQTT Broker/Server
      Serial.println("Subscrito a test01");
      client.subscribe("test02"); //Subscribe to this topic on the MQTT Broker/Server
      Serial.println("Subscrito a test02");
      client.subscribe("test03"); //Subscribe to this topic on the MQTT Broker/Server
      Serial.println("Subscrito a test03");
      client.subscribe("test04"); //Subscribe to this topic on the MQTT Broker/Server
      Serial.println("Subscrito a test04");
    } else {
      Serial.print("Fallo la conexion, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( !client.connected() ) {
    reconnect();
  }

  client.loop();

}
