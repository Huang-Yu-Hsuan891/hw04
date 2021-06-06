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
   }
}
void parkingcar(Arguments *in, Reply *out){
    char outbuf[256];
    //char buffer[200];
    int x = in->getArg<int>();
    int y = in->getArg<int>();
    int z = in->getArg<int>();
   double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   //line
   double speed_table0[] = {-12.437, -13.553, -12.995, -11.241, -5.820, 0.000, 5.820, 11.241, 12.995, 13.553, 12.437};
   double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   //ring
   double speed_table1[] = {-10.204, -10.045, -10.523, -10.125, -7.175, 0.239, 7.175, 10.125, 10.523, 10.045, 10.204};

   // first and fourth argument : length of table
   car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

   int dis1;
   int dis2;

   dis1 = x - 5;
   dis2 = y - 5;

   float time1;
   float time2;

   time1 = (dis1 / 10.0) * 1000;
   time2 = (dis2 / 10.0) * 1000;
   
   double factorturn;

   if (z == 0) factorturn = 0.4; // west
   else if (z == 1) factorturn = -0.1; // east
   car.stop();
   ThisThread::sleep_for(2s);

   car.goStraightCalib(-10);
   ThisThread::sleep_for(time2);
   car.stop();
   ThisThread::sleep_for(1s);

   car.goStraightCalibturn(-10, factorturn);
   ThisThread::sleep_for(2s);
   car.stop();
   ThisThread::sleep_for(1s);

   car.goStraightCalib(-10);
   ThisThread::sleep_for(time1);
   car.stop();
}