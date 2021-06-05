#include"mbed.h"
#include "bbcar.h"
#include "cstdlib"

//BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

DigitalOut led1(LED1);
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
DigitalInOut pin10(D10);

BBCar car(pin5, pin6, servo_ticker);

int main(){

   uart.set_baud(9600);
   parallax_ping  ping1(pin10);

   car.goStraight(20);
   //ThisThread::sleep_for(500ms);
   while(1){
      // for ping to detect object
      //car.goStraight(50);
      if((float)ping1>10) led1 = 1;
      else {
         led1 = 0;
         car.stop();
         break;
      }
      ThisThread::sleep_for(10ms);

      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            //pc.write(recv, sizeof(recv));
            float a = atof(recv);
            printf("a = %d", a);
            if (a < 180) car.turn(20, 0.8);
            else if (a > 180) car.turn(20, -0.8);
            else car.goStraight(20);
            ThisThread::sleep_for(10ms);
      }


   }
}