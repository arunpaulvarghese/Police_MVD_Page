#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>
TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(D7,D8);
byte sensorpin = 9; //d1
char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";  // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
void setup() {
  Serial.begin(9600);
  ss.begin(9600);// declaring the software serial 

  pinMode(sensorpin,INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(sensorpin, INPUT);
}
void loop() {
  client.connect(server, 80);

   while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); //6 will be the floating point number taken as the string value from the gps module.
        client.print(lat_str+'\r');
        
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        client.print(lng_str+'\n');

        String Lat = client.readStringUntil('\r');
        String Lon = client.readStringUntil('\n');
        
        Serial.println("LATITUDE:" + Lat);
        Serial.println("LONGITUDE:" + Lon);
        client.flush();
        client.stop();
        delay(1000);

      }
      
      if (gps.date.isValid())
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)// 10 is just a value that is been displayed within the number ie 01,02,03..ect
          date_str = '0';
        date_str += String(date);

        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month);

        date_str += " / ";

        if (year < 10)
        date_str += '0';
        date_str += String(year);
        Serial.println("DATE:" + date_str);
         delay(1000);

      }

      if (gps.time.isValid())
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        minute = (minute + 30);
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;

        if (hour >= 12)
          pm = 1;
        else
          pm = 0;

        hour = hour % 12;

        if (hour < 10)
          time_str = '0';
        time_str += String(hour);

        time_str += " : ";

        if (minute < 10)
          time_str += '0';
        time_str += String(minute);

        time_str += " : ";

        if (second < 10)
          time_str += '0';
        time_str += String(second);

        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
Serial.println("Time "  +time_str );
      }
else
      {
        latitude = 10.023456;
        lat_str = String(latitude , 6); //6 will be the floating point number taken as the string value from the gps module.
        client.print(lat_str+'\r');
        
        longitude = 77.7777777;
        lng_str = String(longitude , 6);
        client.print(lng_str+'\n');

        String Lat = client.readStringUntil('\r');
        String Lon = client.readStringUntil('\n');
        
        Serial.println("LATITUDE:" + Lat);
        Serial.println("LONGITUDE:" + Lon);
        client.flush();
        client.stop();
        delay(1000);

      }

    }

}
