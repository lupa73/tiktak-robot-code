#include <CrcLib.h>

#define LF CRC_PWM_1
#define RF CRC_PWM_2
#define BL CRC_PWM_3
#define BR CRC_PWM_4
#define PUL = CRC_PWM_5
#define RSERVO CRC_PWM_6
#define CLSERVO CRC_PWM_7  // left, right claw servos respectively
#define CRSERVO CRC_PWM_8


void setup() {
  // put your setup code here, to run once:
  CrcLib::Initialize();
  Serial.begin(2000000);

  CrcLib::InitializePwmOutput(LF);
  CrcLib::InitializePwmOutput(RF);
  CrcLib::InitializePwmOutput(BL);
  CrcLib::InitializePwmOutput(BR);
  CrcLib::InitializePwmOutput(PUL);
  CrcLib::InitializePwmOutput(RSERVO);
  CrcLib::InitializePwmOutput(CLSERVO);
  CrcLib::InitializePwmOutput(CRSERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  CrcLib::Update();
  Serial.println();

  if (CrcLib::IsCommValid()) {
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

    if (r2trigger > 0) {
      pullyup(80);
    } else if (l2trigger > 0) {
      pullydown(80);
    } else {
      CrcLib::SetPwmOutput(PUL, 0);
    }

    if (ybutton == HIGH) {
      armRotateRight();
    } else {
      armRotateLeft();
    }

    if (rbumper == HIGH) {
      armopen(80);
    } else if (lbumper == HIGH) {
      armclose(80);
    }

    CrcLib::Update();

  } else {
    Serial.print("No controller connected, file will not work.");
    CrcLib::Update();
  }
}


void armRotateRight() {
  CrcLib::SetPwmOutput(RSERVO, 500)
}

void armRotateLeft() {
  CrcLib::SetPwmOutput(RSERVO, 2500)
}

void clawClose() {
  CrcLib::SetPwmOutput(CLSERVO, 2500);
  CrcLib::SetPwmOutput(CRSERVO, 500);
  CrcLib::Update();
}

void clawOpen() {
  CrcLib::SetPwmOutput(CLSERVO, 500);
  CrcLib::SetPwmOutput(CRSERVO, 2500);
  CrcLib::Update();
  
}

void pullyup(int speed) {
  CrcLib::SetPwmOutput(PUL, speed);
  CrcLib::Update();
}

void pullydown(int speed) {
  CrcLib::SetPwmOutput(PUL, -speed);
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
}

void waitfast(int a) {
  CrcLib::Update();
  unsigned long x = micros();
  unsigned long y = x + a;

  while (x < y) {
    CrcLib::Update();
    x = micros();
  };
}
