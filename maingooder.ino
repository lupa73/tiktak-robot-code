#include <CrcLib.h>

#define LF CRC_PWM_1
#define RF CRC_PWM_2
#define BL CRC_PWM_3
#define BR CRC_PWM_4
#define ARMSERVO CRC_DIG_4
#define PUL CRC_PWM_6
#define ARMROT CRC_PWM_7


using namespace Crc; 

/* int mode = 0;

int vitesse = 0;

int modes[] = {0, 25, 70, 127}; // 4 modes: potentiometer (as 0), low, medium, high, ultra-high

int ballstatus = 0;  */

/* bool armstate = HIGH;

 unsigned long x = 0; */

void setup() {
  CrcLib::Initialize();
  Serial.begin(9600); //Utilise (2000000), mieux que (9600)

  CrcLib::InitializePwmOutput(LF);
  CrcLib::InitializePwmOutput(RF);
  CrcLib::InitializePwmOutput(BL);
  CrcLib::InitializePwmOutput(BR);
  CrcLib::InitializePwmOutput(ARMROT);
  CrcLib::InitializePwmOutput(PUL);
  CrcLib::SetDigitalPinMode(ARMSERVO, OUTPUT);

/*   CrcLib::SetDigitalPinMode(TOPHATCH, OUTPUT);
  CrcLib::SetDigitalPinMode(BOTHATCH, OUTPUT);
  CrcLib::SetDigitalPinMode(IN1, OUTPUT);
  CrcLib::SetDigitalPinMode(IN2, OUTPUT);
  CrcLib::SetDigitalPinMode(IN3, OUTPUT);
  CrcLib::SetDigitalPinMode(IN4, OUTPUT); */

}

void loop() {
  CrcLib::Update();
  Serial.println();

  if (CrcLib::IsCommValid()) {
    // Put ALL main code in here. This way, main.ino will only run if CrcConnect is online, connected and functional.


    int j1xpos = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
    int j1ypos = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);

    int j2xpos = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);
    int j2ypos = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);

    bool select = CrcLib::ReadDigitalChannel(BUTTON::SELECT);
    bool start = CrcLib::ReadDigitalChannel(BUTTON::START);
    
    int l2trigger = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
    int r2trigger = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);

    bool lbumper = CrcLib::ReadDigitalChannel(BUTTON::L1);
    bool rbumper = CrcLib::ReadDigitalChannel(BUTTON::R1);

    bool ybutton = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
    bool bbutton = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
    bool abutton = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);

    int individual = CrcLib::ReadDigitalChannel(BUTTON::ARROW_UP);
    int full = CrcLib::ReadDigitalChannel(BUTTON::ARROW_DOWN);

    CrcLib::MoveHolonomic(ANALOG::JOYSTICK1_Y, ANALOG::JOYSTICK1_X, ANALOG::JOYSTICK2_X, LF, BL, RF, BR);

       if(r2trigger > 0) {
          pullyup(80);
        }else if (l2trigger > 0) {
          pullydown(80);
        }else{
        CrcLib::SetPwmOutput(PUL, 0);
        }      

      if(ybutton == HIGH){
        CrcLib::SetPwmOutput(ARMROT, 80);
      }else if(abutton == HIGH){
        CrcLib::SetPwmOutput(ARMROT, -80);
      }else{
        CrcLib::SetPwmOutput(ARMROT, 0);
      }
     

      if(rbumper == HIGH){
        armopen(80);
      }else if(lbumper == HIGH){
        armclose(80);
      }

    CrcLib::Update();
  
  } else {
    Serial.print("No controller connected, file will not work.");
    CrcLib::Update();
  }
}
void armrotate180(){
  CrcLib::SetPwmOutput(ARMROT, -30);
}

void armrotate90(){
  CrcLib::SetPwmOutput(ARMROT, 30);
}

void armopen(int speed){
  CrcLib::SetDigitalOutput(ARMSERVO, HIGH);
  CrcLib::Update();
}

void armclose(int speed){
  CrcLib::SetDigitalOutput(ARMSERVO, LOW);
  CrcLib::Update();
}

void pullyup(int speed){
  CrcLib::SetPwmOutput(PUL, speed);
  CrcLib::Update();
}
void pullydown(int speed){
  CrcLib::SetPwmOutput(PUL, -speed);
  CrcLib::Update();
}

void turnranalog(int t) {
  CrcLib::SetPwmOutput(LF, t);
  CrcLib::SetPwmOutput(BL, t);
  CrcLib::SetPwmOutput(RF, -t);
  CrcLib::SetPwmOutput(BR, -t);
  CrcLib::Update();
}

void turnlanalog(int t) {
  CrcLib::SetPwmOutput(LF, -t);
  CrcLib::SetPwmOutput(BL, -t);
  CrcLib::SetPwmOutput(RF, t);
  CrcLib::SetPwmOutput(BR, t);
  CrcLib::Update();
}

void forwardanalog(int t) {
  CrcLib::SetPwmOutput(LF, t);
  CrcLib::SetPwmOutput(BL, t);
  CrcLib::SetPwmOutput(RF, t);
  CrcLib::SetPwmOutput(BR, t);
  CrcLib::Update();
}

void backwardanalog(int t) {
  CrcLib::SetPwmOutput(LF, -t);
  CrcLib::SetPwmOutput(BL, -t);
  CrcLib::SetPwmOutput(RF, -t);
  CrcLib::SetPwmOutput(BR, -t);
  CrcLib::Update();
}

void forward(int vitesse) {
  CrcLib::SetPwmOutput(LF, vitesse);
  CrcLib::SetPwmOutput(BL, vitesse);
  CrcLib::SetPwmOutput(RF, vitesse);
  CrcLib::SetPwmOutput(BR, vitesse);
  CrcLib::Update();
}

void backward(int vitesse) {
  CrcLib::SetPwmOutput(LF, -vitesse);
  CrcLib::SetPwmOutput(BL, -vitesse);
  CrcLib::SetPwmOutput(RF, -vitesse);
  CrcLib::SetPwmOutput(BR, -vitesse);
  CrcLib::Update();
}

void turnr(int vitesse) {
  CrcLib::SetPwmOutput(LF, vitesse);
  CrcLib::SetPwmOutput(BL, vitesse);
  CrcLib::SetPwmOutput(RF, -vitesse);
  CrcLib::SetPwmOutput(BR, -vitesse);
  CrcLib::Update();
}

void turnl(int vitesse) {
  CrcLib::SetPwmOutput(LF, -vitesse);
  CrcLib::SetPwmOutput(BL, -vitesse);
  CrcLib::SetPwmOutput(RF, vitesse);
  CrcLib::SetPwmOutput(BR, vitesse);
  CrcLib::Update();
}

void latr(int vitesse) {
  CrcLib::SetPwmOutput(LF, vitesse);
  CrcLib::SetPwmOutput(BL, -vitesse);
  CrcLib::SetPwmOutput(RF, -vitesse);
  CrcLib::SetPwmOutput(BR, vitesse);
  CrcLib::Update();
}

void latl(int vitesse) {
  CrcLib::SetPwmOutput(LF, -vitesse);
  CrcLib::SetPwmOutput(BL, vitesse);
  CrcLib::SetPwmOutput(RF, vitesse);
  CrcLib::SetPwmOutput(BR, -vitesse);
  CrcLib::Update();
}

void done() {
  CrcLib::SetPwmOutput(LF, 0);
  CrcLib::SetPwmOutput(BL, 0);
  CrcLib::SetPwmOutput(RF, 0);
  CrcLib::SetPwmOutput(BR, 0);
  CrcLib::SetPwmOutput(ARMSERVO, 0);
  CrcLib::SetPwmOutput(PUL,0);
  CrcLib::SetPwmOutput(ARMROT, 0);
  CrcLib::Update();
}

void wait(int a) {
  CrcLib::Update();
  unsigned long x = millis();
  unsigned long y = x + a;

  while (x < y) {
    CrcLib::Update();
    x = millis();
  };

};

void waitfast(int a) {
  CrcLib::Update();
  unsigned long x = micros();
  unsigned long y = x + a;

  while (x < y) {
    CrcLib::Update();
    x = micros();
  };

};
// Functions here? Or maybe a library....
