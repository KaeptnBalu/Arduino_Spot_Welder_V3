#ifndef _ARDUINO_SPOT_WELDER_V3_H
#define _ARDUINO_SPOT_WELDER_V3_H
/***********************************************************************************************//**
 *  \par        Arduino Spot Welder - Header.
 *
 *  \par        Details
 *  \par
 *              Arduino Spot Welder V3 firmware.
 *              This is the Arduino Code for the Spot Welder V3. Do not use it with the older V2 
 *              pcbs. It is not compatible with these.
 *  \par
 *              You need to have the Ardafruit_GFX library and the Ardafruit_SSD1306 library 
 *              installed in your Arduino IDE to sucessfully compile the Code.
 *              
 *              This release has been tested with the following library versions:    
 *              Adafruit SSD1306 V1.2.9
 *              Adafruit GFX V1.5.3            
 *
 *  \file       Arduino_Spot_Welder_V3_3_3.h
 *  \author     Marc Schönfleisch <http://malectrics.eu/>
 *  \version    3.3.3
 *  \date       September 2019
 *  \copyright  Copyright(c)2019 Marc Schönfleisch <info@malectrics.eu>. All right reserved.
 *
 *  \par        Changelog
 *  \li         01jul2017  MS  Initial release
 *  \li         12dec2017  JFF New release with major rewrite
 *  \li         15djan2018  MS change battery voltage reading for V3.2 Spot Welder 
 *  \li         05djun2018  MS remove softwarereset to eliminate need of optiboot bootloader 
 *  \li         11aug2018  MS fix 10.000 welds counter bug
 *  \li         24nov2018  AJ improve Auto Pulse functionality with progress bar
 *  \li         09apr2019  MS add foot switch wrong connection error message
 *  \li         05jun2019  MS code update for SSD1306 library V1.2.9 and general improvements
 *  \li         12sep2019  GW imporove slow progress bar drawing problem
 *
 *  \par        License
 *              This program is free software: you can redistribute it and/or modify it under the
 *              terms of the GNU General Public License as published by the Free Software 
 *              Foundation, either version 3 of the License, or (at your option) any later version.
 *  \par
 *              This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 *              WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 *              PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *  \par
 *              You should have received a copy of the GNU General Public License along with this 
 *              program.  If not, see <http://www.gnu.org/licenses/> or write to the Free Software 
 *              Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 *//***********************************************************************************************/

// General macros
#define str(s)              #s
#define xstr(s)             str(s)

// Most of these macros define strings that appear on the splash screen 
// (each line of the splash screen is limited to 21 characters)
#define _DEVICENAME_        "Arduino Spot Welder"
#define _PROGNAME_          "Arduino Spot Welder Control Firmware"
#define _AUTHOR_            "Marc Schonfleisch"
#define _VERSION_MAJOR_     3
#define _VERSION_MINOR_     3
#define _REVISION_          3
#define _COPYRIGHT_         "2019"
#define _COMPANY_           "Malectrics"
#define _RIGHTS_            "All right reserved"

/***************************************************************************************************
* User Configuration                                                                               *
***************************************************************************************************/

//#define _DEVELOPMENT_                       /**< Allows printing of diagnostics */
//#define _BOOTSYS_                           /**< Force boot to system menu for testing */

#define _LANG_EN_                           /**< Language:  _LANG_EN/DE/FR/ES/IT_ */
//#define _TESTING_                           /**< Allows ignoring the low battery alarm */
#define _SERIAL_BAUD_       115200          /**< Comms rate for serial debugging */

/***************************************************************************************************
* Pin and interrupt definitions                                                                    *
***************************************************************************************************/

#define ENC_INT             0               /**< Rotary interrupt for CLK input (Ph0) */
#define PIN_CLK             2               /**< Rotary encoder CLK input (Ph0) */
#define PIN_DT              8               /**< Rotary encoder DT input (Ph1) */
#define PIN_SW              6               /**< Rotary encoder push button switch input */
#define PIN_FOOT_SWITCH     7               /**< Foot switch sense input */
#define PIN_AUTO_PULSE      3               /**< Auto-pulse sense input */
#define PIN_PULSE           5               /**< Weld pulse output */
#define PIN_LED             4               /**< Status LED output */
#define PIN_BATT_V          A0              /**< A/D input for battery voltage sense */

/***************************************************************************************************
* Macros                                                                                           *
***************************************************************************************************/
// Defaults for operational variables
#define DEF_AUTO_PLSDELAY   20              /**< Default auto pulse delay time (ms*100) */ 
#define DEF_PULSE_TIME      5               /**< Default pulse time (ms) */ 
#define DEF_MAX_PULSE_TIME  100             /**< Default maximum pulse time (ms) */ 
#define DEF_SPULSE_TIME     12              /**< Default short pulse time (% of pulse time) */ 
#define DEF_NOM_BATT_V      124             /**< Default nominal battery voltage (for testing) */
#define DEF_MAX_BATT_V      127             /**< Default maximum battery voltage (V*10) */
#define DEF_PULSE_VOLTAGE   40              /**< Default voltage during pulse (for testing) (V*10) */
#define DEF_PULSE_AMPS      5000            /**< Default Amps during pulse (for testing) (A*10) */
#define DEF_BATTERY_OFFSET  0               /**< Default battery calibration offset (V*10) */
#define DEF_BATT_ALARM      110             /**< Default low battery voltage (V*10) */
#define DEF_AUTO_PULSE      true            /**< Default Auto-pulse enable */ 
#define DEF_OLED_INVERT     false           /**< Default OLED orientation */ 

// Limits for operational variables
#define MIN_PULSE_TIME      1               /**< Minimum weld pulse time */
#define MAX_PULSE_TIME      500             /**< Absolute maximum weld pulse time */
#define MAX_APULSE_DELAY    50              /**< Maximum auto pulse delay */
#define MIN_APULSE_DELAY    5               /**< Minimum auto pulse delay */
#define MAX_SPULSE_TIME     100             /**< Maximum short pulse time */
#define MIN_SPULSE_TIME     0               /**< Minimum short pulse time */
#define MAX_BATT_ALARM      120             /**< Maximum low battery alarm voltage */
#define MIN_BATT_BALARM     74             /**< Minimum low battery alarm voltage */
#define MAX_BATT_V          200             /**< Absolute maximum battery voltage */
#define MIN_BATT_V          50              /**< Absolute minimum battery voltage */

// Timing macros
#define STANDBY_TIME_OUT    300000L         /**< Device sleep timeout (ms) */ 
#define EEPROM_UPDATE_T     5000            /**< EEPROM update time (ms) */
#define WP_RETRIGGER_DELAY  500             /**< Weld pulse re-trigger delay (ms) */
#define FS_TRIGGER_DELAY    200             /**< Foot switch activation delay (ms) */
#define RS_DEBOUNCE         50  /*20*/      /**< Rotary encoder & switch debounce time (ms) */
#define BV_INTERVAL         20000            /**< Battery voltage measurement interval (ms) */
#define PV_DELAY            2000            /**< Time the foot switch has to be hold before the pulse data is shown after a pulse (ms) */

// Display screen layout
#define CHR_W               6               /**< Width of character [size=1] (pixels) */   
#define CHR_H               8               /**< Height of character [size=1] (pixels) */   
#define LINE_H              (CHR_H+2)       /**< Height of line [size=1] (pixels) */   

// Macros to define logical states
#define DD_READ             true            /**< Data transfer direction - read */
#define DD_WRITE            false           /**< Data transfer direction - write */
#define P_ON                true            /**< General macro for ON state */
#define P_OFF               false           /**< General macro for OFF state */
#define B_DN                true            /**< General macro for DOWN state */
#define B_UP                false           /**< General macro for UP state */
#define PL_ACTIVE_H         false           /**< Pin logic macro for Active High */
#define PL_ACTIVE_L         true            /**< Pin logic macro for Active Low */

// EEPROM macros
#define EEA_ID              0               /**< Address of unique ID */
#define EEA_PDATA           (EEA_ID+4)      /**< Eeprom address of program data */
#define EE_UNIQUEID         0x18fae9c8      /**< Unique Eeprom verification ID */
#define EE_FULL_RESET       true            /**< Reset parameter to reset all Eeprom parameters */

// Macros masquerading as functions - makes the code more readable
/** This macro reads the state of the pushbutton switch on the encoder. */
#define btnState()          (!digitalRead(PIN_SW))

/** This macro drives the welding pulse. */
#define weldPulse(state)    digitalWrite(PIN_PULSE,state?HIGH:LOW)

/** Where has this macro gone?? It was in WString.h */
#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))               

/***************************************************************************************************
* OLED Display Configuration                                                                       *
***************************************************************************************************/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET          4               /**< OLED mode */
#define OLED_INVERT         2               /**< OLED defined orientation mode - check OLED doc'n */
#define SPLASHTIME          2500            /**< Splash screen time (ms) */


/***************************************************************************************************
* Structure, union, and enumerated type definitions                                                *
***************************************************************************************************/

typedef  enum {                             /**< Type enumerations for format of variables */
         VF_BATTALM,                        /**< Battery alarm voltage */
         VF_BATTV,                          /**< Battery voltage */
         VF_BATTA,                          /**< Battery Amps */
         VF_WELDCNT,                        /**< Weld count */
         VF_PLSDLY,                         /**< Pulse delay */
         VF_SHTPLS,                         /**< Short pulse duration */
         VF_DELAY                           /**< Delay */
} vf_Type;

typedef  struct   progData {                /**< Program operating data structure */
         uint8_t  autoPulseDelay;           /**< Auto-pulse delay (ms/100) */ 
         uint8_t  batteryAlarm;             /**< Low battery voltage (A/D count) */
         uint16_t weldCount;                /**< Count of welds performed */
         uint16_t pulseTime;                /**< Pulse time (ms) */ 
         uint16_t maxPulseTime;             /**< Maximum allowed pulse time (ms) */ 
         uint8_t  shortPulseTime;           /**< Short pulse time (% of pulse time) */ 
         int8_t   batteryOffset;            /**< Battery voltage calibration offset (signed) x10 */
         uint16_t  PulseBatteryVoltage;     /**< Battery voltage during pulse x10 */
         uint16_t  PulseAmps;               /**< esimated Amps during pulse x10 */  
         struct progFlags {                 /**< Program logical flags */
             unsigned en_autoPulse:  1;     /**< Auto-pulse enable */ 
             unsigned en_oledInvert: 1;     /**< OLED orientation - true for inverted else normal */
             unsigned unused:        6;     /**< Unused program flags */ 
         } pFlags;
} progData;

/***************************************************************************************************
* Procedure prototypes                                                                             *
***************************************************************************************************/

void     stateMachine();

void     resetEeprom(boolean = false);
void     loadEeprom();
void     updateEeprom();

void     checkForLowVoltageEvent();
void     checkForSleepEvent();
void     checkForBtnEvent();
void     isr();
void     splash();
void     sendWeldPulse(uint8_t, uint16_t, uint16_t, boolean = PL_ACTIVE_H);  
void     message(const __FlashStringHelper*, const __FlashStringHelper*,
                 const __FlashStringHelper*, uint8_t = 0);
void     displayMenuType1(const __FlashStringHelper*, const __FlashStringHelper*,
                          const __FlashStringHelper*, const __FlashStringHelper*, 
                          uint8_t SelectedItem);
void     displayMenuType2(const __FlashStringHelper*, const char*, const __FlashStringHelper*);
void     displayMainScreen();
void     displayLowBattery();
void     drawStatusLine();
void     setTextProp(uint8_t, uint8_t, uint8_t, uint16_t = WHITE, boolean = false);
char*    valStr(char*, uint16_t, vf_Type);

/***************************************************************************************************
* Language strings (very simple language implementation - English is the default)                  *
***************************************************************************************************/

// Copy the language strings from the else clause into your language specific clause, then alter
// the strings to suit your language. Define your language at the top of this header file. It is
// important to maintain the correct formatting of the strings. Each string has an inline comment
// defining its format.

// Comment legend: field width          21 for small font, 10 for large font
//                 justification        left, centre, right
//                 padded               spaces both ends to fill field

#ifdef _LANG_DE_
          
#elif defined _LANG_FR_

#elif defined _LANG_ES_

#elif defined _LANG_IT_

#else
//                                           0123456789               // large font
//                                           012345678901234567890    // small font

static const char LS_APULSE[]     PROGMEM = "Auto Pulse";             // 10 char, centre, padded
static const char LS_BATTALM1[]   PROGMEM = "Batt Alarm";             // 10 char, centre, padded
static const char LS_SHORTPLS1[]  PROGMEM = "Shrt Pulse";             // 10 char, centre, padded

static const char LS_MANAUTO[]    PROGMEM = " Activate ";             // 10 char, centre, padded
static const char LS_DELAY[]      PROGMEM = "  Delay   ";             // 10 char, centre, padded
static const char LS_EXIT[]       PROGMEM = "  Exit    ";             // 10 char, centre, padded

static const char LS_STANDBY[]    PROGMEM = "  STANDBY ";             // 10 char, centre, padded
static const char LS_CLICKBTN[]   PROGMEM = " Please Click Button";   // 21 char, left
static const char LS_EXITSTBY[]   PROGMEM = "   to Exit Standby";     // 21 char, left

static const char LS_BATTALM[]    PROGMEM = "Battery Alarm";          // 21 char, left
static const char LS_BATTERY[]    PROGMEM = "BATTERY";                // 10 char, left
static const char LS_LOWV[]       PROGMEM = "LOW VOLTS";              // 10 char, left
static const char LS_PULSEV[]     PROGMEM = "VOLTS DURING PULSE";     // 21 char, left
static const char LS_PULSEA[]     PROGMEM = "EST. AMPS";              // 21 char, left

static const char LS_AUTOPLSON[]  PROGMEM = "Auto Pulse Setting";     // 21 char, left
static const char LS_AUTO[]       PROGMEM = "ON";              // 10 char, left
static const char LS_MANUAL[]     PROGMEM = "OFF";            // 10 char, left
static const char LS_AUTO_BAR[]   PROGMEM = "Auto";                   // 10 char, left
static const char LS_MANUAL_BAR[] PROGMEM = "Manual";                 // 10 char, left

static const char LS_AUTOPLSDLY[] PROGMEM = "Auto Pulse Delay";       // 21 char, left
static const char LS_SHORTPLS[]   PROGMEM = "Short Pulse";            // 21 char, left
static const char LS_WPDRN[]      PROGMEM = "Weld Pulse Duration";    // 21 char, left

static const char LS_BATTMSG[]    PROGMEM = " Battery";               // 10 char, centre
static const char LS_MAXPMSG[]    PROGMEM = "   Duration Set";        // 21 char, centre

static const char LS_PCOF[]       PROGMEM = "% of Pulse Time";        // 21 char, left
static const char LS_SECONDS[]    PROGMEM = "Seconds";                // 21 char, left
static const char LS_VOLTAGE[]    PROGMEM = "Volts";                  // 21 char, left
static const char LS_MS[]         PROGMEM = "ms";                     // 2  char, left
static const char LS_VUNITS[]     PROGMEM = "V";                      // 1  char, left
static const char LS_AUNITS[]     PROGMEM = "A";                      // 1  char, left
static const char LS_WELDS[]      PROGMEM = "W";                      // 1  char, left


static const char LS_REBOOTFR[]   PROGMEM = "   with Full Reset";     // 21 char, centre
static const char LS_REBOOTNR[]   PROGMEM = "   without Reset";       // 21 char, centre
static const char LS_REBOOTSR[]   PROGMEM = "   with Safe Reset";     // 21 char, centre
static const char LS_RECALMSG[]   PROGMEM = "   re-calibrated";       // 21 char, centre
static const char LS_WAITMSG[]    PROGMEM = " PLEASE REMOVE POWER";        // 21 char, centre

static const char LS_SYSMENU[]    PROGMEM = "System Menu";            // 21 char, left
static const char LS_SETTINGS[]   PROGMEM = " Settings ";             // 10 char, centre, padded
static const char LS_DISPLAY[]    PROGMEM = "  Display ";             // 10 char, centre, padded
static const char LS_BOOT[]       PROGMEM = "   Boot   ";             // 10 char, centre, padded

static const char LS_SETTMENU[]   PROGMEM = "System Settings";        // 21 char, left
static const char LS_MAXPULSE[]   PROGMEM = "Max Pulse ";             // 10 char, centre, padded
static const char LS_BATTCAL[]    PROGMEM = " Batt Cal ";             // 10 char, centre, padded

static const char LS_BOOTMENU[]   PROGMEM = "Reboot Spot Welder";     // 21 char, left
static const char LS_REBOOT[]     PROGMEM = "  Reboot  ";             // 10 char, centre, padded  
static const char LS_SAFERST[]    PROGMEM = "Safe Reset";             // 10 char, centre, padded
static const char LS_FULLRST[]    PROGMEM = "Full Reset";             // 10 char, centre, padded

static const char LS_INVERTMENU[] PROGMEM = "Screen Orientation";     // 21 char, left
static const char LS_SCRNORM[]    PROGMEM = "NORMAL";                 // 10 char, left
static const char LS_SCRINV[]     PROGMEM = "INVERTED";               // 10 char, left

static const char LS_MAXPLSMENU[] PROGMEM = "Set Max Weld Pulse";     // 21 char, left

static const char LS_BATCALMENU[] PROGMEM = "Calibrate Battery";      // 21 char, left
static const char LS_BATCALMSG[]  PROGMEM = "Set Measured Volts";     // 21 char, left
static const char LS_MSGHDR[]     PROGMEM = "System Message";         // 21 char, left

#endif            

#endif // _ARDUINO_SPOT_WELDER_V3_H

// EOF Arduino_Spot_Welder_V3.h
 
