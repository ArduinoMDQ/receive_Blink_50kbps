// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int LED=7;
const char ID_TX=0x70;
const char ID_RX=0x80;//id del dispositivo
boolean ledON=1;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(9600);
    pinMode(LED,OUTPUT);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_50KBPS))                   // init can bus : baudrate = 50k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(1000);
        goto START_INIT;
    }
}


void loop()
{
    unsigned char stmpON[8] = {0, 1, 1, 3, 4, 5, 6, 7};
    unsigned char stmpOFF[8] = {0, 1, 0, 3, 4, 5, 6, 7};
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.println("Dispositivo ID: ");
        Serial.println(canId);
        
        if(buf[2]==1){
        digitalWrite(LED,true);
          Serial.println("Mensaje: Led Encendido");
           CAN.sendMsgBuf(ID_TX,0, 8, stmpON);//cuando enciende manda memsaje

        }else{
          digitalWrite(LED,false);
            Serial.println("Mensaje: Led Apagado");
           CAN.sendMsgBuf(ID_TX,0, 8, stmpOFF);//cuando enciende manda memsaje

        }
    


     /*   for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i]);
            Serial.print("\t");
            if(ledON && i==0)
            {
             
              digitalWrite(LED,buf[i]);
              ledON=0;
              delay(500);
              }
            else if((!(ledON)) && i==4){
              
              digitalWrite(LED,buf[i]);
              ledON=1;
              }
              
              
        }*/
        Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
