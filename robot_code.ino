int motor1Pin1 = 3; 
int motor1Pin2 = 4; 
int enable1Pin = 6; 
int motor2Pin1 = 8; 
int motor2Pin2 = 9; 
int enable2Pin = 11; 

int state;
int flag=0;        //makes sure that the serial only prints once the state
int stateStop=0;

int echoPin1 = 5;
int trigPin1 = 7;

int in1 = 4;
int in2 = 5;
int in3 = 9;
int in4 = 10;

long duration;
int distance;

void setup() {
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    // sets enable1Pin and enable2Pin high so that motor can turn on:
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);

    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);


    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void drive_forward()
 {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
 }
 
 void drive_backward()
 {
  digitalWrite(motor1Pin1, LOW); 
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
 }

 void turn_right()
 {
  digitalWrite(motor1Pin1, LOW); 
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
 }

 void turn_left()
 {
  digitalWrite(motor1Pin1, HIGH); 
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
 }

 void stopped()
 {
  digitalWrite(motor1Pin1, LOW); 
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
 }


void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }
    
    //Default to ultrasonic sensor
    ////////////////////   
    else
    {
      // Clears the trigPin condition
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
     // Reads the echoPin, returns the sound wave travel time in microseconds
     duration = pulseIn(echoPin1, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    drive_forward();
    
    if (distance <= 20)
    {
      delay(500);
      turn_right();
      delay(500);
      Serial.print("Turn Right");
    }

    else if (distance <= 15)
    {
      delay(500);
      drive_forward();
      delay(500);
      Serial.print("Drive Backward");
    }

    else if (distance <= 5) 
    {
      delay(500);
      stopped();
      Serial.print("Stopped");
    }
     }
    //////////////
    
    // if the state is 'F' the DC motor will go forward
    if (state == 'F') 
    {
      drive_forward();
      if(flag == 0)
      {
        Serial.println("Go Forward!");
        flag=1;
      }
    }
    
    // if the state is 'R' the motor will turn left
    else if (state == 'R') 
    {
      turn_left();
        if(flag == 0)
        {
          Serial.println("Turn LEFT");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    
    // if the state is 'S' the motor will Stop
    else if (state == 'S' || stateStop == 1) 
    {
      turn_left();
      if(flag == 0)
      {
        Serial.println("STOP!");
        flag=1;
      }
      stateStop=0;
    }
    
    // if the state is 'L' the motor will turn right
    else if (state == 'L') 
    {
      turn_right();
      if(flag == 0)
      {
        Serial.println("Turn RIGHT");
        flag=1;
      }
      delay(1500);
      state=3;
      stateStop=1;
    }
    // if the state is 'B' the motor will Reverse
    else if (state == 'B') 
    {
      drive_backward();
      if(flag == 0)
      {
        Serial.println("Reverse!");
        flag=1;
      }
    }
    }
    //For debugging purpose
    //Serial.println(state);

 
