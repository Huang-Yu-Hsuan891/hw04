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
#以上的code就是讓車子倒退，轉彎再倒退所呼叫的function和time
# 以下為part1內容講解
