/*=======================================================================================
                                    Includes
========================================================================================*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

/*=======================================================================================
                                User Configurarations
========================================================================================*/
#define	_STANDBY_TIME_OUT	(300000)	//in mSeconds

const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 511;

/*=======================================================================================
                                    Definitions
========================================================================================*/
#define _ENCODER_EN

#define STANDBY 				0
#define MAIN_SCREEN 		1
#define MAIN_SCREEN_CNT 2
#define MENU_SCREEN 		3
#define SUB_MENU_1 			4
#define SUB_MENU_2 			5
#define BATTERY_LOW			6

/*=======================================================================================
                          Pin definitions and variables
========================================================================================*/
const int PinCLK	= 2; 	// Used for generating interrupts using CLK signal
const int PinDT		= 8;  // Used for reading DT signal
const int PinSW		= 6;  // Used for the push button switch

const int PinFootSwitch		= 7;
const int PinAutoPulse		= 3;

const int PinPulse				= 5;
const int PinLED					= 4;

const int PinBatVol				= A0;

/*=======================================================================================
                       OLED Display Configurarions and variables
========================================================================================*/
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 			0
#define YPOS 			1
#define DELTAY 		2

#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH  128 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


/*=======================================================================================
                                  Globle Variables
========================================================================================*/
long lastVirtualPosition = 0;
uint8_t selectedMenu = 0;
uint8_t State = MAIN_SCREEN;
uint8_t lastBatterVoltage = 0;
uint16_t lastWeldCount = 0, lastPulseDelay = 0;

uint8_t BatteryVoltage = 124;

typedef struct AllData{
	uint8_t delay;
	uint8_t batteryAlarm;
	uint16_t weldCount;
	uint16_t pulseDelay;
	uint8_t shortPulse;
	uint8_t autoPulse;

}allData;

allData gAllData;

uint8_t Delay 				= 20;
uint8_t BatteryAlarm 	= 110;
uint16_t WeldCount 		= 0;
uint16_t PulseDelay 	= 5;
uint8_t ShortPulse 		= 12;
uint8_t AutoPulse 		= 1;

long VirtualPosition = 0;
static unsigned long lastInterruptTime = 0;

unsigned long lastActiveTime;
unsigned long previousMillis = 0; 
unsigned long interval = 1000;    


/*=======================================================================================
                                   Setup function
========================================================================================*/
void setup()   {                
  Serial.begin(9600);

  pinMode(PinCLK,INPUT);
  pinMode(PinDT,INPUT);  
  
  pinMode(PinSW,INPUT_PULLUP);
  digitalWrite(PinSW,HIGH);
  
  attachInterrupt (0,isr,FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
	
	pinMode(PinLED,OUTPUT);
	pinMode(PinPulse,OUTPUT);
	
	pinMode(PinFootSwitch,INPUT_PULLUP);
	digitalWrite(PinFootSwitch,HIGH);
	
	pinMode(PinAutoPulse,INPUT);
	//digitalWrite(PinAutoPulse,LOW);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
  display.clearDisplay();
  display.display();	
	lastActiveTime = millis();
	lastVirtualPosition = VirtualPosition;
	
	
	
	gAllData.delay 				= 20;
	gAllData.batteryAlarm = 110;
	gAllData.weldCount 		= 0;
	gAllData.pulseDelay 	= 5;
	gAllData.shortPulse		= 12;
	gAllData.autoPulse		= 1;
	
	byte tmpArraEe[10],tmp2ArrEe[10];
	eeprom_read_bytes(0,tmpArraEe,8);
	
	if( memcmp(tmpArraEe,&gAllData,8) != 0){
		if( tmpArraEe[6] == 0xFF ){
			memcpy(tmp2ArrEe, &gAllData,8);
			eeprom_write_bytes(0,tmp2ArrEe,8);
		}
		else{	
			memcpy(&gAllData,tmpArraEe,8);
		}
	}
	eepromReset();
	
	//Serial.println(gAllData.delay);
	//Serial.println(gAllData.batteryAlarm);
	//Serial.println(gAllData.weldCount);
	//Serial.println(gAllData.pulseDelay);
	//Serial.println(gAllData.shortPulse);
	//Serial.println(gAllData.autoPulse);
	
	Delay					=		gAllData.delay 				;
	BatteryAlarm	=		gAllData.batteryAlarm ;
	WeldCount			=		gAllData.weldCount 		;
	PulseDelay		=		gAllData.pulseDelay 	;
	ShortPulse		=		gAllData.shortPulse		;
	AutoPulse			=		gAllData.autoPulse		;
	
}

/*=======================================================================================
                                            Loop
========================================================================================*/
void loop(){	
	StateMachine();
	CheckForSleep();
	CheckBatteryVoltage();
	updateEeprom();
	
	if(State==MAIN_SCREEN_CNT){

//------------------------Pulse activated with AutoPulse feature-------------------------
		if(digitalRead(PinAutoPulse) && (AutoPulse == 0)){
			//auto pulse activate			
      delay(Delay*100);
			sendPulse();
			  // Wait until switch has been released
        do {
        digitalWrite(PinPulse, LOW);
        } while (digitalRead(PinAutoPulse));
      // Delay before impulse can be triggered again
      delay(500);			
		}

//------------------------Pulse activated with Foot switch-------------------------------
		if(!digitalRead(PinFootSwitch)){
			//pulse activated;
     delay(200);
		 sendPulse();
        do {
        digitalWrite(PinPulse, LOW);
        }
			  while(!digitalRead(PinFootSwitch));
     // Delay before impulse can be triggered again
     delay(500);
		}
	}
}

/*=======================================================================================
                                         Functions
========================================================================================*/

void eepromReset(){
	if( encBtnState()==LOW ){
		byte tmpArraEe[10],tmp2ArrEe[10];		
			
		gAllData.delay 					= 20;
		gAllData.batteryAlarm 	= 110;
		gAllData.weldCount 			= gAllData.weldCount;
		gAllData.pulseDelay 		= 5;
		gAllData.shortPulse			= 12;
		gAllData.autoPulse			= 1;
			
		memcpy(tmp2ArrEe, &gAllData,8);
		eeprom_write_bytes(0,tmp2ArrEe,8);
		Serial.println("EEPROM reset");
		
		while(!encBtnState());
	}
}

void sendPulse(){
	//Serial.println("pulse activated");
	unsigned long shortPulseDelay = PulseDelay*ShortPulse/100;
	
	if(shortPulseDelay < 1) shortPulseDelay = 1; 	// so that the delay less than 1 millisecond will round off to 1ms.
	
	digitalWrite(PinPulse,HIGH);
	delay(shortPulseDelay);
	digitalWrite(PinPulse,LOW);
	delay(shortPulseDelay);
	
	digitalWrite(PinPulse,HIGH);
	delay(PulseDelay);
	digitalWrite(PinPulse,LOW);
  WeldCount++;
	lastActiveTime = millis();
}

void updateEeprom(){
	byte tmpArraEe[10],tmp2ArrEe[10];
	if( gAllData.delay != Delay || \
			gAllData.batteryAlarm != BatteryAlarm || \
			gAllData.weldCount != WeldCount || \
			gAllData.pulseDelay != PulseDelay ||\
			gAllData.shortPulse	!= ShortPulse || \
			gAllData.autoPulse	!= AutoPulse ){
		
		gAllData.delay 					= Delay;
		gAllData.batteryAlarm 	= BatteryAlarm;
		gAllData.weldCount 			= WeldCount;
		gAllData.pulseDelay 		= PulseDelay;
		gAllData.shortPulse			= ShortPulse;
		gAllData.autoPulse			= AutoPulse;
		
		memcpy(tmp2ArrEe, &gAllData,8);
		eeprom_write_bytes(0,tmp2ArrEe,8);
		//Serial.println("Updated eeprom");	
	}
}

void CheckBatteryVoltage(){
	static uint8_t LastState = MAIN_SCREEN; 
	uint16_t tmp = analogRead(PinBatVol);
	double tmp1 = tmp * 5 * 4.03 * 10 / 1023 + 6;
	uint8_t tmp2 = (uint8_t)tmp1;
   if (millis() - previousMillis > interval) {
    previousMillis = millis();   // aktuelle Zeit abspeichern
    BatteryVoltage = tmp2; 
   }
	
	
	if(BatteryAlarm > BatteryVoltage && State!=BATTERY_LOW){
		State = BATTERY_LOW;
		LastState = State;
		char tmpAr1[5] = {0,0,0,0,0};
		tmpAr1[0] = BatteryVoltage/100+ '0';	tmpAr1[1] = BatteryVoltage%100/10+ '0';	tmpAr1[2] = '.';	tmpAr1[3] = BatteryVoltage%100%10+ '0';
		lowBatterry(tmpAr1);
	}
	
	if(BatteryAlarm <= BatteryVoltage && State==BATTERY_LOW){
		State = LastState;
	}
}

void CheckForSleep(){
	/*
	if(lastActiveTime + 1000 < millis() ){
		inactiveTime += millis() - lastActiveTime;
		lastActiveTime = millis();
		//Serial.println(inactiveTime);
	
		if(inactiveTime > _STANDBY_TIME_OUT){//(1000*60*_STANDBY_TIME_OUT)){			
			//Serial.println("Enter Standby Mode");
			inactiveTime = 0;
		}
	}		
	*/
	if(lastActiveTime + _STANDBY_TIME_OUT < millis() ){
		if(State!=BATTERY_LOW){
			State = STANDBY;
			standByMsg();
		}
	}	
}

/*-----------------------------------State Machine--------------------------------------*/
void StateMachine(){
	char tmpAr1[5];
	char tmpAr2[5];
	char tmpAr3[5];
	static uint8_t selectedMenu = 0;
	static uint8_t selectedMainMenu = 0;
	static uint8_t selectedSubMenu = 0;
	
	switch(State){
		case STANDBY:
				if( encBtnState()==LOW ){
					State = MAIN_SCREEN;
					delay(30);
					//set all the functionalities anable;
					while(!encBtnState());
				}
			break;
			
		case BATTERY_LOW:
			
		break;
		
		case MAIN_SCREEN:
			State = MAIN_SCREEN_CNT;
			selectedMenu = 0;
			memset(tmpAr1,0,5);
			memset(tmpAr2,0,5);
			memset(tmpAr3,0,5);
			
			tmpAr1[0] = BatteryVoltage/100+ '0';	tmpAr1[1] = BatteryVoltage%100/10+ '0';	tmpAr1[2] = '.';												tmpAr1[3] = BatteryVoltage%100%10+ '0';
			tmpAr2[0] = WeldCount/1000+ '0';			tmpAr2[1] = WeldCount%1000/100+ '0';		tmpAr2[2] = WeldCount%1000%100/10+ '0';	tmpAr2[3] = WeldCount%1000%100%10+ '0';
			tmpAr3[0] = PulseDelay/1000+ '0';			tmpAr3[1] = PulseDelay%1000/100+ '0';		tmpAr3[2] = PulseDelay%1000%100/10+ '0';	tmpAr3[3] = PulseDelay%1000%100%10+ '0';
			
			mainScreen(tmpAr3,tmpAr1,tmpAr2);
			
			break;
		
		case MAIN_SCREEN_CNT:
			if( encBtnState()==LOW ){
				State = MENU_SCREEN;	
				selectedMenu = 0;			
				displayMainMenu(0);
				delay(30);
				//set all the functionalities anable;
				while(!encBtnState());
				break;
			}
			
			if( lastVirtualPosition != VirtualPosition ){			
				if( lastVirtualPosition > VirtualPosition ){
					PulseDelay--;					
				}
				else{		
					PulseDelay++;
				}
				if( PulseDelay <= 1 ) PulseDelay = 1;	
				else if( PulseDelay >= 999)	PulseDelay = 999;	
				
				//PulseDelay = selectedMenu;
				lastVirtualPosition = VirtualPosition;					
			}								
				
			if(lastBatterVoltage!=BatteryVoltage || lastWeldCount != WeldCount || lastPulseDelay != PulseDelay){
				memset(tmpAr1,0,5);
				memset(tmpAr2,0,5);
				memset(tmpAr3,0,5);
				
				tmpAr1[0] = BatteryVoltage/100+ '0';	tmpAr1[1] = BatteryVoltage%100/10+ '0';	tmpAr1[2] = '.';												tmpAr1[3] = BatteryVoltage%100%10+ '0';
				tmpAr2[0] = WeldCount/1000+ '0';			tmpAr2[1] = WeldCount%1000/100+ '0';		tmpAr2[2] = WeldCount%1000%100/10+ '0';	tmpAr2[3] = WeldCount%1000%100%10+ '0';
				tmpAr3[0] = PulseDelay/1000+ '0';			tmpAr3[1] = PulseDelay%1000/100+ '0';		tmpAr3[2] = PulseDelay%1000%100/10+ '0';	tmpAr3[3] = PulseDelay%1000%100%10+ '0';
				
				mainScreen(tmpAr3,tmpAr1,tmpAr2);
				
				lastBatterVoltage=BatteryVoltage;
				lastWeldCount = WeldCount;
				lastPulseDelay = PulseDelay;
				
			}
			
			//other functions
			break;
		
		case MENU_SCREEN:		
			if( encBtnState()==LOW ){
				delay(30);
				State = SUB_MENU_1;
				selectedMainMenu = selectedMenu;
				if(selectedMainMenu == 0){
					displaySubMenuType1(selectedMenu);
				}
				else if(selectedMainMenu == 1){
					uint8_t value = BatteryAlarm;		
					memset(tmpAr1,0,5);				
					tmpAr1[0] = value/100+'0';
					tmpAr1[1] = value%100/10+'0';
					tmpAr1[2] = '.';
					tmpAr1[3] = value%100%10+'0';
					displaySubMenuType2("Battery Alarm: ", tmpAr1 , "voltage");
				}
				else if(selectedMainMenu == 2){
					uint8_t value = ShortPulse;
					memset(tmpAr1,0,5);	
					tmpAr1[0] = value/100+'0';
					tmpAr1[1] = value%100/10+'0';
					tmpAr1[2] = value%100%10+'0';
					displaySubMenuType2("Short Pulse: ", tmpAr1 , "% of pulse time");		
				}
				selectedMenu = 0;
				//set all the functionalities anable;
				while(!encBtnState());	
				break;
			}
			
			if( lastVirtualPosition != VirtualPosition ){		
				if( lastVirtualPosition > VirtualPosition ){
					selectedMenu--;
				}
				else{		
					selectedMenu++;
				}
				if( selectedMenu >= 250){
					selectedMenu = 0;
				}
				else if( selectedMenu >= 2){
					selectedMenu = 2;
				}
				
				lastVirtualPosition = VirtualPosition;
				displayMainMenu(selectedMenu);
			}		
			break;
		
		case SUB_MENU_1:
			if( encBtnState()==LOW ){
				delay(30);
				//set all the functionalities anable;
				if(selectedMainMenu==0){
					State = SUB_MENU_2;
					selectedSubMenu = selectedMenu;
					
					if(selectedSubMenu==0){
						if(AutoPulse == 0){
							displaySubMenuType2("Auto Pulse: On/Off", "ON" , " ");
							AutoPulse = 1;
						}
						else if(AutoPulse == 1){
							displaySubMenuType2("Auto Pulse: On/Off", "OFF" , " ");
							AutoPulse = 0;
						}
					}
					else if(selectedSubMenu==1){
						uint8_t value = Delay;
						memset(tmpAr1,0,5);				
						tmpAr1[0] = value/10+'0';
						tmpAr1[1] = '.';
						tmpAr1[2] = value%10+'0';
						displaySubMenuType2("Auto Pulse: Delay", tmpAr1 , "seconds");
					}
					else{
					
					}
					selectedMenu = 0;
				}
				else if(selectedMainMenu == 1){					
					State = MAIN_SCREEN;
					selectedMenu = 0; 
				}
				else if(selectedMainMenu == 2){					
					State = MAIN_SCREEN;
					selectedMenu = 0;
				}
				else{			
					State = MAIN_SCREEN;
					selectedMenu = 0;
				}
				while(!encBtnState());	
				selectedMenu = 0;
				break;
			}
			
			if(selectedMainMenu==0){
				if( lastVirtualPosition != VirtualPosition ){		
					if( lastVirtualPosition > VirtualPosition ){
						selectedMenu--;
					}
					else{		
						selectedMenu++;
					}
					
					if( selectedMenu >= 3){
						selectedMenu = 2;
					}
					
					lastVirtualPosition = VirtualPosition;
					displaySubMenuType1(selectedMenu);
				}					
			}
			else if(selectedMainMenu == 1){
				
				if( lastVirtualPosition != VirtualPosition ){						
					
					if( lastVirtualPosition > VirtualPosition ){
						BatteryAlarm--;
						
					}
					else{		
						BatteryAlarm++;
					}
					if( BatteryAlarm <= 100 ) BatteryAlarm = 100;	
					else if( BatteryAlarm >= 200)	BatteryAlarm = 200;					
					
					lastVirtualPosition = VirtualPosition;	
					
					uint8_t value = BatteryAlarm;			
					memset(tmpAr1,0,5);				
					tmpAr1[0] = value/100+'0';
					tmpAr1[1] = value%100/10+'0';
					tmpAr1[2] = '.';
					tmpAr1[3] = value%100%10+'0';
					displaySubMenuType2("Battery Alarm: ", tmpAr1 , "voltage");				
				}								
			}
			else if(selectedMainMenu == 2){
				if( lastVirtualPosition != VirtualPosition ){					
					
					if( lastVirtualPosition > VirtualPosition ){
						ShortPulse--;
					}
					else{		
						ShortPulse++;
					}
					if( ShortPulse <= 1 ) ShortPulse = 1;
					else if( ShortPulse >= 100)	ShortPulse = 100;									
					
					lastVirtualPosition = VirtualPosition;	
					uint8_t value = ShortPulse;
					memset(tmpAr1,0,5);	
					tmpAr1[0] = value/100+'0';
					tmpAr1[1] = value%100/10+'0';
					tmpAr1[2] = value%100%10+'0';
					displaySubMenuType2("Short Pulse: ", tmpAr1 , "% of pulse time");					
				}								
			}
			else{
			}
			
			break;
			
		case SUB_MENU_2:			
			if( encBtnState()==LOW ){
				delay(30);
				//set all the functionalities anable;
				State = MAIN_SCREEN;
				while(!encBtnState());	
				selectedMenu = 0;
				break;
			}
			
			if(selectedSubMenu==0){
				if( lastVirtualPosition != VirtualPosition ){
					
					
					if( lastVirtualPosition > VirtualPosition ){
						AutoPulse--;
					}
					else{		
						AutoPulse++;
					}
					if( AutoPulse <= 0 ) AutoPulse = 0;
					else if( AutoPulse >= 1)	AutoPulse = 1;

					
					lastVirtualPosition = VirtualPosition;
					if(AutoPulse == 0){
						displaySubMenuType2("Auto Pulse: On/Off", "ON" , " ");
					}
					else if(AutoPulse == 1){
						displaySubMenuType2("Auto Pulse: On/Off", "OFF" , " ");
					}	
				}
			}
			else if(selectedSubMenu==1){
				if( lastVirtualPosition != VirtualPosition ){					
					
					if( lastVirtualPosition > VirtualPosition ){
						Delay--;
					}
					else{		
						Delay++;
					}
					if( Delay >= 50)	Delay = 50;
					else if( Delay <= 5 ) Delay = 5;

					
					lastVirtualPosition = VirtualPosition;
					
					uint8_t value = Delay;
					memset(tmpAr1,0,5);				
					tmpAr1[0] = value/10+'0';
					tmpAr1[1] = '.';
					tmpAr1[2] = value%10+'0';
					displaySubMenuType2("Auto Pulse: Delay", tmpAr1 , "seconds");
				}
			}
			else{
			
			}	
			
			break;
			
		default:
			break;
	}
}

bool encBtnState(){	
	if(!digitalRead(PinSW)){
		lastActiveTime = millis();
	}
	return (digitalRead(PinSW));
}


/*--------------------------------------- isr ------------------------------------------*/
void isr(){                    
	unsigned long interruptTime = millis();
	if (interruptTime - lastInterruptTime > 20){
	/*
		if (digitalRead(PinCLK)){
			if(digitalRead(PinDT)){			
			}
			else{
				VirtualPosition++;		
			}
		}
		else{
			if(digitalRead(PinDT)){
				VirtualPosition--;
			}
		} 
		*/
		if(digitalRead(PinDT)){
			VirtualPosition--;
		}
		else{
			VirtualPosition++;		
		}
		lastInterruptTime = interruptTime;
		lastActiveTime = interruptTime;
	}
}

/*--------------------------------- Display Functions ----------------------------------*/
void displayMainMenu(uint8_t SelectedItem){
	uint8_t _GAP = 4;
  display.clearDisplay();
  display.setCursor(1,_GAP);
	display.setTextSize(2);
	
  display.setTextColor(WHITE);
  if(SelectedItem == 0) display.setTextColor(BLACK, WHITE);
  display.println("Auto Pulse");
	
  display.setCursor(1,(2*_GAP+16));
  display.setTextColor(WHITE);
  if(SelectedItem == 1) display.setTextColor(BLACK, WHITE);
  display.println("Btry Alarm");
	
  display.setCursor(1,(3*_GAP + 2*16));
  display.setTextColor(WHITE);
  if(SelectedItem == 2) display.setTextColor(BLACK, WHITE);
  display.println("Shrt Pulse");
	
  display.display();	
}

void displaySubMenuType1( uint8_t SelectedItem ){
	uint8_t _GAP = 4;
  display.clearDisplay();
	
  display.setCursor(1,_GAP);
	display.setTextSize(1);	
  display.setTextColor(WHITE);
  display.println("Auto Pulse:");
	
	display.setTextSize(2);	
  display.setCursor(1,(2*_GAP+16 - 8));
  display.setTextColor(WHITE);
  if(SelectedItem == 0) display.setTextColor(BLACK, WHITE);
  display.println("ON/OFF");
	
	display.setTextSize(2);	
  display.setCursor(1,(3*_GAP + 2*16 - 8));
  display.setTextColor(WHITE);
  if(SelectedItem == 1) display.setTextColor(BLACK, WHITE);
  display.println("Delay");
	
	display.setTextSize(1);		
  display.setCursor(1,(4*_GAP + 3*16 - 8));
  display.setTextColor(WHITE);
  if(SelectedItem == 2) display.setTextColor(BLACK, WHITE);
  display.println("Exit");
	
  display.display();	
}

void displaySubMenuType2( const char * menuName, const char *value, const char * units){
	uint8_t _GAP = 4;
  display.clearDisplay();
	
  display.setCursor(1,_GAP);
	display.setTextSize(1);	
  display.setTextColor(WHITE);
  display.println(menuName);
	
	display.setTextSize(2);	
  display.setCursor(1,(3*_GAP + 16 - 8));
  display.setTextColor(WHITE);
  display.println(value);
	
	display.setTextSize(1);	
  display.setCursor(1,(4*_GAP + 2*16 - 8));
  display.setTextColor(WHITE);
  display.println(units);	
	
  display.display();	
}

void mainScreen( const char * pulseTime, const char * batteryV, const char * totalWelds){
	uint8_t _GAP = 5;
  display.clearDisplay();
	
  display.setCursor(1,_GAP);
	display.setTextSize(2);	
  display.setTextColor(WHITE);
  display.print("  ");
  display.print(pulseTime);
  display.println(" ms");
	
	display.setTextSize(1);	
  display.setCursor(1,(3*_GAP + 16));
  display.setTextColor(WHITE);
  display.println("Battery:");
	
	display.setTextSize(1);	
  display.setCursor(64,(3*_GAP + 16));
  display.setTextColor(WHITE);
  display.println("Tot Welds:");
	
	display.setTextSize(1);	
  display.setCursor(1,(4*_GAP + 2*16 - 8));
  display.setTextColor(WHITE);
  display.println(batteryV);
	
	display.setTextSize(1);	
  display.setCursor(64,(4*_GAP + 2*16 - 8));
  display.setTextColor(WHITE);
  display.println(totalWelds);	
	
	display.setTextSize(1);	
  display.setCursor(96,(5*_GAP + 1*16 + 2*8));
  display.setTextColor(WHITE);
  if(AutoPulse==0) display.print("AUTO");
	else display.print("MANU");
  display.display();	
}

void lowBatterry( const char * batteryV ){
	uint8_t _GAP = 2;
  display.clearDisplay();
	
  display.setCursor(1,_GAP);
	display.setTextSize(2);	
  display.setTextColor(WHITE);
  display.println("   LOW   ");
	
  display.setCursor(1,(2*_GAP + 16));
  display.println(" BATTERY ");
	
	display.setTextSize(2);	
  display.setCursor(1,(3*_GAP + 2*16));
  display.print("  ");
  display.print(batteryV);		
  display.println("V");	
	
  display.display();	
}

void standByMsg(){
	uint8_t _GAP = 5;
  display.clearDisplay();
	
  display.setTextColor(WHITE);
	display.setTextSize(2);	
  display.setCursor(1,2*_GAP);
  display.println(" STANDBY  ");
	display.setTextSize(1);	
  display.setCursor(1,5*_GAP + 16);	
  display.println("Please click button");	
	
  display.display();	
}


/*--------------------------------- Utility Functions ----------------------------------*/

//
// Writes a sequence of bytes to eeprom starting at the specified address.
// Returns true if the whole array is successfully written.
// Returns false if the start or end addresses aren't between
// the minimum and maximum allowed values.
// When returning false, nothing gets written to eeprom.
//
boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
  // counter
  int i;

  // both first byte and last byte addresses must fall within
  // the allowed range  
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
    return false;
  }

  for (i = 0; i < numBytes; i++) {
    EEPROM.write(startAddr + i, array[i]);
  }

  return true;
}

//
// Reads the specified number of bytes from the specified address into the provided buffer.
// Returns true if all the bytes are successfully read.
// Returns false if the star or end addresses aren't between
// the minimum and maximum allowed values.
// When returning false, the provided array is untouched.
//
// Note: the caller must ensure that array[] has enough space
// to store at most numBytes bytes.
//
boolean eeprom_read_bytes(int startAddr, byte array[], int numBytes) {
  int i;

  // both first byte and last byte addresses must fall within
  // the allowed range  
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
    return false;
  }

  for (i = 0; i < numBytes; i++) {
    array[i] = EEPROM.read(startAddr + i);
  }

  return true;
}

//
// Returns true if the address is between the
// minimum and maximum allowed values,
// false otherwise.
//
// This function is used by the other, higher-level functions
// to prevent bugs and runtime errors due to invalid addresses.
//
boolean eeprom_is_addr_ok(int addr) {
  return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}
