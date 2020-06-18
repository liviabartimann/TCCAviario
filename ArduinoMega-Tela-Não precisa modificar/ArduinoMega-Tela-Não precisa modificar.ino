/*______Import Libraries_______*/
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
/*Serial Node*/
#include<SoftwareSerial.h>

/*Real time*/
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

 
/*ID de tela*/
int tela=0;

/*Coordenadas tela*/
int X,Y;



/*______Define LCD pins (I have asigned the default values)_______*/
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
/*_______End of defanitions______*/

/*______Assign names to colors and pressure_______*/
#define WHITE   0x0000 //Black->White
#define YELLOW    0x001F //Blue->Yellow
#define CYAN     0xF800 //Red->Cyan
#define PINK   0x07E0 //Green-> Pink
#define RED    0x07FF //Cyan -> Red
#define GREEN 0xF81F //Pink -> Green 
#define BLUE  0xFFE0 //Yellow->Blue
#define BLACK   0xFFFF //White-> Black
#define MINPRESSURE 10
#define MAXPRESSURE 1000
/*_______Assigned______*/

/*____Calibrate TFT LCD_____*/
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905

/*______End of Calibration______*/
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 is the sensitivity
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); //Start communication with LCD

/*________Define Fingerprint__________*/
SoftwareSerial SerialESP(53, 51);


void setup()
{
  /*Conf. Real time*/
  clock.begin();
 // clock.setDateTime(2020, 3, 19, 19, 36, 00);
  
  Serial.begin(9600);   //Use serial monitor for debugging	
  SerialESP.begin(4800);
  delay(2000);
  tft.reset();          //Always reset at start
  tft.begin(0x9341);    // My LCD uses LIL9341 Interface driver IC
  tft.setRotation(1);   // I just roated so that the power jack faces up - optional
  tft.fillScreen(WHITE);
  WelcomeScreen();  
  
  
}

void loop(){
  if(SerialESP.available()>0)
  {
	  String response = SerialESP.readString();
    Serial.println(response);
    atualizaValores(response);
  } 
}

void atualizaValores(String response){
  String id=response.substring(0,response.indexOf(";"));
  Serial.println("ID:"+id);
  response=response.substring(response.indexOf(";")+1,response.length());
  String T=response.substring(0,response.indexOf(";"));
  Serial.println("T:"+T);
  response=response.substring(response.indexOf(";")+1,response.length());
  String U=response.substring(0,response.indexOf(";"));
  Serial.println("U:"+U);
  response=response.substring(response.indexOf(";")+1,response.length());
  String P=response.substring(0,response.indexOf(";"));
  Serial.println("P:"+P);
  response=response.substring(response.indexOf(";")+1,response.length());
  String L=response.substring(0,response.indexOf(";"));
  Serial.println("L:"+L);
  response=response.substring(response.indexOf(";")+1,response.length());
  String G=response.substring(0,response.length());
  Serial.println("G:"+G);
  atualizaQuadrados(id.toInt(),T,U,P,G,L);
}
void WelcomeScreen()
{
  tela=1;
  tft.fillScreen(WHITE);
  tft.setCursor (0, 30);
  tft.setTextSize (2);
  tft.setTextColor(RED);
  tft.println("Iniciando sistema ...");
  tft.fillRect(0, 10, 50, 20, BLACK);
  delay(1000);
  tft.fillRect(0, 10, 100, 20, BLACK);
  delay(1000);
  tft.fillRect(0, 10, 280, 20, BLACK);
  delay(1000);
  tft.setCursor (0, 80);
  tft.setTextSize (5);
  tft.setTextColor(BLUE);
  tft.println("BEM VINDO!");
  tft.setTextSize (2);
  tft.println("Aviario - IFMS/NA");
  delay(2800);
	tela1();
}
void tela1()
{
    tft.fillScreen(BLACK);
    tft.setCursor (10, 0);
    tft.setTextSize (2);
    tft.setTextColor(WHITE);
    //tft.println("Modulos-HH:mm-dd/mm/aaaa");
    dt = clock.getDateTime();
    
    tft.println("Modulos:"+String(dt.day)+"/"+String(dt.month)+"/"+String(dt.year)+"-"+String(dt.hour)+":"+String(dt.minute));
    drawQuadrados();
    for(int i=1;i<=9;i++){
      atualizaQuadrados(i,"28.80","80","850","100","200");
    }
}
void atualizaQuadrados(int i, String T, String U,String P,String G,String L){
int x,y;
if(i==1){
  x=0;
  y=0;
}else if(i==2){
  x=1;
  y=0;
}else if(i==3){
  x=2;
  y=0;
}else if(i==4){
  x=0;
  y=1;
}else if(i==5){
  x=1;
  y=1;
}else if(i==6){
  x=2;
  y=1;
}else if(i==7){
  x=0;
  y=2;
}else if(i==8){
  x=1;
  y=2;
}else {
  x=2;
  y=2;
}
tft.setTextSize (1);
tft.fillRect(100*x+5, 67*y+39, 95, 60, WHITE);
for(int z=0;z<7;z++){
   tft.setCursor (100*x+6, 67*y+30+z*10);
   tft.setTextColor(PINK);
   if(z==1){tft.setTextColor(BLACK);tft.println("      ID:."+String(i)+".    ");}
     else if(z==2){tft.println("T:" + T + " c");}
     else if(z==3){tft.println("U:" + U + " %");}
     else if(z==4){tft.println("P:" + P + " kpa");}
     else if(z==5){tft.println("L:" + L + " ");}
     else if(z==6){tft.println("G:" + G + " ");}  
}
}
void drawQuadrados(){
  for (int x=0;x<3;x++)
  for (int y=0;y<3;y++)
  tft.fillRect(100*x+5, 67*y+39, 95, 60, WHITE);  
 }
