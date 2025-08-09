#include <Adafruit_GC9A01A.h>


#define RST 2
#define CS 1
#define DC 0
#define SDA 4
#define SCL 5

#define REDBUTTON 7
#define GREENBUTTON 3
#define YELLOWBUTTON 10
#define BLUEBUTTON 8

int numbersInputted = 0;
int chainNumber = 1;
String masterChain = "";
String inputChain = "";
boolean gameNotLost = true;
int delayTimer = 0;


Adafruit_GC9A01A tft(CS, DC, SDA, SCL, RST);


void setup() 
{
  pinMode(REDBUTTON, INPUT_PULLUP);
  pinMode(GREENBUTTON, INPUT_PULLUP);
  pinMode(YELLOWBUTTON, INPUT_PULLUP);
  pinMode(BLUEBUTTON, INPUT_PULLUP);
  tft.begin();
  tft.setRotation(0); 
  tft.fillScreen(GC9A01A_BLACK);
  tft.setCursor(90,90);
  drawColors();
  randomSeed(123123);
  Serial.begin(9600);
}

void loop() 
{
  while(gameNotLost)
  {
    playCode();
    displayCode();
    Serial.print("Number: ");
    Serial.println(chainNumber);
    Serial.print("Current code: ");
    Serial.println(masterChain);
    getInput();
    checkInput();
    chainNumber++;
  }

}

void drawColors()
{
  tft.fillRect(0,0,120,120,GC9A01A_RED);
  tft.fillRect(0,120,120,120,GC9A01A_BLUE);
  tft.fillRect(120,0,120,120,GC9A01A_GREEN);
  tft.fillRect(120,120,120,120,GC9A01A_YELLOW);
  tft.fillCircle(120,120,70,GC9A01A_BLACK);
  delay(2000);
}
void displayCode()
{
  for(int i = 0; i < masterChain.length(); i++)
  {
    if(masterChain.charAt(i) == '1')
    {
      Serial.println("printing");
      tft.fillRect(90,90,30,30,GC9A01A_RED);
      tone(6,440);
      delay(500-delayTimer);
      noTone(6);
      tft.fillRect(90,90,30,30,GC9A01A_BLACK);
      delay(500-delayTimer);
    }
    else if(masterChain.charAt(i) == '2')
    {//blue
      tft.fillRect(90,120,30,30,GC9A01A_BLUE);
      tone(6,540);
      delay(500-delayTimer);
      noTone(6);
      tft.fillRect(90,120,30,30,GC9A01A_BLACK);
      delay(500-delayTimer);
    }
    else if(masterChain.charAt(i) == '3')
    {//green
      tft.fillRect(120,90,30,30,GC9A01A_GREEN);
      tone(6,640);
      delay(500-delayTimer);
      noTone(6);
      tft.fillRect(120,90,30,30,GC9A01A_BLACK);
      delay(500-delayTimer);
    }
    else if(masterChain.charAt(i) == '4')
    {//ylw
      tft.fillRect(120,120,30,30,GC9A01A_YELLOW);
      tone(6,340);
      delay(500-delayTimer);
      noTone(6);
      tft.fillRect(120,120,30,30,GC9A01A_BLACK);
      delay(500-delayTimer);
    }
  }
}
void playCode()
{
  int currentNumber = random(1,5);
  //red
  if(currentNumber == 1)
  {
    masterChain = masterChain + "1";
  }
  else if(currentNumber == 2)
  {//blue
    masterChain = masterChain + "2";
  }
  else if(currentNumber == 3)
  {//green
    masterChain = masterChain + "3";
  }
  else if(currentNumber == 4)
  {//ylw
    masterChain = masterChain + "4";
    
  }


}

void getInput()
{
  while(true)
  {
    if(digitalRead(REDBUTTON) == LOW)
    {
      inputChain = inputChain + "1";
      numbersInputted++;
      tft.fillCircle(90,90,15, GC9A01A_RED);
      delay(200);
      Serial.println("red entered");
      tft.fillCircle(90,90,15, GC9A01A_BLACK);
      
    }
    if(digitalRead(BLUEBUTTON) == LOW)
    {
      inputChain = inputChain + "2";
      numbersInputted++;
      tft.fillCircle(90,150,15,GC9A01A_BLUE);
      delay(200);
      Serial.println("blue entered");
      tft.fillCircle(90,150,15,GC9A01A_BLACK);
      
    }
    if(digitalRead(GREENBUTTON) == LOW)
    {
      inputChain = inputChain + "3";
      numbersInputted++;
      tft.fillCircle(150,90,15,GC9A01A_GREEN);
      delay(200);
      Serial.println("green entered");
      tft.fillCircle(150,90,15,GC9A01A_BLACK);

    }
    if(digitalRead(YELLOWBUTTON) == LOW)
    {
      inputChain = inputChain + "4";
      numbersInputted++;
      tft.fillCircle(150,150,15,GC9A01A_YELLOW);
      delay(200);
      Serial.println("yellow entered");
      tft.fillCircle(150,150,15,GC9A01A_BLACK);
      
    }
    if(numbersInputted == masterChain.length())
    {
      Serial.print("Final chain Input: ");
      Serial.println(inputChain);
      checkInput();
      numbersInputted = 0;
      break;
    }
  }
}


void checkInput()
{
  for(int i = 0; i < inputChain.length(); i++)
  {
    Serial.print("Looking For: ");
    Serial.println(inputChain.charAt(i));
    Serial.print("Got: ");
    Serial.println(masterChain.charAt(i));
    if(inputChain.charAt(i) != masterChain.charAt(i))
    {
      gameNotLost = false;
      Serial.println("Lost");
      break;
    }
  }
  inputChain = "";
  delayTimer = delayTimer + 15;
}
