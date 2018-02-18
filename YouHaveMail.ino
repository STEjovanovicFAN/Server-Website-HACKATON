#include "cellular_hal.h"
#include <stdlib.h>
// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

//First we will need to declare which pins are used for reading and writing
//As well as set some constants.
#define TIMEOUT 1000
#define CTRL_Z 0x1A


\\Set up the pins
int motionPower = D0;
int motionInput = A1;
int boardLed = D7;
int timeOut = 20000; //unused



int power = D0;
int resetButtonOut = C1;
int resetButtonInput = C3;
int led1 = D6; //unused
long delayLength = 1000;

//unused
bool motionDetected = false;


int callback(int type, const char* buf, int len, char* param){
	Serial.print("Return: ");
    Serial.write((const uint8_t*)buf, len);
    Serial.println();
	return WAIT;
}


//unused
void text2(){

char message[] = "testing";
char* pMessage= message;

char szReturn[32] = "";
//Cellular.command(callback, szReturn, TIMEOUT,"AT+CMGS=\"+14038757188\"");
//Cellular.command(callback, szReturn, TIMEOUT, "Reset! 0x1A");

char szCmd[64];



}

void setup() {
// Set the keep-alive value for TELUS SIM card
Particle.keepAlive(30);

pinMode(motionPower, OUTPUT);
pinMode(motionInput, INPUT);
pinMode(boardLed, OUTPUT);
pinMode(led1, OUTPUT);

pinMode(resetButtonInput, INPUT);
pinMode(resetButtonOut, OUTPUT);


digitalWrite(motionPower, HIGH);
digitalWrite(resetButtonInput, HIGH);
//Wait for 1 minute for it to set up (warm up?);


delay(60000);


digitalWrite(boardLed, HIGH);



}




//send a text to my phone number
void text(){

char message[] = "testing";
char* pMessage= message;

char szReturn[32] = "";
//Cellular.command(callback, szReturn, TIMEOUT,"AT+CMGS=\"+14038757188\"");
//Cellular.command(callback, szReturn, TIMEOUT, "Testing! 0x1A");

char szCmd[64];

Cellular.command(callback, szReturn, TIMEOUT, "AT+CMGF=1\r\n");
Cellular.command(callback, szReturn, TIMEOUT, "AT+CMGS=\"+14038077104\" \r\n");
Cellular.command(callback, szReturn, TIMEOUT, "You have mail!");
  sprintf(szCmd, "%c", CTRL_Z);
Cellular.command(callback, szReturn, TIMEOUT, szCmd);

}






bool disabled = false;

//if motion send text

void loop () {
	
	if(!disabled){
		if(digitalRead(motionInput) == HIGH){
			
			text();
			digitalWrite(boardLed, LOW);
			
		}
		
			
		
	
	}
	
}


