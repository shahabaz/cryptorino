#include <Wire.h>  
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "SSD1306.h"
#include "OLEDDisplayUi.h" 


#define CLEAR 1
#define DONT_CLEAR 0

const char* ssid = "No Internet Access";
const char* password = "sollamudiathu"; 

 

SSD1306  display(0x3c, 5, 4); // Initialise the OLED display using Wire library
 
void setup () {
 
  Serial.begin(115200);



  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();
  WiFi.begin(ssid, password);
    
  display.drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
      lcd(64, 7,DONT_CLEAR,"CONNECTING",10,'C'); 
      lcd(0, 25,DONT_CLEAR,ssid,10,'L'); 
  }
  
  display.clear();
  wifiConnected();
  lcd(64, 35,DONT_CLEAR,"connected",10,'C'); 
  display.display();
  delay(1500);

}
 

void lcd(int x, int y,int clear, String text,int size, char align){

  if(clear == 1){
    display.clear();
  }


  if(align == 'L'){
    display.setTextAlignment(TEXT_ALIGN_LEFT);
  }else if(align == 'C'){
    display.setTextAlignment(TEXT_ALIGN_CENTER);
  }else if(align == 'R'){
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
  }

  if(size = 16){
    display.setFont(ArialMT_Plain_16);    
  }else if(size = 10){
    display.setFont(ArialMT_Plain_10);    
  }else if(size = 24){
    display.setFont(ArialMT_Plain_24);    
  }
  

  display.drawString(x, y+10, text);
  display.display();


}


String getByKey(String json, String key){
 

  int start = json.lastIndexOf(key)+1;
  int end =  json.substring(start+3, json.length()).indexOf('}');
  String part = json.substring(start+3, end-1);
  return part;


}


boolean isValidNumber(String str)
{
   boolean isNum=false;
   if(!(str.charAt(0) == '+' || str.charAt(0) == '-' || isDigit(str.charAt(0)))) return false;

   for(byte i=1;i<str.length();i++)
   {
       if(!(isDigit(str.charAt(i)) || str.charAt(i) == '.')) return false;
   }
   return true;
}

 
const char WiFi_Logo_bits[] PROGMEM = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
  0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
  0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
  0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
  0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
  0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };


void drawCircleDemo() {
    for (int i = 119; i < 128; i++) {
      display.setPixel(i, 1);
    }
    for (int i = 120; i < 127; i++) {
      display.setPixel(i, 3);
    } 
    for (int i = 121; i < 126; i++) {
      display.setPixel(i, 5);
    }
    for (int i = 122; i < 125; i++) {
      display.setPixel(i, 7);
    }
    for (int i = 123; i < 124; i++) {
      display.setPixel(i, 9);
    }
}

void wifiConnected(){
    display.drawXbm(34, 12, 60, 36, WiFi_Logo_bits);
    display.display();
} 

void wifiDisconnected(){

}

String koinexCryptoCodes[8][3] = { 
  {"1_BTC","BTC_1","BTC"},
  {"1_ETH","ETH_1","ETH"},
  {"1_XRP","XRP_1","XRP"},
  {"1_BCH","BCH_1","BCH"},
  {"1_LTC","LTC_1","LTC"},
  {"1_MIOTA","MIOTA_1","MIOTA"},
  {"1_OMG","OMG_1","OMG"},
  {"1_GNT","GNT_1","GNT"}
};


//G!*k(sRe$sCRV1V%Udcw
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
 
    HTTPClient http;

 
    http.begin("http://monsoonal-semicondu.000webhostapp.com/koinex.php");  //Specify request destination 
    int httpCode = http.GET();  

    if (httpCode > 0) { //Check the returning code
 
      String responses = http.getString();
     // Serial.println(responses);
     
      responses.replace('"',' ');

      String prices = getByKey(responses,"prices");
      Serial.println(prices);

      String xrp_part = getByKey(prices,"XRP");

      int end = xrp_part.indexOf(",");
      String xrp = xrp_part.substring(1, end-1);
      xrp.replace(" ", "");

      display.clear();

      drawCircleDemo();

      if(isValidNumber(xrp)){
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.setFont(ArialMT_Plain_16);
        display.drawString(64, 5, "KOINEX"); 
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(64, 23, "XRP");
        display.drawString(64, 39, xrp);
      }else{
        display.drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        display.setFont(ArialMT_Plain_16);
        display.drawString(64, 10, "ERROR !");
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(64, 30, "Invalid Response");
        display.drawString(64, 43, "Refresh");
      }
      

      display.display();

    }else{

      display.clear();
      display.drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.setFont(ArialMT_Plain_16);
      display.drawString(64, 10, "Invalid req head");
      display.drawString(64, 30, "ERR KOINEX");
      display.display();

    }
    http.end();   //Close connection
  }else{
    display.clear();
    wifiConnected();
    lcd(64, 30,DONT_CLEAR,"Disconnected",10,'C'); 
    display.display();
  }
 
  delay(40000);    //Send a request every 30 seconds
 
}

 