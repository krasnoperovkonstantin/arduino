#include <jsonlib.h>
#include <ESP8266WiFi.h>
#include <SimpleDHT.h>

#include <Arduino.h>
#include <U8g2lib.h>


#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

 U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


#ifndef STASSID
#define STASSID "router"
#define STAPSK  "krasnoperovkonstantin"
#endif


String str ;
int countstr=0;
unsigned int displaydelay=10;
const char* ssid     = STASSID;
const char* password = STAPSK;
//const char* DegreeSymbol = 167;

const char* host = "b90681jr.beget.tech";

const uint16_t port = 80;


// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 5;
SimpleDHT11 dht11(pinDHT11);
/*
void setfont (String font){
    if (font == "u8g2_font_4x6_t_cyrillic"){ u8g2.setFont(u8g2_font_4x6_t_cyrillic); }
    if (font == "u8g2_font_5x7_t_cyrillic"){ u8g2.setFont(u8g2_font_5x7_t_cyrillic); }
    if (font == "u8g2_font_5x8_t_cyrillic"){ u8g2.setFont(u8g2_font_5x8_t_cyrillic); }
    if (font == "u8g2_font_6x12_t_cyrillic"){ u8g2.setFont(u8g2_font_6x12_t_cyrillic); }
    if (font == "u8g2_font_6x13_t_cyrillic"){ u8g2.setFont(u8g2_font_6x13_t_cyrillic); }
    if (font == "u8g2_font_6x13B_t_cyrillic"){ u8g2.setFont(u8g2_font_6x13B_t_cyrillic); }
    if (font == "u8g2_font_7x13_t_cyrillic"){ u8g2.setFont(u8g2_font_7x13_t_cyrillic); }
    if (font == "u8g2_font_8x13_t_cyrillic"){ u8g2.setFont(u8g2_font_8x13_t_cyrillic); }
    if (font == "u8g2_font_9x15_t_cyrillic"){ u8g2.setFont(u8g2_font_9x15_t_cyrillic); }
    if (font == "u8g2_font_10x20_t_cyrillic"){ u8g2.setFont(u8g2_font_10x20_t_cyrillic); }
    if (font == "u8g2_font_cu12_t_cyrillic"){ u8g2.setFont(u8g2_font_cu12_t_cyrillic); }
    if (font == "u8g2_font_unifont_t_cyrillic"){ u8g2.setFont(u8g2_font_unifont_t_cyrillic); }
    if (font == "u8g2_font_haxrcorp4089_t_cyrillic"){ u8g2.setFont(u8g2_font_haxrcorp4089_t_cyrillic); }
}

void display (String json){
  String element;
  // очищаем память дисплея
  u8g2.clearBuffer();
  for (byte i=0;i<100;i++)
  {
    element = jsonExtract(jsonExtract(json, "display"), "element"+String(i));
    Serial.print("element"+String(i)+":"); Serial.println(element);
    
    String type = jsonExtract(element,"type");  
     Serial.print("type:"); Serial.println(type);   
    if (type == "text"){
      setfont (jsonExtract(element,"font"));
      u8g2.setCursor(jsonExtract(element,"cursorx").toInt(), jsonExtract(element,"cursory").toInt());
      String text = jsonExtract(element,"string");
      u8g2.print(text);
        Serial.print("string:"); Serial.println(text);   
    }

    if (type == "box"){  
      u8g2.drawBox(jsonExtract(element,"cursorx").toInt(), jsonExtract(element,"cursory").toInt(),jsonExtract(element,"sizex").toInt(), jsonExtract(element,"sizey").toInt());
    }

    if (type == "line"){  
      u8g2.drawLine(jsonExtract(element,"cursorx").toInt(), jsonExtract(element,"cursory").toInt(),jsonExtract(element,"sizex").toInt(), jsonExtract(element,"sizey").toInt());
    }
      
    if (type == "frame"){  
      u8g2.drawFrame(jsonExtract(element,"cursorx").toInt(), jsonExtract(element,"cursory").toInt(),jsonExtract(element,"sizex").toInt(), jsonExtract(element,"sizey").toInt());
    }
    if (type == "config"){  
      u8g2.setContrast(jsonExtract(element,"contrast").toInt());
      displaydelay=jsonExtract(element,"delay").toInt();
    }
  }
  u8g2.sendBuffer();
}

{"datetime":"2020-01-26 00:22:06","temperature_now":"-10","humidity_now":"40","speed_now":"5",
"temperature_tomorrow":"0","humidity_tomorrow":"0","speed_tomorrow":"0","time":"02:10:32"}

//string.length()
*/
String setlenstr (String s, byte l){
  if ( s.length() == l) return s;
  if ( s.length() < l) return  (" " + s);
  if ( s.length() < l+1) return  ("  " + s);
  if ( s.length() < l+2) return  ("   " + s);
}

void display (String json){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);

  u8g2.setCursor (0, 9);
  u8g2.print("Сейчас " + setlenstr((String)jsonExtract(json, "temperature_now"), 3)  + " C" + setlenstr((String)jsonExtract(json, "humidity_now"), 3) + "%" + setlenstr((String)jsonExtract(json, "speed_now"), 3) + "м/c"  );
  u8g2.setCursor (0, 18);
  u8g2.print("Утро   " + setlenstr((String)jsonExtract(json, "temperature_morning"), 3)  + " C" + setlenstr((String)jsonExtract(json, "humidity_morning"), 3) + "%" + setlenstr((String)jsonExtract(json, "speed_morning"), 3) + "м/c"  );
  u8g2.setCursor (0, 27);
  u8g2.print("Вечер  " + setlenstr((String)jsonExtract(json, "temperature_evening"), 3)  + " C" + setlenstr((String)jsonExtract(json, "humidity_evening"), 3) + "%" + setlenstr((String)jsonExtract(json, "speed_evening"), 3) + "м/c"  );
  u8g2.setCursor (0, 36);
  u8g2.print("Левая  " + setlenstr((String)jsonExtract(json, "temperature_left"), 3)  + " C" + setlenstr((String)jsonExtract(json, "humidity_left"), 3) + "%" );
  u8g2.setCursor (0, 45);
  u8g2.print("Правая " + setlenstr((String)jsonExtract(json, "temperature_right"), 3)  + " C" + setlenstr((String)jsonExtract(json, "humidity_right"), 3) + "%" );
 
  u8g2.setFont(u8g2_font_6x12_mf);
  char d = 176;
  u8g2.setCursor (59, 10);
  u8g2.print(d);
  u8g2.setCursor (59, 19);
  u8g2.print(d);  
  u8g2.setCursor (59, 28);
  u8g2.print(d);  
  u8g2.setCursor (59, 37);
  u8g2.print(d);
  u8g2.setCursor (59, 46);
  u8g2.print(d);
  
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  u8g2.setCursor (0, 54);
  u8g2.print(jsonExtract(json, "message1") + jsonExtract(json, "message2"));
  u8g2.setCursor (0, 63);
  u8g2.print((String)jsonExtract(json, "time") + "г.");
  u8g2.setContrast(jsonExtract(json,"contrast").toInt());
  u8g2.sendBuffer();
  displaydelay=jsonExtract(json,"delay").toInt();
}

void displayfailed (){
   u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);

  u8g2.setCursor (0, 9);
  u8g2.print("Сервер не доступен");
  u8g2.setCursor (0, 18);
  u8g2.print("WiFi status: " + String (WiFi.status()));
  u8g2.setCursor (0, 27);
  u8g2.print("IP: " );
  u8g2.print(WiFi.localIP());
  u8g2.setCursor (0, 45);
 
  
  u8g2.setContrast(0);
  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);
 // начало работы с дисплеем
  u8g2.begin();
  // включаем поддержку UTF8
  u8g2.enableUTF8Print();

  //u8g2.drawBox(0,0,128,64);
  //  u8g2.sendBuffer();
//delay(5000);
  u8g2.setContrast(0);
     u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  u8g2.setCursor(0,12);
  u8g2.print("Подключение к ");
  u8g2.setCursor(0,24);
  u8g2.print(ssid);
  u8g2.sendBuffer();
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    u8g2.print(".");
    u8g2.sendBuffer();
  }

  u8g2.setCursor(0,36);

  u8g2.print("IP: ");
  u8g2.print(WiFi.localIP());
  u8g2.sendBuffer();
  delay(1000);
  // dht.begin();
}

void loop() {
   // read without samples.
 
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    displayfailed ();
    delay(10000);
    return;
  } else
  {
        
      

    Serial.println("connected to server");
    // Make a HTTP request:
    //client.println("GET /bot.php?bot902895700:AAEsDU-_fzvGjxBgq0bGY1Y28I7kuqxIArU/sendMessage?chat_id=947789479&text=температура=",(int)temperature,"C HTTP/1.1");
    /*
    client.print("GET /datacollection.php?");
    client.print("id_sensor1=1&value1=");
    client.print((int)temperature);
    client.print("&id_sensor2=2&value2=");
    client.print((int)humidity);
*/
    client.print("GET /display.php");
    
    client.println(" HTTP/1.1");
    
    client.println("Host: b90681jr.beget.tech");
    client.println("User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:18.0) Gecko/20100101 Firefox/18.0");
    client.println("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    client.println("Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
    client.println("Accept-Encoding: deflate");
    client.println("Cookie: wp-settings");
    client.println("Connection: keep-alive");
    client.println("Connection: close");
    client.println();
    
  }


//  str="";
  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(10000);
      return;

      
    }
  }


 str="";

// char ch2;
 //   bool flag1 = false;
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here

  while (client.available()) {
    char ch = static_cast<char>(client.read());
    str += ch;
    Serial.print(ch);
    
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 2000) {
        break;
      }
    }
  }


  
  
 str += '\0';
 Serial.println();
 Serial.println(str.indexOf("HTTP/1.1 200"));
 //Serial.print(str.length());
 if (str.indexOf("HTTP/1.1 200")>=0){
   display (str);
 } else {
    displayfailed ();
 }
 

  // Close the connection
  
  Serial.println("closing connection");
  client.stop();

  delay(1000*displaydelay); // execute once every 5 minutes, don't flood remote service
}
