#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
AsyncDelay delay_Cs; 
AsyncDelay delay_5s;
int LED = -1;
bool start = 0;
int slow = 500;
int time = 200;
int level = -1;
int Score = 0;
volatile const byte slideSwitch = 7;
volatile const byte Lbut = 4;
volatile const byte Rbut = 5;
bool Slowmoflag = 0;
bool clicking =0;
bool lost = 1;
bool Winner = 1;
bool countDown = 1;
int slowmoDelay[10] = {3000,2800,2600,2400,2200,2000,1800,1600,1400,1200};//array for the wait duration for the slow mo, in other words how long the slow-mo mode is active for.
int sloar[10]={600,550,500,450,400,350,300,250,200,150};//array for the slow-mo values
int timar[10]={200,190,180,170,160,150,140,130,120,110};// array for the normal run times
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(slideSwitch), startstop, CHANGE);//creates the interupt for switch
  attachInterrupt(digitalPinToInterrupt(Lbut), SlowMo, RISING);
  attachInterrupt(digitalPinToInterrupt(Rbut), click, RISING);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (delay_5s.isExpired() && lost == 1){//Will print "get ready to play" after 5 seconds then waits an additonal second for the user to get ready.  
    Serial.println("Get ready to play");
    delay(1000);
    lost = 0;
  }
  if (delay_5s.isExpired() && Winner == 1){//Will print "get ready to play" after 5 seconds then waits an additonal second for the user to get ready. Probably will make these into their own function.
    Serial.println("Get ready to play");
    delay(1000);
    Winner = 0;
  }
  if (start == 1 && countDown == 0 && !lost && !Winner){//where the game actually is. it only plays when the switch is on, countdown is done and lost is false and winner is false. 
    LED++;//selects the pixel linearly 1-10
    CircuitPlayground.setPixelColor(LED, 0, 0, 255);//LED color blue
    delay(time);//controls the speed of the game
    Serial.println(time);//this is just for testing purposes
    CircuitPlayground.clearPixels();

    if (LED ==10){//resets the LED count to -1 so it can get all 10 LEDS
      LED = -1;
    }
    if (Slowmoflag == 1){//this is where the slowmo happens
      time = timar[level]+sloar[level];//choses normal time depending on level and choses slowmo time also depending on level and the sum of these values gets added to time 
      if (delay_Cs.isExpired()){//Waits the certain time depending on level, to change the time back to what the normal time should be depending on the level 
        time = timar[level];
        Slowmoflag = 0;
      }
    }
    clicking = 0;
  }
}

void startstop(){//starts the game when the switch is to the left and turns off when the switch is to the right
  CircuitPlayground.clearPixels();
  start = CircuitPlayground.slideSwitch();
  if (start == 1){
    countDown = 1;
    Serial.println("Game on");
    CountDownfunc();// I think I need to move this to the main loop and thw numbers are getting printed instantly.
    lost = 0;
    Winner = 0;
  }else if(start == 0){
    Serial.println("Game off");
    CircuitPlayground.clearPixels();
    level = -1;
    slow = 500;
    time = 200;
    Score = 0;
    lost = 1;
    Winner = 1;
  }
}
void CountDownfunc(){// give the user 3.4 seconds to get read along with a count down
    Serial.println("Get Ready! LED to hit on is #7. ");
    delay(400);
    Serial.println("3");
    delay(1000);
    Serial.println("2");
    delay(1000);
    Serial.println("1");
    delay(1000);
    Serial.print("GO!");
    countDown = 0;
    Nextlevel();
}
void SlowMo(){//left button interrupt which is the slow-mo button
  Serial.println("slowmo");
  Serial.println(level);
  Slowmoflag = 1;
  delay_Cs.start(slowmoDelay[level], AsyncDelay::MILLIS); // makes the timer cout up by 1 second
}
void click(){// right button interrupt and is where we detect if they click on the currect LED
 if (!clicking){
  clicking = 1;
  if (clicking == 1 && LED == 7){//only changes level when they have clicked on the correct LED which is the seventh LED
    Serial.println("Good hit!!");
    Nextlevel();
  }else if(clicking == 1){// if they miss it calls the lose function
    Lose();
  }
 }
}
void Nextlevel(){// determines the Level
  Serial.println("Level: ");
  Serial.println(level);
  level = level + 1;//increases the level by one when the games first starts and when the get a correct hit.
  Scoreboard();//calls score function
  time = timar[level]; //makes sure the correct game speed is set.
  if (level == 10){
    win();
  }
}
void Scoreboard(){
  Score = Score + 20;
  Serial.println(Score);
}
void Lose(){
  Serial.println("You lost");
  lost = 1;
  Serial.print("Your Final Score: ");
  Serial.println(Score);
  delay_5s.start(5000, AsyncDelay::MILLIS);
  Score = 0;
  level = 0;
}
void win(){
  Serial.println("YAY you won!!");
  //colorFirework();
  delay_5s.start(5000, AsyncDelay::MILLIS);
  level = -1;
  Winner = 0;
  
}

