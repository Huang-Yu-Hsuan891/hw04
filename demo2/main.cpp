#include"mbed.h"

#include "bbcar.h"
#include "cstdlib"
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

int main(){
   uart.set_baud(9600);
   //car.goStraight(20);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            float a = atof(recv);
            if (a == 1) {
               car.turn(30, -0.8); // turn right
               ThisThread::sleep_for(500ms);
               car.stop();
               ThisThread::sleep_for(100ms);
            }
            else if (a == 2) {
               car.turn(30, -0.5);
               ThisThread::sleep_for(500ms);
               car.stop();
               ThisThread::sleep_for(100ms);
            }
            else if (a == 3) {
               car.turn(30, 0.8); // turn left
               ThisThread::sleep_for(500ms);
               car.stop();
               ThisThread::sleep_for(100ms);
            }
            else {
               car.goStraight(20);
               ThisThread::sleep_for(500ms);
               car.stop();
               ThisThread::sleep_for(100ms);
            }
      }
   }
   
}