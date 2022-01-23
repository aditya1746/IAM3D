#include <Servo.h>

Servo thrustN, thrustS, thrustW, thrustE; 

int DCleft = 6, DCright = 7;
int rfcw = 14, rfccw = 15, rbcw = 16, rbccw = 17, lfcw = 18, lfccw = 19, lbcw = 20, lbccw = 21;

void setup()
{
  Serial.begin(9600);
  
  pinMode(DCleft,OUTPUT); pinMode(DCright,OUTPUT);

  pinMode(rfcw,OUTPUT); pinMode(rfccw,OUTPUT); pinMode(rbcw,OUTPUT); pinMode(rbccw,OUTPUT);
  pinMode(lfcw,OUTPUT); pinMode(lfccw,OUTPUT); pinMode(lbcw,OUTPUT); pinMode(lbccw,OUTPUT);

  thrustN.attach(2); thrustS.attach(3); thrustW.attach(4); thrustE.attach(5); 
  
  // ====================== ARMING =================== (ye ya to yaha pr hona chahiye ya fir loop me, to chala ke hit and trial kar lo)
  
  // while(channeli.value<1200);            // esa kuch karna padega, basically apan remote se ek signal ka wait kar rahe he
}

void fly(int hover)
{
  int rpm = map(hover,0,1023,0,180);

  thrustN.write(rpm); thrustS.write(rpm); thrustE.write(rpm); thrustW.write(rpm);
}

void land()
{
  thrustN.write(0); thrustS.write(0); thrustE.write(0); thrustW.write(0);
}

void MOVE(int x, int y)
{
  int x = map(x,0,1023,0,300), y = map(y,0,1023,0,300);
}

void loop()
{
  int hover = analogRead(A0);

  while(hover) fly(hover);

  land();

  int x = analogRead(A2), y = analogRead(A3);

  while(x || y) MOVE(x,y);
}
