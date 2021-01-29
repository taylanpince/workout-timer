#include "LCDTimerMenu.h"
#include "RotaryController.h"


LiquidCrystal_I2C lcd(0x27, 20, 4);

RotaryController controller = RotaryController(2, 3, 6);

LCDTimerMenu timerMenu = LCDTimerMenu(lcd, LCDTimerMenuModeCountUp);

void interruptA() {
    controller.triggerPinA();
}

void interruptB() {
    controller.triggerPinB();
}

void setup() {
    controller.init();

    attachInterrupt(0, interruptA, RISING);
    attachInterrupt(1, interruptB, RISING);

    lcd.init();

    timerMenu.init();
    
    lcd.backlight();

    Serial.begin(57600);
}

void loop() {
    RotaryControllerAction action = controller.checkState();

    if (action == RotaryActionClick) {
        if (timerMenu.timerRunning) {
            Serial.println("Pause");
            timerMenu.pauseTimer();
        } else {
            Serial.println("Resume");
            timerMenu.startTimer();
        }
    }

    timerMenu.update();
}
