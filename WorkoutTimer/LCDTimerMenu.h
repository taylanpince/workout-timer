// LCD Timer Menu controller
// Subclass of LCDMenu that shows large numbers
// Has 3 modes: Count Up, Count Down and Configure

#include "LCDMenu.h"


enum LCDTimerMenuMode {
    LCDTimerMenuModeCountUp = 0,
    LCDTimerMenuModeCountDown = 1,
    LCDTimerMenuModeConfigure = 2,
};


class LCDTimerMenu : public LCDMenu {
public:
    LCDTimerMenuMode mode;
    bool timerRunning = false;

    LCDTimerMenu(LiquidCrystal_I2C &lcd, LCDTimerMenuMode mode) : LCDMenu(lcd) {
        this->mode = mode;
    };

    void init() {
        lcd->createChar(1, bar1);
        lcd->createChar(2, bar2);
        lcd->createChar(3, bar3);
        lcd->createChar(4, bar4);
        lcd->createChar(5, bar5);
        lcd->createChar(6, bar6);
        lcd->createChar(7, bar7);
        lcd->createChar(8, bar8);

        LCDMenu::init();
    };

    void resetTimer() {
        timerRunning = false;
        startTime = 0;
        countSeconds = 0;

        printTime(0);
    };

    void startTimer() {
        if (timerRunning) {
            return;
        }

        timerRunning = true;

        startTime = millis();
    };

    void pauseTimer() {
        if (!timerRunning) {
            return;
        }

        timerRunning = false;
    };

    void update() {
        if (!timerRunning) {
            return;
        }

        currentTime = millis();

        unsigned long interval = currentTime - startTime;

        if (interval > 1000) {
            countSeconds = interval / 1000;

            printTime(countSeconds);
        }
    };

    void printTime(uint32_t seconds) {
        uint8_t mins = seconds / 60;
        uint8_t secs = seconds % 60;

        printNumber(mins / 10, 1);
        printNumber(mins % 10, 4);
        printSeparator(7, (secs % 2 == 0));
        printNumber(secs / 10, 8);
        printNumber(secs % 10, 11);
    };

private:
    const char bar1[8] = {B11100, B11110, B11110, B11110, B11110, B11110, B11110, B11100};
    const char bar2[8] = {B00111, B01111, B01111, B01111, B01111, B01111, B01111, B00111};
    const char bar3[8] = {B11111, B11111, B00000, B00000, B00000, B00000, B11111, B11111};
    const char bar4[8] = {B11110, B11100, B00000, B00000, B00000, B00000, B11000, B11100};
    const char bar5[8] = {B01111, B00111, B00000, B00000, B00000, B00000, B00011, B00111};
    const char bar6[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B11111, B11111};
    const char bar7[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00111, B01111};
    const char bar8[8] = {B11111, B11111, B00000, B00000, B00000, B00000, B00000, B00000};

    unsigned long currentTime = 0.0;
    unsigned long startTime = 0.0;
    uint32_t countSeconds = 0;

    void printNumber0(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(8);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(2);
        lcd->write(6);
        lcd->write(1);
    }

    void printNumber1(int col) {
        lcd->setCursor(col, 0);
        lcd->write(32);
        lcd->write(32);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(32);
        lcd->write(32);
        lcd->write(1);
    }

    void printNumber2(int col) {
        lcd->setCursor(col, 0);
        lcd->write(5);
        lcd->write(3);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(2);
        lcd->write(6);
        lcd->write(6);
    }

    void printNumber3(int col) {
        lcd->setCursor(col, 0);
        lcd->write(5);
        lcd->write(3);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(7);
        lcd->write(6);
        lcd->write(1); 
    }

    void printNumber4(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(6);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(32);
        lcd->write(32);
        lcd->write(1);
    }

    void printNumber5(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(3);
        lcd->write(4);
        lcd->setCursor(col, 1);
        lcd->write(7);
        lcd->write(6);
        lcd->write(1);
    }

    void printNumber6(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(3);
        lcd->write(4);
        lcd->setCursor(col, 1);
        lcd->write(2);
        lcd->write(6);
        lcd->write(1);
    }

    void printNumber7(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(8);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(32);
        lcd->write(32);
        lcd->write(1);
    }

    void printNumber8(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(3);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(2);
        lcd->write(6);
        lcd->write(1);
    }

    void printNumber9(int col) {
        lcd->setCursor(col, 0);
        lcd->write(2);
        lcd->write(3);
        lcd->write(1);
        lcd->setCursor(col, 1);
        lcd->write(7);
        lcd->write(6);
        lcd->write(1);
    }

    void printNumber(int value, int col) {
        if (value == 0) {
            printNumber0(col);
        } if (value == 1) {
            printNumber1(col);
        } if (value == 2) {
            printNumber2(col);
        } if (value == 3) {
            printNumber3(col);
        } if (value == 4) {
            printNumber4(col);
        } if (value == 5) {
            printNumber5(col);
        } if (value == 6) {
            printNumber6(col);
        } if (value == 7) {
            printNumber7(col);
        } if (value == 8) {
            printNumber8(col);
        } if (value == 9) {
            printNumber9(col);
        }
    }

    void printSeparator(int col, bool visible) {
        lcd->setCursor(col, 0);
        lcd->write(visible ? 6 : 32);
        lcd->setCursor(col, 1); 
        lcd->write(visible ? 8 : 32);
    }
};
