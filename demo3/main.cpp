#include"mbed.h"
#include "bbcar.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

DigitalOut led1(LED1);
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
DigitalInOut pin10(D10);

BBCar car(pin5, pin6, servo_ticker);

int main(){
   uart.set_baud(9600);
   parallax_ping  ping1(pin10);


   while(1){
      // for ping to detect object
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
            pc.write(recv, sizeof(recv));
            /*int a = recv;
            if (a < 180) car.turn(50, -0.1);
            else if (a > 180) car.turn(50, 0.1);
            else car.goStraight(50);*/
      }


   }
}