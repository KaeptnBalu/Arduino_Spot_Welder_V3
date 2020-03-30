#define _ARDUINO_SPOT_WELDER_V3_3_3
/***********************************************************************************************//**
 *  \par        Arduino Spot Welder - Source File.
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
 *  \file       Arduino_Spot_Welder_V3_3_3.ino
 *  \author     Marc Schönfleisch <http://malectrics.eu/>
 *  \version    3.3.3
 *  \date       September 2019
 *  \copyright  Copyright(c)2019 Marc Schönfleisch <info@malectrics.eu>. All right reserved.
 *
 *  \par        Changelog
 *  \li         01jul2017  MS  Initial release
 *  \li         12dec2017  JFF New release with major rewrite
 *  \li         15jan2018  MS change battery voltage reading for V3.2 Spot Welder
 *  \li         05jun2018  MS remove softwarereset to eliminate need of optiboot bootloader
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

/***********************************************************************************************//**
 *  \par        Menu and display Screen Descriptions.
 *              The main screen is accessed by a normal device boot. The initial screen is raised
 *              unless the input voltage is too low, in which case a low voltage screen is raised.
 *              The menus and dispay screens are arranged as follows;
 *  \verbatim
 +----------------+  MAIN SCREEN
 |   Status Line  |  Trigger mode, number of welds, battery charge indicator
 |----------------|
 | Variable       |  Pulse duration in 4x font, adjusted using the encoder
 | Variable Units |  Time units in 2x font
 |    Message     |  Message line in 1x font
 +----------------+

 +----------------+  MAIN MENU
 |   Status Line  |  Trigger mode, number of welds, battery charge indicator
 |----------------|
 |   Auto Pulse   |  Raise the AutoPulse menu
 |   Batt Alarm   |  Raise the Battery Alarm setting screen
 |   Shrt Pulse   |  Raise the Short Pulse setting screen
 +----------------+

 +----------------+  AUTOPULSE MENU
 |  Auto Pulse    |  Menu label
 |----------------|
 |   Activate     |  Raise the AutoPulse Activate setting screen
 |    Delay       |  Raise the AutoPulse Delay setting screen
 |     Exit       |  Exit to the Main screen
 +----------------+

    The system screen is accessed by booting the device with the encoder push button depressed.
    The screen allows changing of system settings. It is arranged as follows;

 +----------------+  SYSTEM MENU
 |    Settings    |  Raise the SETTINGS menu
 |    Display     |  Raise the Display Invert setting screen
 |     Boot       |  Raise the REBOOT menu
 +----------------+

 +----------------+  SETTINGS MENU
 |   Max Pulse    |  Raise the Maximum Weld Pulse Duration setting screen
 |   Batt Cal     |  Raise the Battery Calibration screen
 |     Exit       |  Return to the System Menu
 +----------------+

 +----------------+  REBOOT MENU
 |     Reboot     |  Re-boot device
 |   Safe Reset   |  Reset EEPROM keeping current weld count and re-boot the device
 |   Full Reset   |  Reset EEPROM to factory default settings and re-boot the device
 +----------------+
    \endverbatim
 *//***********************************************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <avr/wdt.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "printf.h"
#include "Arduino_Spot_Welder_V3_3_3.h"

// Machine states
enum states {
	ST_STANDBY,        /**< Machine state: standby */
	ST_MAIN_SCREEN,    /**< Machine state: display main screen */
	ST_MAIN_SCREEN_CNT, /**< Machine state: display statistics */
	ST_MENU_SCREEN,    /**< Machine state: display menu screen */
	ST_SUB_MENU_1,     /**< Machine state: display sub-menu1 */
	ST_SUB_MENU_2,     /**< Machine state: display sub-menu2 */
	ST_BATTERY_LOW,    /**< Machine state: low battery voltage */

	ST_SYSTEM_SCREEN,  /**< Machine state: display system screen */
	ST_SYSTEM_MENU,    /**< Machine state: display system menu */
	ST_SETTINGS_MENU,  /**< Machine state: display settings menu */
	ST_REBOOT_MENU,    /**< Machine state: display reboot menu */
	ST_MAXWELD_SCREEN, /**< Machine state: display max weld setting screen */
	ST_BATTCAL_SCREEN, /**< Machine state: display battery calibration */
	ST_INVERT_SCREEN,  /**< Machine state: display invert setting screen */
	ST_PULSE_VOLTAGE,  /**< Machine state: display measured pulse voltage screen */
};

enum event {
	// Private machine events
	EV_NONE,           /**< Machine event: no pending event */
	EV_BTNDN,          /**< Machine event: button pressed */
	EV_BTNUP,          /**< Machine event: button released */
	EV_ENCUP,          /**< Machine event: encoder rotate right */
	EV_ENCDN,          /**< Machine event: encoder rotate left */

	// Public machine events
	EV_BOOTDN,         /**< Machine event: button pressed on boot */
	EV_STBY_TIMEOUT,   /**< Machine event: standby timer has timed out */
	EV_BATT_LV,        /**< Machine event: battery low voltage event */
	EV_EEUPD,          /**< Machine event: EEPROM needs updating */
	EV_PULSE_VOLTS,    /**< Machine event: foot switch hold during pulse */
};

/***************************************************************************************************
* Global program variables and objects                                                             *
***************************************************************************************************/

// Structures and objects
progData pData;                             /**< Program operating data */
Adafruit_SSD1306 display( 128, 64, &Wire, OLED_RESET, 800000L ); /**< OLED display object */

// Static variables
uint8_t mState         = ST_MAIN_SCREEN;    /**< Current machine state */
uint8_t batteryVoltage = DEF_NOM_BATT_V;    /**< Current battery voltage x10 */
int8_t batt_gauge;                          /**< Battery gauge segments to display */
boolean sysMenu = false;             /**< In the system menu structure */

// Volatile variables - will be changed by the ISR
volatile unsigned long lastActiveTime;
volatile uint8_t mEvent;          /**< Current pending machine event */

void reset_mcusr( void ) __attribute__( ( naked ) ) __attribute__( ( section( ".init3" ) ) );
void reset_mcusr( void ) {
	MCUSR = 0;
	wdt_disable();
}

/***************************************************************************************************
* Program setup                                                                                    *
***************************************************************************************************/
/**
 *  \brief    Program setup.
 *  \remarks  Performed once only at powerup.
 */
void setup() {
#if defined  _DEVELOPMENT_ || defined _BOOTSYS_
		Serial.begin( _SERIAL_BAUD_ );
#endif /* _DEVELOPMENT_ || _BOOTSYS_*/

	// Setup the pin states and directions.
	pinMode( PIN_LED,              OUTPUT );
	pinMode( PIN_PULSE,            OUTPUT );
	pinMode( PIN_CLK,              INPUT );
	pinMode( PIN_DT,               INPUT );
	pinMode( PIN_SW,               INPUT_PULLUP );
	pinMode( PIN_FOOT_SWITCH,      INPUT_PULLUP );
	pinMode( PIN_AUTO_PULSE,       INPUT );
	digitalWrite( PIN_SW,          HIGH );
	digitalWrite( PIN_FOOT_SWITCH, HIGH );

	// Setup the OLED display and clear it.
	display.begin( SSD1306_SWITCHCAPVCC, 0x3C );
	display.clearDisplay(); // clear remnants when rebooting
	display.display();

	// The interrupt is used to sense the encoder rotation. It could just as well be polled
	// without loss of responsiveness. This was actually tried and no noticeable performance
	// degradation was observed. Interrupts are usefull for high speed encoders such as
	// used on servo systems. Manually adjusted encoders are very slow.
	attachInterrupt( ENC_INT, isr, FALLING );

	// This is used by the standbby timer to identify the period of inactivity.
	lastActiveTime = millis();

	// Test if the pushbutton is pressed at boot time. If so then ensure entry to the system
	// menu by the issue of a boot button down event.
#ifdef _BOOTSYS_
		mEvent = EV_BOOTDN;
#else
		mEvent = btnState() == B_DN ? EV_BOOTDN : EV_NONE;
#endif /* _BOOTSYS_ */

	loadEeprom();

	// Invert the display if required and draw the splash screen. This can only be done after
	// loading the program data (which contains the screen invert switch).
	display.setRotation( pData.pFlags.en_oledInvert ? OLED_INVERT : 0 );
	splash();

	if ( !digitalRead( PIN_FOOT_SWITCH ) )
		foot_switch_error();

#ifdef _DEVELOPMENT_
		Serial.print( F( "Pulse Time       " ) ); Serial.println( pData.pulseTime );
		Serial.print( F( "Pulse Voltage    " ) ); Serial.println( pData.PulseBatteryVoltage );
		Serial.print( F( "Pulse Amps       " ) ); Serial.println( pData.PulseAmps );
		Serial.print( F( "Battery Alarm    " ) ); Serial.println( pData.batteryAlarm );
		Serial.print( F( "Weld Count       " ) ); Serial.println( pData.weldCount );
		Serial.print( F( "Auto Pulse Delay " ) ); Serial.println( pData.autoPulseDelay );
		Serial.print( F( "Max Pulse Time   " ) ); Serial.println( pData.maxPulseTime );
		Serial.print( F( "Short Pulse Time " ) ); Serial.println( pData.shortPulseTime );
		Serial.print( F( "Battery Offset   " ) ); Serial.println( pData.batteryOffset );
		Serial.print( F( "Auto Pulse       " ) ); Serial.println( pData.pFlags.en_autoPulse ? "On" : "Off" );
		Serial.print( F( "Display Invert   " ) ); Serial.println( pData.pFlags.en_oledInvert ? "Invert" : "Normal" );
#endif /* _DEVELOPMENT_ */
}

/***************************************************************************************************
* Main program loop                                                                                *
***************************************************************************************************/
/**
 *  \brief    Main program loop.
 *  \remarks  Manages the state machine and eeprom updates.
 */
void loop() {
	// The state machine is run every loop cycle - as fast as possible.
	stateMachine();

	// The eeprom is updated with changed variables. The update routine internally ensures that
	// the eeprom is only updated every few seconds to limit wearout.
	updateEeprom();
}

/***************************************************************************************************
* State Machine                                                                                    *
***************************************************************************************************/
/**
 *  \brief  Implementation of state machine.
 */

// This entire state machine is legacy code that has been much modified and added to. It is
// somewhat of a "dog's breakfast" and really is in need of a complete rewrite. Even I have
// difficulty following it and modifications that work are a pleasant surprise - JFF.

void stateMachine() {
	char str[5];
	static uint8_t selectedMenu       = 0;
	static uint8_t selectedMainMenu   = 0;
	static uint8_t selectedSubMenu    = 0;
	static boolean btn                = false;
	static uint8_t measuredVoltage;

	// Scan for events - the event queue length is one.

	// Process any public boot events. These events are the highest priority
	// and must be processed before any of the private events.
	if ( mEvent == EV_BOOTDN ) {
		mState = ST_SYSTEM_SCREEN;
		mEvent = EV_NONE;

	} else {
		// Search for and process any private events.
		checkForBtnEvent();
		checkForSleepEvent();
		checkForLowVoltageEvent();

		switch ( mEvent ) {
		case EV_STBY_TIMEOUT: mState = ST_STANDBY;
			mEvent = EV_NONE;
			break;
		case EV_BATT_LV:

			if ( !sysMenu ) mState = ST_BATTERY_LOW;

			mEvent = EV_NONE;
			break;
		case EV_BTNUP:

			if ( mState != ST_REBOOT_MENU ) mEvent = EV_NONE;

			break;
		case EV_PULSE_VOLTS: mState = ST_PULSE_VOLTAGE;
			mEvent = EV_NONE;
			break;
		}
	}

	// Machine states
	switch ( mState ) {

	// Pulse Voltage State entered by holding down the foot switch button during pulse,
	// it is exited by a button press event.
	case ST_PULSE_VOLTAGE:

		if ( mEvent == EV_BTNDN )
			mState = sysMenu ? ST_SYSTEM_SCREEN : ST_MAIN_SCREEN;

		displayPulseData();
		mEvent = EV_NONE;
		break;

	// Standby state entered by receiving a standby timeout event,
	// it is exited by a button press event.
	case ST_STANDBY:

		if ( mEvent == EV_BTNDN ) mState = sysMenu ? ST_SYSTEM_SCREEN : ST_MAIN_SCREEN;

		message( FPSTR( LS_STANDBY ), FPSTR( LS_CLICKBTN ), FPSTR( LS_EXITSTBY ) );
		mEvent = EV_NONE;
		break;

	// Low battery state. Entered by receiving a low battery event,
	// this state cannot be exited except by reboot.
	case ST_BATTERY_LOW:

		if ( mEvent == EV_BTNDN ) mState = sysMenu ? ST_SYSTEM_SCREEN : ST_MAIN_SCREEN;

		displayLowBattery();
		mEvent = EV_NONE;
		break;

	// Main screen state displays the main screen without responding to events. This is
	// effectively the home location for an idle loop that cycles through this and the
	// next state where it looks for events. Any state can return to this state to
	// enable an idle loop.
	case ST_MAIN_SCREEN:

		mState = ST_MAIN_SCREEN_CNT;
		sysMenu = false;
		selectedMenu = 0;
		displayMainScreen();
		break;

	// Main screen state that responds to events. This state is an entry point for
	// the menu structure and allows setting and display of operational variables.
	// Weld pulses are also issued from this state if they are required.
	case ST_MAIN_SCREEN_CNT:

		// Activate a weld pulse if required.
		// Check if AutoPulse is enabled and activated.
		if ( digitalRead( PIN_AUTO_PULSE ) && pData.pFlags.en_autoPulse ) {
			displayMainScreen( 1 );
			sendWeldPulse( PIN_AUTO_PULSE, pData.autoPulseDelay * 100, WP_RETRIGGER_DELAY );
			displayMainScreen();
		}

		// Else check if the Foot switch is activated.
		else if ( !digitalRead( PIN_FOOT_SWITCH ) )
			sendWeldPulse( PIN_FOOT_SWITCH, FS_TRIGGER_DELAY, WP_RETRIGGER_DELAY, PL_ACTIVE_L );

		// A button press event will enter the menu structure.
		if ( mEvent == EV_BTNDN ) {
			mState = ST_MENU_SCREEN;
			selectedMenu = 0;
			mEvent = EV_NONE;
			displayMenuType1( NULL, FPSTR( LS_APULSE ), FPSTR( LS_BATTALM1 ), FPSTR( LS_SHORTPLS1 ), 0 );

		} else {

			// Rotary encoder events will change the value of the weld pulse time.
			// The time is constrained between 1ms and a stored maximum value.
			if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
				if ( mEvent == EV_ENCUP ) pData.pulseTime = pData.pulseTime < pData.maxPulseTime
			? pData.pulseTime + 1 : pData.maxPulseTime;
				else pData.pulseTime = pData.pulseTime > MIN_PULSE_TIME ?
					               pData.pulseTime - 1 : MIN_PULSE_TIME;

				pData.pulseTime = pData.pulseTime <MIN_PULSE_TIME ? MIN_PULSE_TIME :
				                                   pData.pulseTime> pData.maxPulseTime ? pData.maxPulseTime : pData.pulseTime;
				mEvent = EV_NONE;
			}

			displayMainScreen();
		}

		break;

	// The first menu in the menu structure. This is accessed from the main screen
	// by a button press event.
	case ST_MENU_SCREEN:

		// A button press event will enter the next level of the menu structure. There are
		// three items in the menu to decide which new menu is entered.
		if ( mEvent == EV_BTNDN ) {
			mState = ST_SUB_MENU_1;
			selectedMainMenu = selectedMenu;

			// Enter a sub-menu to select more options.
			if ( selectedMainMenu == 0 )
				displayMenuType1( FPSTR( LS_APULSE ), FPSTR( LS_MANAUTO ),
				                  FPSTR( LS_DELAY ),  FPSTR( LS_EXIT ), selectedMenu );

			// Allow setting of battery low alarm voltage.
			else if ( selectedMainMenu == 1 ) displayMenuType2( FPSTR( LS_BATTALM ),
				                                            valStr( str, pData.batteryAlarm, VF_BATTALM ), FPSTR( LS_VOLTAGE ) );

			// Allow setting of pre-heat pulse duration.
			else if ( selectedMainMenu == 2 ) displayMenuType2( FPSTR( LS_SHORTPLS ),
				                                            valStr( str, pData.shortPulseTime, VF_SHTPLS ), FPSTR( LS_PCOF ) );

			mEvent = EV_NONE;
			selectedMenu = 0;

			// Rotary encoder events will allow scrolling through the menu options.
		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) selectedMenu = selectedMenu == 0 ? 2 : selectedMenu - 1;
			else selectedMenu = selectedMenu == 2 ? 0 : selectedMenu + 1;

			mEvent = EV_NONE;
			displayMenuType1( NULL, FPSTR( LS_APULSE ), FPSTR( LS_BATTALM1 ),
			                  FPSTR( LS_SHORTPLS1 ), selectedMenu );
		}

		break;

	// Next menu down the menu structure. This is accessed from the
	// first menu by a button press.
	case ST_SUB_MENU_1:

		// A button press event will enter the next level of the menu structure. There are
		// three items in the menu to decide which new menu is entered.
		if ( mEvent == EV_BTNDN ) {
			if ( selectedMainMenu == 0 ) {
				mState = ST_SUB_MENU_2;
				selectedSubMenu = selectedMenu;

				// Set the auto-pulse status.
				if ( selectedSubMenu == 0 ) displayMenuType2( FPSTR( LS_AUTOPLSON ), NULL,
					                                      pData.pFlags.en_autoPulse ? FPSTR( LS_AUTO ) : FPSTR( LS_MANUAL ) );

				// Allow setting of the auto-pulse delay time.
				else if ( selectedSubMenu == 1 ) displayMenuType2( FPSTR( LS_AUTOPLSDLY ),
					                                           valStr( str, pData.autoPulseDelay, VF_DELAY ), FPSTR( LS_SECONDS ) );
				else if ( selectedSubMenu == 2 ) mState = ST_MAIN_SCREEN;

			} else if ( selectedMainMenu == 1 ) mState = ST_MAIN_SCREEN;

			else if ( selectedMainMenu == 2 ) mState = ST_MAIN_SCREEN;
			else mState = ST_MAIN_SCREEN;

			mEvent = EV_NONE;
			selectedMenu = 0;

			// The menu entry type has already been selected from the previous menu. Here the
			// variables are altered according to the selected type.
		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( selectedMainMenu == 0 ) {
				if ( mEvent == EV_ENCDN ) selectedMenu = selectedMenu == 0 ? 2 : selectedMenu - 1;
				else selectedMenu = selectedMenu == 2 ? 0 : selectedMenu + 1;

				displayMenuType1( FPSTR( LS_APULSE ), FPSTR( LS_MANAUTO ),
				                  FPSTR( LS_DELAY ),  FPSTR( LS_EXIT ), selectedMenu );

				// Set the battery alarm voltage by responding to rotary encoder events.
				// The battery alarm voltage cannot be set higher than the current battery voltage
				// and in any event not higher than the maximum allowable alarm voltage.
			} else if ( selectedMainMenu == 1 ) {
				if ( mEvent == EV_ENCDN ) pData.batteryAlarm = pData.batteryAlarm >
					                                       MIN_BATT_BALARM ? pData.batteryAlarm - 1 : MIN_BATT_BALARM;
				else pData.batteryAlarm = pData.batteryAlarm < min( batteryVoltage, MAX_BATT_ALARM ) ?
					                  pData.batteryAlarm + 1 : min( batteryVoltage, MAX_BATT_ALARM );

				displayMenuType2( FPSTR( LS_BATTALM ),
				                  valStr( str, pData.batteryAlarm, VF_BATTALM ), FPSTR( LS_VOLTAGE ) );

				// Set the pre-heat pulse duration by responding to rotary encoder events.
			} else if ( selectedMainMenu == 2 ) {
				if ( mEvent == EV_ENCDN ) pData.shortPulseTime = pData.shortPulseTime >
					                                         MIN_SPULSE_TIME ?  pData.shortPulseTime - 1 : MIN_SPULSE_TIME;
				else pData.shortPulseTime = pData.shortPulseTime < MAX_SPULSE_TIME ?
					                    pData.shortPulseTime + 1 : MAX_SPULSE_TIME;

				displayMenuType2( FPSTR( LS_SHORTPLS ),
				                  valStr( str, pData.shortPulseTime, VF_SHTPLS ), FPSTR( LS_PCOF ) );
			}

			mEvent = EV_NONE;
		}

		break;

	case ST_SUB_MENU_2:

		if ( mEvent == EV_BTNDN ) {
			mState = ST_MAIN_SCREEN;
			mEvent = EV_NONE;
			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( selectedSubMenu == 0 ) {
				pData.pFlags.en_autoPulse ^= 1;
				displayMenuType2( FPSTR( LS_AUTOPLSON ), NULL, pData.pFlags.en_autoPulse ?
				                  FPSTR( LS_AUTO ) : FPSTR( LS_MANUAL ) );
			} else if ( selectedSubMenu == 1 ) {
				if ( mEvent == EV_ENCDN ) pData.autoPulseDelay = pData.autoPulseDelay >
					                                         MIN_APULSE_DELAY ? pData.autoPulseDelay - 1 : MIN_APULSE_DELAY;
				else pData.autoPulseDelay = pData.autoPulseDelay < MAX_APULSE_DELAY ?
					                    pData.autoPulseDelay + 1 : MAX_APULSE_DELAY;

				displayMenuType2( FPSTR( LS_AUTOPLSDLY ),
				                  valStr( str, pData.autoPulseDelay, VF_DELAY ), FPSTR( LS_SECONDS ) );
			}

			mEvent = EV_NONE;
		}

		break;

	// System screen state displays the system screen without responding to events.
	// This is the home state of another idle loop, this one for the system menu.
	case ST_SYSTEM_SCREEN:

		mState = ST_SYSTEM_MENU;
		sysMenu = true;
		selectedMenu = 0;
		displayMenuType1( FPSTR( LS_SYSMENU ), FPSTR( LS_SETTINGS ),
		                  FPSTR( LS_DISPLAY ), FPSTR( LS_BOOT ), 0 );
		break;

	// The first menu in the system menu structure. This is accessed by rebooting the
	// welder while holding the encoder button down.
	case ST_SYSTEM_MENU:

		if ( mEvent == EV_BTNDN ) {
			mEvent = EV_NONE;

			if ( selectedMenu == 0 ) {
				mState = ST_SETTINGS_MENU;
				displayMenuType1( FPSTR( LS_SETTMENU ), FPSTR( LS_MAXPULSE ),
				                  FPSTR( LS_BATTCAL ),  FPSTR( LS_EXIT ), selectedMenu = 0 );

			} else if ( selectedMenu == 1 ) {
				selectedSubMenu = 0;
				mState = ST_INVERT_SCREEN;
				displayMenuType2( FPSTR( LS_INVERTMENU ), NULL, pData.pFlags.en_oledInvert ?
				                  FPSTR( LS_SCRINV ) : FPSTR( LS_SCRNORM ) );

			} else if ( selectedMenu == 2 ) {
				btn = false;
				mState = ST_REBOOT_MENU;
				displayMenuType1( FPSTR( LS_BOOTMENU ), FPSTR( LS_REBOOT ),
				                  FPSTR( LS_SAFERST ),  FPSTR( LS_FULLRST ), selectedMenu = 0 );
			}

			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) selectedMenu = selectedMenu == 0 ? 2 : selectedMenu - 1;
			else selectedMenu = selectedMenu == 2 ? 0 : selectedMenu + 1;

			mEvent = EV_NONE;
			displayMenuType1( FPSTR( LS_SYSMENU ), FPSTR( LS_SETTINGS ),
			                  FPSTR( LS_DISPLAY ), FPSTR( LS_BOOT ), selectedMenu );
		}

		break;

	case ST_SETTINGS_MENU:

		if ( mEvent == EV_BTNDN ) {
			mEvent = EV_NONE;

			if ( selectedMenu == 0 ) {
				displayMenuType2( FPSTR( LS_MAXPLSMENU ),
				                  valStr( str, pData.maxPulseTime, VF_PLSDLY ), FPSTR( LS_MS ) );
				mState = ST_MAXWELD_SCREEN;
				mEvent = EV_NONE;

			} else if ( selectedMenu == 1 ) {
				measuredVoltage = batteryVoltage;
				displayMenuType2( FPSTR( LS_BATCALMENU ),
				                  valStr( str, measuredVoltage, VF_BATTV ), FPSTR( LS_BATCALMSG ) );
				mState = ST_BATTCAL_SCREEN;
				mEvent = EV_NONE;

			} else if ( selectedMenu == 2 ) {
				mState = ST_SYSTEM_SCREEN;
				mEvent = EV_NONE;
			}

			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) selectedMenu = selectedMenu == 0 ? 2 : selectedMenu - 1;
			else selectedMenu = selectedMenu == 2 ? 0 : selectedMenu + 1;

			mEvent = EV_NONE;
			displayMenuType1( FPSTR( LS_SETTMENU ), FPSTR( LS_MAXPULSE ),
			                  FPSTR( LS_BATTCAL ),  FPSTR( LS_EXIT ), selectedMenu );
		}

		break;

	case ST_REBOOT_MENU:

		if ( mEvent == EV_BTNDN ) btn = true;
		else if ( ( mEvent == EV_BTNUP ) && btn ) {
			if ( selectedMenu == 1 )
				resetEeprom( false );
			else if ( selectedMenu == 2 )
				resetEeprom( true );

			message( FPSTR( LS_REBOOT ), selectedMenu == 1 ? FPSTR( LS_REBOOTSR ) :
			         selectedMenu == 2 ? FPSTR( LS_REBOOTFR ) :
			         FPSTR( LS_REBOOTNR ), FPSTR( LS_WAITMSG ), 2 );


		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) selectedMenu = selectedMenu == 0 ? 2 : selectedMenu - 1;
			else selectedMenu = selectedMenu == 2 ? 0 : selectedMenu + 1;

			displayMenuType1( FPSTR( LS_BOOTMENU ), FPSTR( LS_REBOOT ),
			                  FPSTR( LS_SAFERST ),  FPSTR( LS_FULLRST ), selectedMenu );
		}

		mEvent = EV_NONE;
		break;

	case ST_MAXWELD_SCREEN:

		if ( mEvent == EV_BTNDN ) {
			message( FPSTR( LS_MAXPULSE ), FPSTR( LS_MAXPMSG ), FPSTR( LS_WAITMSG ), 2 );
			mState = ST_SYSTEM_SCREEN;
			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) pData.maxPulseTime = pData.maxPulseTime > MIN_PULSE_TIME ?
				                                       pData.maxPulseTime - 1 : MIN_PULSE_TIME;
			else pData.maxPulseTime = pData.maxPulseTime < MAX_PULSE_TIME ?
				                  pData.maxPulseTime + 1 : MAX_PULSE_TIME;

			pData.maxPulseTime = pData.maxPulseTime <MIN_PULSE_TIME ? MIN_PULSE_TIME :
			                                         pData.maxPulseTime> MAX_PULSE_TIME ? MAX_PULSE_TIME : pData.maxPulseTime;
			displayMenuType2( FPSTR( LS_MAXPLSMENU ),
			                  valStr( str, pData.maxPulseTime, VF_PLSDLY ), FPSTR( LS_MS ) );
		}

		mEvent = EV_NONE;
		break;

	case ST_BATTCAL_SCREEN:

		if ( mEvent == EV_BTNDN ) {
			message( FPSTR( LS_BATTMSG ), FPSTR( LS_RECALMSG ), FPSTR( LS_WAITMSG ), 2 );
			mState = ST_SYSTEM_SCREEN;
			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			if ( mEvent == EV_ENCDN ) measuredVoltage = measuredVoltage > MIN_BATT_V ?
				                                    measuredVoltage - 1 : MIN_BATT_V;
			else measuredVoltage = measuredVoltage < MAX_BATT_V ?
				               measuredVoltage + 1 : MAX_BATT_V;

			pData.batteryOffset += (int16_t)measuredVoltage - (int16_t)batteryVoltage;
			displayMenuType2( FPSTR( LS_BATCALMENU ),
			                  valStr( str, measuredVoltage, VF_BATTV ), FPSTR( LS_BATCALMSG ) );
		}

		mEvent = EV_NONE;
		break;

	case ST_INVERT_SCREEN:

		if ( mEvent == EV_BTNDN ) {
			mState = ST_SYSTEM_SCREEN;
			mEvent = EV_NONE;
			selectedMenu = 0;

		} else if ( mEvent == EV_ENCUP || mEvent == EV_ENCDN ) {
			pData.pFlags.en_oledInvert = !pData.pFlags.en_oledInvert;
			display.setRotation( pData.pFlags.en_oledInvert ? 2 : 0 );
			displayMenuType2( FPSTR( LS_INVERTMENU ), NULL, pData.pFlags.en_oledInvert ?
			                  FPSTR( LS_SCRINV ) : FPSTR( LS_SCRNORM ) );
		}

		mEvent = EV_NONE;
		break;

	default: break;
	}
}

/***************************************************************************************************
* Hardware management routines                                                                     *
***************************************************************************************************/
struct progress {
	uint16_t time;
#define PGR_OFF   ( 0 << 0 )
#define PGR_ON    ( 1 << 0 )
#define PGR_INIT  ( 1 << 7 )
	uint8_t opt;

	uint8_t step;
	unsigned long millis;
};

/**
 *  \brief      Draws progress bar
 *
 *  \param [in/out] o           progress control structure
 *  \param [in] clear           clear progress indicator if true
 *
 *  \return Zero if progress isn't completed otherwise no-zero
 */
int drawProgress( struct progress *o, bool clear ) {
	const int steps = 25, height = 4, x = SSD1306_LCDWIDTH - steps - 1, y = 15;
	int res = 0;

	// Clear indicator?
	if ( clear != false ) {
		display.fillRect( x - 1, y - 1, steps + 2, height + 2, BLACK );
	} else
		// Does indicator initialized?
		if ( !( o->opt & PGR_INIT ) ) {
			display.drawRect( x - 1, y - 1, steps + 2, height + 2, WHITE );
			display.fillRect( x, y, steps, height,
			                  o->opt & PGR_ON ? BLACK : WHITE );
			display.display();
			o->step = 1;
			o->millis = millis();
			o->opt |= PGR_INIT;
		} else
			// Drawing progress if any
			if ( millis() >= ( o->millis + o->step * ( o->time / steps ) ) ) {
				display.fillRect( x, y, o->step, height,
				                  o->opt & PGR_ON ? WHITE : BLACK );
				display.display();
				o->step = (int)( millis() - o->millis ) / ( o->time / steps );
				res = o->step > steps;
			}

	return res;
}

/**
 *  \brief      Generates the welding pulse.
 *  \remarks    Sends the pre-heat pulse, delays, sends the main weld pulse, delays,
 *              then increments the weld count.
 *  \param [in] uint8_t  sensePin         Pulse engagement sensor pin
 *  \param [in] uint16_t delayEngage      Delay before pulse engagement (trigger delay)
 *  \param [in] uint16_t delayRelease     Delay after pulse disengagement (re-trigger delay)
 *  \param [in] boolean  senseActiveLevel Sensor pin logic. Default = PL_ACTIVE_H.
 */
void sendWeldPulse( uint8_t sensePin,
                    uint16_t delayEngage,
                    uint16_t delayRelease,
                    boolean senseActiveLevel ) {
	struct progress wait;
#ifdef _DEVELOPMENT_
		Serial.println( F( "Pulse Activated" ) );
#endif /* _DEVELOPMENT_ */
	bool activePinState = senseActiveLevel != PL_ACTIVE_H ? 0 : 1;

	// Compute the short pulse delay and clip it to greater than or equal to 1 ms.
	unsigned long shortPulseDelay = ( pData.pulseTime * pData.shortPulseTime ) / 100;

	if ( shortPulseDelay < 1 ) shortPulseDelay = 1;

	// Wait the pulse engagement delay time.
	if ( sensePin == PIN_AUTO_PULSE ) {
		wait.opt = PGR_ON;
		wait.time = delayEngage;

		while ( !drawProgress( &wait, false ) ) {
			if ( digitalRead( PIN_AUTO_PULSE ) != activePinState ) {
				drawProgress( &wait, true );
				return;
			}
		}
	} else {
		delay( delayEngage );
	}

	if ( pData.shortPulseTime > 0 && pData.pulseTime > 3 ) {
		// Send the pre-heat pulse.
		weldPulse( P_ON );
		delay( shortPulseDelay );
		weldPulse( P_OFF );

		// Wait the inter-pulse delay time.
		delay( shortPulseDelay );
	}

	// Send the main weld pulse.
	weldPulse( P_ON );
	delay( pData.pulseTime );
	uint16_t battery = analogRead( PIN_BATT_V );
	weldPulse( P_OFF );

	checkForPulseDataEvent( battery );

	unsigned long currentMillis = millis();

	// Wait until the the pulse engagement sensor is deactivated.
	do {
		weldPulse( P_OFF );
	} while ( digitalRead( sensePin ) == activePinState && ( millis() - currentMillis < PV_DELAY ) );

	delay( 10 );

	if ( millis() - currentMillis > PV_DELAY )
		mEvent = EV_PULSE_VOLTS;

	// Delay before the weld pulse can be triggered again.
	wait.opt = PGR_OFF;
	wait.time = delayRelease;

	while ( !drawProgress( &wait, false ) )
		continue;

	// Increment the weld counter and flag activity.
	if ( pData.weldCount < 9999 )
		pData.weldCount++;
	else
		pData.weldCount = 0;

	lastActiveTime = millis();

	if ( !digitalRead( PIN_FOOT_SWITCH ) )
		mEvent = EV_PULSE_VOLTS;
}
/**
 *  \brief    Checks the battery voltage and responds to the result.
 *  \remarks  Reads the battery voltage from an analog pin and converets it to an internal
 *            representation adjusted by the stored calibration offset. If the voltage is below
 *            the alarm setting then a low voltage event is issued.
 */
void checkForLowVoltageEvent() {

	static unsigned long lastBVTime = 0;

	// Do not read the battery voltage too often.
	if ( millis() - lastBVTime > BV_INTERVAL ) {
		lastBVTime = millis();

		// Battery voltage obtained by reading the a/d converter, scaling the result, and
		// adding the stored offset voltage. The result is the voltage * 10
		batteryVoltage = (uint8_t)( analogRead( PIN_BATT_V ) * 5.0 * 4.03 * 10.0 /
		                            1023.0 + pData.batteryOffset );


#ifdef _TESTING_
			// Ignore low battery for UI testing. This prevents a low voltage lockout
			// when running from USB power without a 12V battery connected.
			batteryVoltage = DEF_NOM_BATT_V + pData.batteryOffset;
#endif /* _TESTING_ */

		// If the battery voltage is low then issue a low voltage event.
		if ( pData.batteryAlarm > batteryVoltage ) mEvent = EV_BATT_LV;

		// compute the number of battery gauge segments to display on the status line.
		batt_gauge = (int8_t)( ( ( ( (int16_t)( batteryVoltage ) * 10 - (int16_t)( pData.batteryAlarm ) * 11 +
		                             DEF_MAX_BATT_V ) * 10 ) / ( DEF_MAX_BATT_V - (int16_t)( pData.batteryAlarm ) ) - 5 ) / 20 );
		batt_gauge = batt_gauge < 1 ? 0 : batt_gauge > 5 ? 5 : batt_gauge;
	}
}

void checkForPulseDataEvent( uint16_t battery ) {
	pData.PulseBatteryVoltage = (uint16_t)( battery * 5.0 * 4.03 * 10.0 /
	                                        1023.0 + pData.batteryOffset );

	// 111 = 1/0.009 --- where 0.009 eqauls 9mOhm system resistance
	pData.PulseAmps = (uint16_t)( pData.PulseBatteryVoltage * 117 );
}

/**
 *  \brief    Issues a standby timeout event if the standby time has expired without any activity.
 *  \remarks  The standby timeout period is defined in ms in the file header.
 */
void checkForSleepEvent() {
	// The last active time is updated every time some activity occurs. If the standby timeout
	// period has expired without any activity then a timeout event is issued.
	if ( lastActiveTime + STANDBY_TIME_OUT < millis() )
		if ( mState != ST_BATTERY_LOW ) mEvent = EV_STBY_TIMEOUT;
}
/**
 *  \brief    Reads the rotary encoder push button switch transition event.
 *  \remarks  Issues a switch transition event according to whether the switch is has been pressed
 *            and the debounce interval has expired or whether the switch has been released.
 */
void checkForBtnEvent() {
	static unsigned long lastBtnTime = 0;
	static boolean lastBtnState = B_UP;
	boolean thisBtnState;

	thisBtnState = btnState();

	// Ignore changes that occur within the debounce period.
	if ( millis() - lastBtnTime > RS_DEBOUNCE ) {

		// Only respond to a change of the biutton state.
		if ( thisBtnState != lastBtnState ) {

			// Issue an event based on the current state of the button.
			mEvent = thisBtnState == B_UP ? EV_BTNUP : EV_BTNDN;
			lastActiveTime = lastBtnTime = millis();
			lastBtnState = thisBtnState;
		}
	}
}

/***************************************************************************************************
* Interrupt service routine                                                                        *
***************************************************************************************************/
/**
 *  \brief    Interrupt service routine.
 *  \remarks  Responds to interrupts from the rotary encoder. Manages and tracks rotary encoder
 *            position changes. Issues encoder position transition events according to whether
 *            the encoder is rotated clockwise (up) or anticlockwise (down).
 */
void isr() {
	static volatile unsigned long lastInterruptTime = 0;

	// Ignore changes that occur within the debounce period.
	if ( ( millis() - lastInterruptTime ) > RS_DEBOUNCE ) {

		// There are two pins to the encoder. One pin issues the interrupt. The other pin
		// therefore indicates the phase, which is effectively the direction of rotation.
		// Read the phase pin and issue an encoder direction event based on its state.
		mEvent = digitalRead( PIN_DT ) ? EV_ENCDN : EV_ENCUP;
		lastActiveTime = lastInterruptTime = millis();
	}
}

/***************************************************************************************************
* Menu management routines                                                                         *
***************************************************************************************************/
/**
 *  \brief      Displays a menu type 1 on the LCD.
 *  \remarks    This is a three line selection menu. If the title pointer is NULL then a standard
 *              status line is drawn otherwise the title is drawn on the screen.
 *  \param [in] const __FlashStringHelper *title       Menu title.
 *  \param [in] const __FlashStringHelper *line1       Line 1 text.
 *  \param [in] const __FlashStringHelper *line2       Line 2 text.
 *  \param [in] const __FlashStringHelper *line3       Line 3 text.
 *  \param [in] uint8_t                   SelectedItem Selected menu item.
 */
void displayMenuType1( const __FlashStringHelper *title,
                       const __FlashStringHelper *line1,
                       const __FlashStringHelper *line2,
                       const __FlashStringHelper *line3,
                       uint8_t SelectedItem ) {

	display.clearDisplay();

	if ( title == NULL )
		drawStatusLine();
	else {
		setTextProp( 1, 1, 1, WHITE );
		display.print( title );
		display.drawLine( 0, CHR_H + 3, SSD1306_LCDWIDTH - 1, CHR_H + 3, WHITE );
	}

	setTextProp( 2, 2, 16, WHITE, SelectedItem == 0 );
	display.print( line1 );
	setTextProp( 2, 2, 16 + 2 * CHR_H + 1, WHITE, SelectedItem == 1 );
	display.print( line2 );
	setTextProp( 2, 2, 16 + 4 * CHR_H + 2, WHITE, SelectedItem == 2 );
	display.print( line3 );
	display.drawRect( 0, SelectedItem == 0 ? 16 :
	                  SelectedItem == 1 ? 16 + 2 * CHR_H + 1 :
	                  16 + 4 * CHR_H + 2, 2, 2 * CHR_H, WHITE );
	display.display();
}
/**
 *  \brief      Displays a menu type 2 on the LCD.
 *  \remarks    This is a variable display and adjustment dialog. Normally the second parameter
 *              is a pointer to a string value in ram and the third parameter is a pointer to the
 *              units string in flash. If the second parameter is NULL then the third parameter
 *              is treated as the second parameter. This enables the display of two adjacent
 *              flash based strings.
 *  \param [in] const __FlashStringHelper *title  Menu title.
 *  \param [in] const char                *value  Item value.
 *  \param [in] const __FlashStringHelper *units  Item units.
 */
void displayMenuType2( const __FlashStringHelper *title,
                       const char *value,
                       const __FlashStringHelper *units ) {

	display.clearDisplay();

	setTextProp( 1, 1, 1, WHITE );
	display.print( title );
	display.drawLine( 0, CHR_H + 3, SSD1306_LCDWIDTH - 1, CHR_H + 3, WHITE );
	setTextProp( 2, 2, 16 + LINE_H );

	if ( value == NULL ) display.print( units );
	else {
		display.print( value );
		setTextProp( 1, 2, 16 + 3 * LINE_H );
		display.print( units );
	}

	display.display();
}

/***************************************************************************************************
* Display management routines                                                                      *
***************************************************************************************************/
/**
 *  \brief                      Sets the properties of a text string to be drawn to the display.
 *  \param [in] uint8_t  size   Text size.
 *  \param [in] uint8_t  xpos   Text x-coordinate in pixels from left.
 *  \param [in] uint8_t  ypos   Text x-coordinate in pixels from top.
 *  \param [in] uint16_t color  Text foreground  color (default WHITE).
 *  \param [in] boolean  invert True if colors are to be inverted (bg=color,fg=BLACK) default false.
 */
void setTextProp( uint8_t size, uint8_t xpos, uint8_t ypos, uint16_t color, boolean invert ) {

	display.setTextSize( size );
	display.setCursor( xpos, ypos );

	if ( invert )
		display.setTextColor( BLACK, color );
	else
		display.setTextColor( color );
}

/**
 *  \brief    Draws a status line to the LCD.
 *  \remarks  The status line shows the pulse trigger mode and the total number of welds performed.
 *            On dual color displays the status line is within the top colored display region. An
 *            underline is drawn under the status line. A battery gauge containing 5 segments is
 *            drawn where each segment is 20% of the range from the battery alarm voltage to the
 *            defined battery maximum voltage. The number of segments to draw is computed in the
 *            procedure that checks the battery voltage. If battery is below 10% then a cross is
 *            drawn inside the battery.
 */
void drawStatusLine() {
	char str[8];

	setTextProp( 1, 1, 1 );
	display.print( pData.pFlags.en_autoPulse ? FPSTR( LS_AUTO_BAR ) : FPSTR( LS_MANUAL_BAR ) );
	setTextProp( 1, 8 * CHR_W, 1 );
	display.print( valStr( str, pData.weldCount, VF_WELDCNT ) );
	setTextProp( 1, 13 * CHR_W, 1 );
	display.print( FPSTR( LS_WELDS ) );

	// Put an underline under the status line.
	display.drawLine( 0, CHR_H + 3, SSD1306_LCDWIDTH - 1, CHR_H + 3, WHITE );

	// Draw the battery gauge skeleton. This is just an empty rectangle with another small
	// rectangle on the left side representing the battery terminal.
	display.drawRect( SSD1306_LCDWIDTH - 33, 0, 33, CHR_H, WHITE );
	display.drawRect( SSD1306_LCDWIDTH - 35, ( CHR_H - 1 - 2 ) / 2, 2, 4, WHITE );

	// Draw the battery gauge segments. Each segment is a filled rectangle.
	if ( batt_gauge )
		for ( int8_t n = 0 ; n < batt_gauge ; n++ )
			display.fillRect( SSD1306_LCDWIDTH - 7 - 6 * n, 2, 5, 4, WHITE );

	else {
		// If battery is below 15% then draw a cross to indicate it is empty.
		display.drawLine( SSD1306_LCDWIDTH - 33,     0,   SSD1306_LCDWIDTH - 1, CHR_H - 1, WHITE );
		display.drawLine( SSD1306_LCDWIDTH - 33, CHR_H - 1, SSD1306_LCDWIDTH - 1,     0,   WHITE );
	}
}

/**
 *  \brief  Draw the main screen to the LCD.
 */
void displayMainScreen( bool signaled ) {
	char str[5];

	display.clearDisplay();
	drawStatusLine();

	// Write the current value of the weld pulse duration and its units.
	setTextProp( 4, 1, 16 + CHR_H / 2 );
	display.print( valStr( str, pData.pulseTime, VF_PLSDLY ) );
	setTextProp( 2, 4 * CHR_W * 4 + CHR_W, 16 + CHR_H / 2 + 4 * CHR_H - 2 * CHR_H - 2, WHITE, signaled );
	display.print( FPSTR( LS_MS ) );

	// Write a message under the value.
	setTextProp( 1, ( SSD1306_LCDWIDTH - ( sizeof( LS_WPDRN ) - 1 ) * CHR_W ) / 2,
	             16 + CHR_H / 2 + 4 * CHR_H - 2 * CHR_H - 2 + 2 * LINE_H );
	display.print( FPSTR( LS_WPDRN ) );

	display.display();
}

void displayMainScreen() {
	displayMainScreen( false );
}

/**
 *  \brief  Display pulse voltage message and battery voltage measured during pulse to LCD.
 */

void displayPulseData() {
	char str[5];

	display.clearDisplay();
	drawStatusLine();

	setTextProp( 1, ( SSD1306_LCDWIDTH - ( sizeof( LS_PULSEV ) - 1 ) * CHR_W * 2 ) / 2, 16 );
	display.print( FPSTR( LS_PULSEV ) );
	setTextProp( 1, ( SSD1306_LCDWIDTH - 5 * CHR_W ) / 2, 16 + 2 * LINE_H );
	display.print( valStr( str, pData.PulseBatteryVoltage, VF_BATTV ) );
	display.print( FPSTR( LS_VUNITS ) );

	setTextProp( 1, 1, 16 + 4 * LINE_H );
	display.print( FPSTR( LS_PULSEA ) );
	setTextProp( 1, 57, 16 + 4 * LINE_H );
	display.print( valStr( str, pData.PulseAmps, VF_BATTA ) );
	display.print( FPSTR( LS_AUNITS ) );

	display.display();
}

/**
 *  \brief  Display LOW BATTERY message and BATTERY voltage to LCD.
 */

void displayLowBattery() {
	char str[5];

	display.clearDisplay();
	drawStatusLine();

	setTextProp( 2, ( SSD1306_LCDWIDTH - ( sizeof( LS_BATTERY ) - 1 ) * CHR_W * 2 ) / 2, 16 );
	display.print( FPSTR( LS_BATTERY ) );
	setTextProp( 2, ( SSD1306_LCDWIDTH - ( sizeof( LS_LOWV ) - 1 ) * CHR_W * 2 ) / 2, 16 + 2 * LINE_H );
	display.print( FPSTR( LS_LOWV ) );
	setTextProp( 1, ( SSD1306_LCDWIDTH - 1 * CHR_W ) / 2, 16 + 4 * LINE_H );
	display.print( valStr( str, batteryVoltage, VF_BATTV ) );
	display.print( FPSTR( LS_VUNITS ) );

	display.display();
}

/**
 *  \brief    Display a MESSAGE screen.
 *  \remarks  A message screen consists of a screen header with underline and 3 rows of text.
 *            The first row is double size font, other rows are normal size.
 *            The message screen is displayed for a specified number of seconds before
 *            returning to the caller. The default time is zero for immediate return.
 *  \param [in] const __FlashStringHelper* line1        Line 1 text.
 *  \param [in] const __FlashStringHelper* line1        Line 2 text.
 *  \param [in] const __FlashStringHelper* line3        Line 3 text.
 *  \param [in] uint8_t                    displayTime  Delay time (default = 0)
 */
void message( const __FlashStringHelper *line1,
              const __FlashStringHelper *line2,
              const __FlashStringHelper *line3,
              uint8_t displayTime ) {

	display.clearDisplay();

	setTextProp( 1, ( SSD1306_LCDWIDTH - ( sizeof( LS_MSGHDR ) - 1 ) * CHR_W ) / 2, 1 );
	display.print( FPSTR( LS_MSGHDR ) );
	display.drawLine( 0, CHR_H + 3, SSD1306_LCDWIDTH - 1, CHR_H + 3, WHITE );

	setTextProp( 2, 1, 16 );
	display.print( line1 );
	setTextProp( 1, 1, 16 + 2 * LINE_H );
	display.print( line2 );
	setTextProp( 1, 1, 16 + 3 * LINE_H );
	display.print( line3 );

	display.display();

	if ( displayTime ) delay( displayTime * 1000 );
}

/**
 *  \brief    Display the SPLASH screen.
 *  \remarks  This is shown once only at start-up and is for general information and advertising.
 */
void splash() {
	display.clearDisplay();
	display.display();

	setTextProp( 1, 1, 1 );
	display.print( F( _DEVICENAME_ ) ); // 21 chars per line
	setTextProp( 1, 1, 16 );
	display.print( F( "Ver " xstr( _VERSION_MAJOR_ ) "." xstr( _VERSION_MINOR_ ) "."
	                  xstr( _REVISION_ ) " " __DATE__ ) );
	setTextProp( 1, 1, 16 + LINE_H );
	display.print( F( "by " _AUTHOR_ ) );
	setTextProp( 1, 1, 16 + 2 * LINE_H );
	display.print( F( "Copyright (c) " _COPYRIGHT_ ) );
	setTextProp( 1, 1, 16 + 3 * LINE_H );
	display.print( F( _COMPANY_ ) );
	setTextProp( 1, 1, 16 + 4 * LINE_H );
	display.print( F( _RIGHTS_ ) );

	display.display();

	uint16_t timer = 0;

	while ( btnState() != B_DN && timer < SPLASHTIME ) {
		delay( 10 );
		timer += 10;
	}

	while ( btnState() == B_DN )
		continue;

	display.clearDisplay();
	display.display();
}

void foot_switch_error() {
	display.clearDisplay();
	display.display();

	setTextProp( 1, 1, 1 );
	display.print( "FOOT SWITCH ERROR!" ); // 21 chars per line
	setTextProp( 1, 1, 16 );
	display.print( F( "Please:" ) );
	setTextProp( 1, 1, 16 + LINE_H );
	display.print( F( "- turn off welder" ) );
	setTextProp( 1, 1, 16 + 2 * LINE_H );
	display.print( F( "- remove foot switch" ) );
	setTextProp( 1, 1, 16 + 3 * LINE_H );
	display.print( F( "- correct the wiring" ) );

	display.display();

	while ( !digitalRead( PIN_FOOT_SWITCH ) );
}

/***************************************************************************************************
* Utility Conversion Functions                                                                     *
***************************************************************************************************/
/**
 *  \brief                    Returns a character string representing a formatted numeric value.
 *  \param [in] char *str     Pointer to the string to receive the formatted result.
 *  \param [in] uint16_t val  The integer value to be formatted.
 *  \param [in] vf_Type fType The type of variable to be formatted.
 *  \return     char*         Pointer to the formatted string.
 */
char *valStr( char *str, uint16_t val, vf_Type fType ) {

	// We must resort to this awkward kludge to format the variables because variable width and
	// precision (* specifier) are not implemented in avr gcc - bugger!!!

	switch ( fType ) {
	case VF_BATTALM:
	case VF_BATTV:   sprintf_P( str, PSTR( "%2.1u.%01u" ), val / 10, val % 10 ); break;
	case VF_BATTA:   sprintf_P( str, PSTR( "%2.1u.%01u" ), val / 10, val % 10 ); break;
	case VF_WELDCNT: sprintf_P( str, PSTR( "%5.1u" ), val );                 break;
	case VF_PLSDLY:  sprintf_P( str, PSTR( "%4.1u" ), val );                 break;
	case VF_SHTPLS:  sprintf_P( str, PSTR( "%3.1u" ), val );                 break;
	case VF_DELAY:   sprintf_P( str, PSTR( "%1.1u.%01u" ), val / 10, val % 10 ); break;
	}

	return str;
}

/***************************************************************************************************
* Utility EEPROM Functions                                                                         *
***************************************************************************************************/
/**
 *  \brief                    Reset the EEPROM and program data to factory default settings.
 *  \remarks                  EEPROM data is only written if the new data is different to the
 *                            existing data to limit EEPROM wearout.
 *  \param [in] boolean full  True to reset the weld count, battery offset, and screen inversion.
 */
void resetEeprom( boolean full ) {

	// Write the factory default data to the eeprom. In the case of a full reset, the weld count,
	// battery offset, and screen orientation are zeroed, otherwise they are left unchanged.
	pData.autoPulseDelay       = DEF_AUTO_PLSDELAY;
	pData.PulseBatteryVoltage  = DEF_PULSE_VOLTAGE;
	pData.PulseAmps            = DEF_PULSE_AMPS;
	pData.batteryAlarm         = DEF_BATT_ALARM;
	pData.weldCount            = full == EE_FULL_RESET ? 0 : pData.weldCount;
	pData.pulseTime            = DEF_PULSE_TIME;
	pData.maxPulseTime         = DEF_MAX_PULSE_TIME;
	pData.shortPulseTime       = DEF_SPULSE_TIME;
	pData.batteryOffset        = full == DEF_BATTERY_OFFSET ? 0 : pData.batteryOffset;
	pData.pFlags.en_autoPulse  = DEF_AUTO_PULSE;
	pData.pFlags.en_oledInvert = full ? DEF_OLED_INVERT : pData.pFlags.en_oledInvert;

	// The put function does not write new data if the existing data is the same thereby
	// limiting eeprom wearout.
	EEPROM.put( EEA_PDATA, pData );

	// The unique id is a simple method to ensure that a valid data set exists in the eeprom
	// (there are much better methods but we don't have the code space to spare).
	EEPROM.put( EEA_ID, EE_UNIQUEID );

#if defined  _DEVELOPMENT_ || defined _BOOTSYS_

		if ( full ) Serial.print( F( "EEPROM Full Reset" ) );
		else Serial.println( F( "EEPROM Reset" ) );

#endif /* _DEVELOPMENT_ || _BOOTSYS_*/
}

void loadEeprom() {
	// Check the eeprom integrity by reading a magic number. If it is corrupt then the eeprom
	// is given a full factory reset, otherwise program data is loaded from the eeprom.
	uint32_t uniqueID;

	EEPROM.get( EEA_ID, uniqueID );

	if ( uniqueID != EE_UNIQUEID )
		resetEeprom( EE_FULL_RESET );
	else
		EEPROM.get( EEA_PDATA, pData );
}
/**
 *  \brief    Udates the EEPROM data with local program data structure.
 *  \remarks  EEPROM data is only written if the new data is different to the
 *            existing data to limit EEPROM wearout.
 */
void updateEeprom() {
	static unsigned long lastEEUpdatetime = 0;

	// Do not do this too often to prevent premature eeprom wearout.
	if ( millis() - lastEEUpdatetime > EEPROM_UPDATE_T ) {
		lastEEUpdatetime = millis();

		// Write the current program data to the eeprom.
		EEPROM.put( EEA_PDATA, pData );

#ifdef _DEVELOPMENT_
			Serial.println( F( "Updated EEPROM" ) );
#endif /* _DEVELOPMENT_ */
	}
}
