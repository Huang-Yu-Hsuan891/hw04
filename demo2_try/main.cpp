#include"mbed.h"
#include "mbed_rpc.h"
#include "bbcar.h"
//#include "cstdlib"
#include "bbcar_rpc.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
void linedetection(Arguments *in, Reply *out);
RPCFunction bLED(&linedetection, "linedetection");

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

//DigitalIn encoder(D11);
volatile int steps;
volatile int last;

int main(){
   //t1.start(callback(&queue, &EventQueue::dispatch_forever));
   //queue.call(detectline);
   //encoder_ticker.attach(&encoder_control, 10ms);
   uart.set_baud(9600);
   //pc.set_baud(9600);
   char buf[256], outbuf[256];
   //FILE *devin = fdopen(&xbee, "r");
   //FILE *devout = fdopen(&xbee, "w");
   while(1){
      for (int i = 0; ; i++){
            char *recv = new char[1];
            uart.read(recv, 1);
            buf[i] = *recv;
            if (*recv == '\n') {break;}
      }
      //printf("%s\r\n", buf);
      RPC::call(buf, outbuf);
      //ThisThread::sleep_for(2s);
   }
}

void linedetection(Arguments *in, Reply *out){
   char outbuf[256];
    int x1 = in->getArg<int>();
    int y1 = in->getArg<int>();
    int x2 = in->getArg<int>();
    int y2 = in->getArg<int>(); 
    int dis = in->getArg<float>();
    //printf("%d\r\n", x1);
    if (x1 - x2 < 5 && dis != 0) {
       car.goStraight(60);
       ThisThread::sleep_for(1s);
       car.stop();
       ThisThread::sleep_for(500ms);
    }
}