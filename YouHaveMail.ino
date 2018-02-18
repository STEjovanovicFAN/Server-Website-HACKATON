#include "cellular_hal.h"
#include <stdlib.h>
// Set the TELUS APN
STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

//First we will need to declare which pins are used for reading and writing
//As well as set some constants.

#define TIMEOUT 1000
#define CTRL_Z 0x1A
char szPhoneNumber[14]= "+********";

int motionPower = D0;
int motionInput = A1;
int boardLed = D7;

int led1 = D6;

long delayLength = 1000;


bool motionDetected = false;


int callback(int type, const char* buf, int len, char* param){
	Serial.print("Return: ");
    Serial.write((const uint8_t*)buf, len);
    Serial.println();
	return WAIT;
}

int sendMessage(char* pMessage){
    char szCmd[64];
    
    sprintf(szCmd, "AT+CMGS=\"+%s\",145\r\n", szPhoneNumber);
    
    Serial.print("Sending command ");
    Serial.print(szCmd);
    Serial.println();
    
    char szReturn[32] = "";
    
    Cellular.command(callback, szReturn, TIMEOUT, "AT+CMGF=1\r\n");
    Cellular.command(callback, szReturn, TIMEOUT, szCmd);
    Cellular.command(callback, szReturn, TIMEOUT, pMessage);
    
    sprintf(szCmd, "%c", CTRL_Z);
    
    int retVal = Cellular.command(callback, szReturn, TIMEOUT, szCmd);
    
    if(RESP_OK == retVal){
        Serial.println("+OK, Message Send");
    }
    else{
        Serial.println("+ERROR, error sending message");
    }
    
    return retVal;
}

void setup() {
// Set the keep-alive value for TELUS SIM card
Particle.keepAlive(30);

pinMode(motionPower, OUTPUT);
pinMode(motionInput, INPUT);
pinMode(boardLed, OUTPUT);
pinMode(led1, OUTPUT);


digitalWrite(motionPower, HIGH);
//Wait for 1 minute for it to set up (warm up?);

delay(60000);


digitalWrite(boardLed, HIGH);



}


void text(){

char message[] = "testing";
char* pMessage= message;

char szReturn[32] = "";
//Cellular.command(callback, szReturn, TIMEOUT,"AT+CMGS=\"+1******\"");
//Cellular.command(callback, szReturn, TIMEOUT, "Testing! 0x1A");

char szCmd[64];

Cellular.command(callback, szReturn, TIMEOUT, "AT+CMGF=1\r\n");
Cellular.command(callback, szReturn, TIMEOUT, "AT+CMGS=\"+1******INSERTPHONENUMBERHERE*******\" \r\n");
Cellular.command(callback, szReturn, TIMEOUT, "You have mail!");
  sprintf(szCmd, "%c", CTRL_Z);
Cellular.command(callback, szReturn, TIMEOUT, szCmd);

}



void loop () {
	
	if(digitalRead(motionInput) == HIGH){
		digitalWrite(led1, HIGH);
		text();
	}
	else{
		digitalWrite(led1, LOW);
	}
	
	
	
}


