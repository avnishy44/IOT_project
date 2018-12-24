/*     
 Read char value from Serial Monitor
 Display that value on the Serial Monitor
 */

#include <LiquidCrystal.h>       //load the liquid crystal library
LiquidCrystal LCD(2,3,4,5,6,7);  //creating the liquid crystal object in format [LiquidCrystal(rs, enable, d4, d5, d6, d7)] 


int i = 0;                      //variable to be incremented for changing body[] array element               
String body[3];                 //variable for storing 3 different values coming from serial monitor
char val = 0;                   //variable to store serial data temporariy
int incoming = 0;               //variable to store serial data availability status

void setup()
{
  Serial.begin(115200);         //begin serial monitor
  Serial.println("Serial Monitor Connected");  
  LCD.begin(16,2);              //initialize LCD screen
  LCD.setCursor(0,1);           //set LCD cursor to lower left corner of display 
    LCD.print("WELCOME");           //print body[0] content to LCD
    delay(2000);
}

void loop()
{
  /*IF SERIAL DATA LINE IS COMPLETED THEN PRINT BODY VARIABLE CONTENT ON LCD*/
  if(val == '\n'){
    
    i=0;                    //reset the value of variable i
    
    Serial.println(body[0]);      //print the cotents of body[0]
    LCD.setCursor(0,0);           //set LCD cursor to upper left corner of display 
    LCD.print("IP address :");    //print out the first line
    LCD.setCursor(0,1);           //set LCD cursor to lower left corner of display 
    LCD.print(body[0]);           //print body[0] content to LCD
    delay(2000);
    
    Serial.println(",,,,,,,,,");
    
    Serial.println(body[1]);        //print the cotents of body[1]
    LCD.setCursor(0,0);             //set LCD cursor to upper left corner of display 
    LCD.print("Soil Moisture :");   //print out the first line
    LCD.setCursor(0,1);             //set LCD cursor to lower left corner of display 
    LCD.print(body[1]);             //print body[1] content to LCD
    delay(2000);
    
    Serial.println(",,,,,,,,,");
    
    Serial.println(body[2]);        //print the cotents of body[2]
    LCD.setCursor(0,0);             //set LCD cursor to upper left corner of display 
    LCD.print("Water Level :");     //print out the first line
    LCD.setCursor(0,1);             //set LCD cursor to lower left corner of display 
    LCD.print(body[2]);             //print body[2] content to LCD
    delay(2000);
    
    LCD.setCursor(0,0);
    LCD.print("                "); //clear the line
    LCD.setCursor(0,1); 
    LCD.print("                "); //clear the line

    /*RESET THE BODY ARRAY*/      
    body[0]="";
    body[1]="";
    body[2]="";
  }
  
  incoming = Serial.available();    //Store serial status in variable incoming
  while (incoming == 0)             //keep checking until something is available
  {
    incoming = Serial.available();  //Store serial status in variable incoming
  }
   val = Serial.read();             //Reads the input from the Serial Monitor
    
  if (val == ',')                    //If val is a comma                           
  {  
    i++;                             //increment the value of i for assigning different body variable for storage
  }
    /*IF i=0 STORE THE SERIAL DATA IN body[0]*/
    if(i == 0){
      body[i]+=char(val);
    } 
    /*IF i=1 STORE THE SERIAL DATA IN body[1]*/
    else if (i == 1){
      if(val!=','){
        body[i]+=char(val);
      }                   
    }
    /*IF i=2 STORE THE SERIAL DATA IN body[2]*/
    else if (i == 2){
      if(val!=','){
        body[i]+=char(val);
      }                   
    } 
}
