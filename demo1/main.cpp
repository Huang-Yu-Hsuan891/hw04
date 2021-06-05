#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "mbed_rpc.h"

void parkingcar(Arguments *in, Reply *out);
RPCFunction bLED(&parkingcar, "parkingcar");
BufferedSerial pc(USBTX,USBRX);

Ticker servo_ticker;
Ticker encoder_ticker;

PwmOut pin5(D5), pin6(D6);
DigitalIn encoder(D11);

BufferedSerial xbee(D1, D0);
volatile int steps;
volatile int last;

BBCar car(pin5, pin6, servo_ticker);

void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}


int main() {

   pc.set_baud(9600);
   encoder_ticker.attach(&encoder_control, 10ms);
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   steps = 0;
   last = 0;
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   //printf("%s\r\n", outbuf);
   //xbee.write(outbuf, sizeof(outbuf));
   }
}
void parkingcar(Arguments *in, Reply *out){
    char outbuf[256];
    //char buffer[200];
    int x = in->getArg<int>();
    int y = in->getArg<int>();
    int z = in->getArg<int>();
    //sprintf(buffer, "x = %d, y = %d\r\n", x, y);
    //out->putData(buffer);
    //printf("y = %d\r\n", y);
    //printf("z = %d\r\n", z);
      car.goStraight(-50);
      while(steps*6.5*3.14/32 < y) {
      //printf("encoder = %d\r\n", steps);
      ThisThread::sleep_for(100ms);
      }
      car.stop();
      car.turn(-100, 0.3);
      while(steps*6.5*3.14/32 < y + 10) {
      //printf("encoder = %d\r\n", steps);
      ThisThread::sleep_for(100ms);
      }
      car.stop();
      car.goStraight(-50);
      while(steps*6.5*3.14/32 < x + y + 10) {
      ThisThread::sleep_for(100ms);
      }
      car.stop();
}
/*void parkingcar(Arguments *in, Reply *out){
    char outbuf[256];
    int x = in->getArg<int>();
    int y = in->getArg<int>();
    int z = in->getArg<int>();
      car.goStraight(-80);
      RPC::call("/goStraight/run -50", outbuf);
      while(steps*6.5*3.14/32 < y - 3) {
      ThisThread::sleep_for(100ms);
      }
      car.turn(-80, -0.3);
      RPC::call("/turn/run 50 -0.3", outbuf);
      while(steps*6.5*3.14/32 < y) {
      ThisThread::sleep_for(100ms);
      }
      car.goStraight(-80);
      RPC::call("/goStraight/run 50", outbuf);
      while(steps*6.5*3.14/32 < x + y) {
      ThisThread::sleep_for(100ms);
      }
      RPC::call("/stop/run ", outbuf);
      car.stop();
}*/