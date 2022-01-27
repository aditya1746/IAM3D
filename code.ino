#include <Servo.h>

Servo thrustN, thrustS, thrustW, thrustE; 

int mode = 2, horizontal = 3, vertical = 4;
int enable_lf = 9, enable_lb = 10, enable_rf = 11, enable_rb = 12;
int rfcw = 14, rfccw = 15, rbcw = 16, rbccw = 17, lfcw = 18, lfccw = 19, lbcw = 20, lbccw = 21;

void setup()
{
  Serial.begin(9600);
  
  pinMode(DCleft,OUTPUT); pinMode(DCright,OUTPUT);

  pinMode(rfcw,OUTPUT); pinMode(rfccw,OUTPUT); pinMode(rbcw,OUTPUT); pinMode(rbccw,OUTPUT);
  pinMode(lfcw,OUTPUT); pinMode(lfccw,OUTPUT); pinMode(lbcw,OUTPUT); pinMode(lbccw,OUTPUT);

  thrustN.attach(5); thrustS.attach(6); thrustW.attach(7); thrustE.attach(8); 
  
  // ====================== ARMING =================== (ye ya to yaha pr hona chahiye ya fir loop me, to chala ke hit and trial kar lo)
  
  int h = pulseIn(horizontal,HIGH), v = pulseIn(vertical,HIGH);
  
  while(h<1800 || v<1800);            // esa kuch karna padega, basically apan remote se ek signal ka wait kar rahe he
}

void fly(int hover)
{
  int rpm = map(hover,950,2050,0,180);

  thrustN.write(rpm); thrustS.write(rpm); thrustE.write(rpm); thrustW.write(rpm);
}

void land()
{
  thrustN.write(0); thrustS.write(0); thrustE.write(0); thrustW.write(0);
}

int turn_fun(int x)
{
	return map(x-40, 0, 510, 0, 100);
}

void MOVE(int x, int y)
{
  int x = map(x,0,1023,0,300), y = map(y,0,1023,0,300);
  
  if(y > 20) 
  {
	digitalWrite(rfcw,HIGH);
	digitalWrite(rfccw,LOW);
	digitalWrite(rbcw,HIGH);
	digitalWrite(rbccw,LOW);
	
	digitalWrite(lfcw,HIGH);
	digitalWrite(lfccw,LOW);
	digitalWrite(lbcw,HIGH);
	digitalWrite(lbccw,LOW);
  }
  else if (y<-20)
  {
	digitalWrite(rfcw,LOW);
	digitalWrite(rfccw,HIGH);
	digitalWrite(rbcw,LOW);
	digitalWrite(rbccw,HIGH);
	
	digitalWrite(lfcw,LOW);
	digitalWrite(lfccw,HIGH);
	digitalWrite(lbcw,LOW);
	digitalWrite(lbccw,HIGH);
  }
  else
  {
	  
  }
  
  if(x>-50 && x<50) // only back and fro
  {
	analogWrite(enable_rf,map(y,-550,550,0,255));
	analogWrite(enable_rb,map(y,-550,550,0,255));
	analogWrite(enable_lf,map(y,-550,550,0,255));
	analogWrite(enable_lb,map(y,-550,550,0,255));
  }
  else if(x > 50) // towards right
  {
	int change = turn_fun(x);
	
	analogWrite(enable_rf,map(y,-550,550,0,255) - change);
	analogWrite(enable_rb,map(y,-550,550,0,255) - change);
	analogWrite(enable_lf,map(y,-550,550,0,255) + change);
	analogWrite(enable_lb,map(y,-550,550,0,255) + change);
  }	  
  else // towards left
  {
	int change = turn_fun(x);
	
	analogWrite(enable_rf,map(y,-550,550,0,255) + change);
	analogWrite(enable_rb,map(y,-550,550,0,255) + change);
	analogWrite(enable_lf,map(y,-550,550,0,255) - change);
	analogWrite(enable_lb,map(y,-550,550,0,255) - change);
  }
}

void stop()
{
	digitalWrite(rfcw,LOW);
	digitalWrite(rfccw,LOW);
	digitalWrite(rbcw,LOW);
	digitalWrite(rbccw,LOW);
	
	digitalWrite(lfcw,LOW);
	digitalWrite(lfccw,LOW);
	digitalWrite(lbcw,LOW);
	digitalWrite(lbccw,LOW);
	
}
void loop()
{
	int hori = pulseIn(horizontal,HIGH);
	int verti = pulseIn(vertical,HIGH);
	int m = pulseIn(mode,HIGH)
	
	if(mode<1100) // fly
	{
		fly(hori);
	}
	else		// drive
	{
		land();
		
		int x = hori - 1500, y = verti - 1500;

		MOVE(x,y);
		
		stop();
	}
	
}
