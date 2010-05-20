/*
    GSM.h - library for the GSM Playground - GSM Shield for Arduino
    www.hwkitchen.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __GSM
#define __GSM

#include "WProgram.h"

#define GSM_LIB_VERSION 101 // library version X.YY (e.g. 1.00)

// if defined - debug print is enabled with possibility to print out 
// debug texts to the terminal program
//#define DEBUG_PRINT

// if defined - debug LED is enabled, otherwise debug LED is disabled
//#define DEBUG_LED_ENABLED

// if defined - SMSs are not send(are finished by the character 0x1b
// which causes that SMS are not send)
// by this way it is possible to develop program without paying for the SMSs 
//#define DEBUG_SMS_ENABLED



// length for the internal communication buffer
#define COMM_BUF_LEN        200

#include "AT.h"


// pins definition
#define GSM_ON              5 // connect GSM Module turn ON to pin 5 
#define GSM_RESET           4 // connect GSM Module RESET to pin 4 
#define DTMF_OUTPUT_ENABLE  2 // connect DTMF Output Enable to pin 2
#define DTMF_DATA_VALID     3 // connect DTMF Data Valid to pin 3
#define DTMF_DATA0          6 // connect DTMF Data0 to pin 6
#define DTMF_DATA1          7 // connect DTMF Data1 to pin 7
#define DTMF_DATA2          8 // connect DTMF Data2 to pin 8
#define DTMF_DATA3          9 // connect DTMF Data3 to pin 9


// some constants for the InitParam() method
#define PARAM_SET_0   0
#define PARAM_SET_1   1

// DTMF signal is NOT valid
#define DTMF_NOT_VALID      0x10

// GPIO pins
#define GPIO10  10
#define GPIO11  11
#define GPIO12  12
#define GPIO13  13
#define GPIO_DIR_IN   0
#define GPIO_DIR_OUT  1

// status bits definition
#define STATUS_NONE                 0
#define STATUS_INITIALIZED          1
#define STATUS_REGISTERED           2
#define STATUS_USER_BUTTON_ENABLE   4


// Time-Delays
#define START_TINY_COMM_TMOUT       20
#define START_SHORT_COMM_TMOUT      500
#define START_LONG_COMM_TMOUT       1000
#define START_XLONG_COMM_TMOUT      5000
#define START_XXLONG_COMM_TMOUT     7000
#define MAX_INTERCHAR_TMOUT         20
#define MAX_MID_INTERCHAR_TMOUT     100
#define MAX__LONG_INTERCHAR_TMOUT   1500
#define AT_DELAY                    500



class GSM : public AT 
{
  public:

    // library version
    int LibVer(void);
    // constructor
    GSM(void);


    // turns on GSM module
    void TurnOn(void);
    // sends some initialization parameters
    void InitParam (byte group);
    // enables DTMF decoder
    void EnableDTMF(void);
    // gets DTMF value
    byte GetDTMFSignal(void);
    // turns off/on the speaker
    void SetSpeaker(byte off_on);
    // checks if module is registered in the GSM network
    // must be called regularly
    byte CheckRegistration(void);
    // returns registration state
    byte IsRegistered(void);
    // returns whether complete initialization was made
    byte IsInitialized(void);
    // finds out the status of call
    byte CallStatus(void);
    byte CallStatusWithAuth(char *phone_number,
                            byte first_authorized_pos, byte last_authorized_pos);
    // picks up an incoming call
    void PickUp(void);
    // hangs up an incomming call
    void HangUp(void);
    // calls the specific number
    void Call(char *number_string);
    // makes a call to the number stored at the specified SIM position
    void Call(int sim_position);

    // Speaker volume methods - set, increase, decrease
    char SetSpeakerVolume(byte speaker_volume);
    char IncSpeakerVolume(void);
    char DecSpeakerVolume(void);

    // sends DTMF signal
    char SendDTMFSignal(byte dtmf_tone);

    // User button methods
    inline byte IsUserButtonEnable(void) {return (module_status & STATUS_USER_BUTTON_ENABLE);};
    inline void DisableUserButton(void) {module_status &= ~STATUS_USER_BUTTON_ENABLE;};
    inline void EnableUserButton(void) {module_status |= STATUS_USER_BUTTON_ENABLE;};
    byte IsUserButtonPushed(void);  

    // User LED methods
    void TurnOnLED(void);
    void TurnOffLED(void);

    // GPIO methods
    char SetGPIODir(byte GPIO_pin, byte direction);
    char SetGPIOVal(byte GPIO_pin, byte value);
    char GetGPIOVal(byte GPIO_pin);

    // Method for reading a temperature 
    int GetTemp(void);



  private:

    // global status - bits are used for representation of states
    byte module_status;


};
#endif