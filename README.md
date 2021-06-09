# hw04
# part1 我是放在demo1_new資料夾內，part2 是放在demo2_try資料夾內，part3 則是放在demo3_2資料夾內。
# 以下為part1內容講解
# 首先有一個RPC function是用來當呼叫這個RPC_FUNCTION parkingcar，分別傳入三個參數(x,y,z)，我用setCalibTable去做車子速度的調控。z=0是從西方倒車，z=1是從東方倒車。dis1 = x - 5和dis2 = y - 5
# 是為了做轉彎的時候也會後退一定的距離，time1 = (dis1 / 10.0) * 1000和time2 = (dis2 / 10.0) * 1000是用來計算以此速度需要行走的時間。
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
# 以上的code就是讓車子倒退，轉彎再倒退所呼叫的function和time

# 以下為part1 python內容講解
   s.write("/parkingcar/run 20 14 0 \n".encode())
   傳一段rpc指令經由xbee給mbed
   
# 以下為part2內容講解
# 首先宣告一個RPC function是用來當呼叫這個RPC_FUNCTION linedetection，如果在規定的範圍內偵測到直線，就讓car直走
       car.goStraight(60);
       
       ThisThread::sleep_for(1s);
       
       car.stop();
       
       ThisThread::sleep_for(500ms);
       
 # 以下為part2 openmv 內容講解
 # 我使用lab14 detection 的方式，只是在merge_distance加大讓線段別那麼多，之後就uart.write(("/linedetection/run %d %d %d %d %f\r\n" % print_args).encode()) 給mbed呼叫rpc function
 
 # 以下為part3內容講解
 # 我額外開了一個queue和thread去做車子角度的調整，每兩秒呼叫一次，做一次車子的調整，在main function中，給了一個迴圈當ping偵測到25公分的距離時會自動停下，否則會一直讀apriltag的資料進來
        if (a == 1) {
                car.turn(40, -0.8);  // turn right
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
        }
        else if (a == 2) {
                car.turn(30, -0.9);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            } 
        else if (a == 3) {
                car.goStraight(20);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
            }
        else if (a == 4) {
                //car.turn(30, -0.9);
                car.goStraight(20);
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
        }
        else if (a == 5) {
                car.goStraight(20);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
        } else if (a == 6) {
                car.turn(30, 0.9);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
        } else if (a == 7) {
                car.turn(40, -0.8);  // turn left
                ThisThread::sleep_for(1s);
                car.stop();
                ThisThread::sleep_for(1s);
        } else if (a == 8) {
                car.stop();
                ThisThread::sleep_for(1s);
        }
# 以上為輸入interger a相對應車子要轉彎還是走直線

# 以下為part openmv 內容講解
# 在這裡我會先進行角度的判斷，最後把相對應的數值再傳給mbed去做使用
      if print_args > 190:
          h = 1
      elif print_args > 183:
          h = 2
      elif print_args > 180:
          h = 3
      elif print_args == 180:
          h = 4
      elif print_args > 177:
          h = 5
      elif print_args > 170:
          h = 6
      else:
          h = 7
   

