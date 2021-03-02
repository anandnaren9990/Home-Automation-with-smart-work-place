#include <ESP8266WiFi.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID "Anand"//Your wifi name
#define WIFI_PASS "qwertyuiop"//your wifi password

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "anandnaren9990" //Your adafruit name
#define MQTT_PASS "aio_qxtW75w0J76r510v0EA7fYwSr4e5" //Your adafruit AIO key

int led = D1;
int led1 = D2;
int led2 = D3;
int led3 = D4;
int led4 = D7;
int ldr = D0;
//WiFiUDP ntpUDP;
int ldr_val;
int k=0;
//NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/MAINLIGHT1");
Adafruit_MQTT_Publish MainLight1Status = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/MainLight1Status");

Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/MAINLIGHT2");
Adafruit_MQTT_Publish MainLight2Status = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/MainLight2Status");

Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/REGLIGHT");
Adafruit_MQTT_Publish RLightStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/RLightStatus");

Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/WORKLIGHT");
Adafruit_MQTT_Publish WLightStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/WLightStatus");

Adafruit_MQTT_Subscribe Mode_Work = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/WORKMODE");
Adafruit_MQTT_Publish WorkModeStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/WorkModeStatus");

void setup()
{
  
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);


  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  digitalWrite(LED_BUILTIN, LOW);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }

  Serial.println("OK!");

  //Subscribe to the Lights topic
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light4);
  mqtt.subscribe(&Mode_Work);

  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ldr,INPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);

  //timeClient.begin();

}

void loop()
{
  
  
  //Connect/Reconnect to MQTT
  MQTT_connect();
  
  
  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    
    //If we're in here, a subscription updated...
    if (subscription == &Light1)
    {
      //Print the new value to the serial monitor
      Serial.print("Light1: ");
      Serial.println((char*) Light1.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) Light1.lastread, "ON"))
      {
        //active low logic
        digitalWrite(led, LOW);
        MainLight1Status.publish("ON");
      }
      else if (!strcmp((char*) Light1.lastread, "OFF"))
      {
        digitalWrite(led, HIGH);
        MainLight1Status.publish("OFF");

      }
      else
      {
        MainLight1Status.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }
    if (subscription == &Light2)
    {
      //Print the new value to the serial monitor
      Serial.print("Light2: ");
      Serial.println((char*) Light2.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) Light2.lastread, "ON"))
      {
        //active low logic
        digitalWrite(led1, LOW);
        MainLight2Status.publish("ON");
      }
      else if (!strcmp((char*) Light2.lastread, "OFF"))
      {
        digitalWrite(led1, HIGH);
        MainLight2Status.publish("OFF");

      }
      else
      {
        MainLight2Status.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }
    if (subscription == &Light3)
    {
      //Print the new value to the serial monitor
      Serial.print("Light3: ");
      Serial.println((char*) Light3.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) Light3.lastread, "ON"))
      {
        //active low logic
        digitalWrite(led2, LOW);
        RLightStatus.publish("ON");
      }
      else if (!strcmp((char*) Light3.lastread, "OFF"))
      {
        digitalWrite(led2, HIGH);
        RLightStatus.publish("OFF");

      }
      else
      {
        RLightStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }

    
    if (subscription == &Light4)
    {
      //Print the new value to the serial monitor
      Serial.print("Light4: ");
      Serial.println((char*) Light4.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) Light4.lastread, "ON"))
      {
        //active low logic
        digitalWrite(led3, LOW);
        //WLightStatus.publish("ON");
      }
      else if (!strcmp((char*) Light4.lastread, "OFF"))
      {
        digitalWrite(led3, HIGH);
        //WLightStatus.publish("OFF");

      }
      else
      {
        //WLightStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }
    
    if (subscription == &Mode_Work)
    {
      //Print the new value to the serial monitor
      Serial.print("Work Mode: ");
      Serial.println((char*) Mode_Work.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) Mode_Work.lastread, "ON"))
      {
        k=1;
        Serial.print(k);
      }
      
      else if (!strcmp((char*) Mode_Work.lastread, "OFF"))
      {
        WorkModeStatus.publish("OFF");
        k = 0;
        Serial.print(k);
        digitalWrite(led4,HIGH);
        
      }
      else
      {
        WorkModeStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }
    
    
  }
  ldr_val = digitalRead(ldr);
    if((k==1)&&ldr_val!=0)
    {
      digitalWrite(led4,LOW);
    }
  //Serial.println(ldr_val);
  //  if (!mqtt.ping())
  //  {
  //    mqtt.disconnect();
  //  }
}


void MQTT_connect()
{

  //  // Stop if already connected
  if (mqtt.connected() && mqtt.ping())
  {
    //    mqtt.disconnect();
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  //Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      ESP.reset();
    }
  }
  //Serial.println("MQTT Connected!");
}
