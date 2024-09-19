// 모터_전진컨트롤
int IN1 = 6;       // IN1
int IN2 = 7;      // IN2

// 모터_후진컨트롤
int IN3 = 8;      // IN3
int IN4 = 9;     // IN4

// 모터_속도컨트롤
int Left_PWM = 10;               // 왼쪽모터 속도
int Right_PWM = 5;              // 오른쪽모터 속도

// IR Sensor
const int Left_Sensor =  3;    // 왼쪽센서
const int Right_Sensor = 2;   // 오른쪽센서

int Left_Sensor_Value;        // 검은색:1
int Right_Sensor_Value;       // 흰색:0

void setup()
{
  pinMode(IN1, OUTPUT);      // PIN 8
  pinMode(IN2, OUTPUT);     // PIN 9
  
  pinMode(IN3, OUTPUT);      // PIN 10
  pinMode(IN4, OUTPUT);     // PIN 11

  pinMode(Left_PWM, OUTPUT);            // PIN 5
  pinMode(Right_PWM, OUTPUT);           // PIN 6
  
  pinMode(Left_Sensor, INPUT);          // 왼쪽센서
  pinMode(Right_Sensor, INPUT);         // 오른쪽센서
}

// 전진
void go() {
  digitalWrite(IN1, HIGH);   // 왼쪽모터   전진_정지
  digitalWrite(IN3, HIGH);  // 오론쪽모터 전진_정지
  
  digitalWrite(IN2, LOW);    // 왼쪽모터   후진_회전
  digitalWrite(IN4, LOW);   // 오른쪽모터 후진_회전
  
  analogWrite(Left_PWM, 125);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 125);          // PWM값(0~255), 모터 회전속도 조절
  delay(5);
}

// 후진
void back() {
  digitalWrite(IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(IN3, LOW);   // 오론쪽모터 전진_정지
  
  digitalWrite(IN2, HIGH);   // 왼쪽모터   후진_회전
  digitalWrite(IN4, HIGH);  // 오른쪽모터 후진_회전
  
  analogWrite(Left_PWM, 125);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 125);          // PWM값(0~255), 모터 회전속도 조절
  
}

// 정지
void brake() {
  digitalWrite(IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(IN2, LOW);   // 오론쪽모터 전진_정지
  
  digitalWrite(IN3, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(IN4, LOW);   // 오른쪽모터 후진_정지
  //delay(5);  
}

// 좌회전
void turn_left(){
  digitalWrite(IN3, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(IN1, HIGH);  // 오론쪽모터 전진_회전
  
  digitalWrite(IN2, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(IN4, LOW);   // 오른쪽모터 후진_정지

  analogWrite(Right_PWM, 125);           // PWM값(0~255), 모터 회전속도 조절
  //delay(5);
}

// 우회전
void turn_right() {
  digitalWrite(IN3, HIGH);   // 왼쪽모터   전진_회전
  digitalWrite(IN1, LOW);   // 오론쪽모터 전진_정지
  
  digitalWrite(IN2, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(IN4, LOW);   // 오른쪽모터 후진_정지

  analogWrite(Left_PWM, 125);           // PWM값(0~255), 모터 회전속도 조절
  //delay(5);
}

void loop()
{
  while(1)
  {

  //신호가 있으면(흰색) LOW,  신호가 없으면(검은색) HIGH
  Right_Sensor_Value = digitalRead(Right_Sensor);
  Left_Sensor_Value = digitalRead(Left_Sensor);

  // 전진: 왼쪽센서 검은색, 오른쪽센서 검은색
  if (Left_Sensor_Value == HIGH && Right_Sensor_Value == HIGH)
    go();

  // 좌회전: 왼쪽센서 검은색, 오른쪽센서 흰색
  else if (Left_Sensor_Value == HIGH & Right_Sensor_Value == LOW)
    turn_left();

  // 우회전: 왼쪽센서 흰색, 오른쪽센서 검은색
  else if (Left_Sensor_Value == LOW & Right_Sensor_Value == HIGH) 
    turn_right();

  // 정지: 왼쪽센서 흰색, 오른쪽센서 흰색
  else
    back();
  }
}
