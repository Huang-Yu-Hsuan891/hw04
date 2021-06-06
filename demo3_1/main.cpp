#include"mbed.h"
#include "bbcar.h"
#include "cstdlib"

BufferedSerial pc(USBTX,USBRX);
BufferedSerial uart(D1,D0);
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);
Thread t1;
EventQueue queue1(32 * EVENTS_EVENT_SIZE);
/*int main(){
   uart.set_baud(9600);
   int a = 0;
   //car.goStraight(20);
   //ThisThread::sleep_for(1s);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            a = atoi(recv);

            if (a == 1) {
                car.turn(30, -0.5);  // turn right
                ThisThread::sleep_for(1s);
                car.stop();
            }
            else if (a == 2) {
                car.turn(30, +0.8);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
            } 
            else if (a == 3) {
                car.goStraight(20);
                ThisThread::sleep_for(1s);
                car.stop();
            } else car.stop();
      }
   }
}*/
int a = 0;
void detectges() {
            if (a == 1) {
                car.turn(50, -0.7);  // turn right
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            }
            else if (a == 2) {
                car.turn(50, 0.7);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            } 
            else if (a == 3) {
                car.goStraight(40);
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            } else {
                car.stop();
                ThisThread::sleep_for(1s);
            }
}

int main(){
   uart.set_baud(9600);
   //int a = 0;
   //car.goStraight(20);
   //ThisThread::sleep_for(1s);
   t1.start(callback(&queue1, &EventQueue::dispatch_forever));
   queue1.call_every(2s, &detectges);

   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            a = atoi(recv);

           /* if (a == 1) {
                car.turn(40, -0.3);  // turn right
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            }
            else if (a == 2) {
                car.turn(40, 0.8);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            } 
            else if (a == 3) {
                car.goStraight(20);
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            } else {
                car.stop();
                ThisThread::sleep_for(1s);
            }*/
      }
   }
}