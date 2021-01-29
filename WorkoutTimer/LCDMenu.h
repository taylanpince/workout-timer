// LCD Menu controller
// Works with LiquidCrystal and LiquidCrystal_I2C
// Allows creating and controlling a basic scrolling menu system

#include <LiquidCrystal_I2C.h>


class LCDMenu {
private:


public:
    LiquidCrystal_I2C *lcd;

    LCDMenu(LiquidCrystal_I2C &lcd) : lcd(&lcd) {};
    
    void init() {
        
    };

    void update() {
        
    };
};


class LCDMenuOption {
private:


public:
    LCDMenuOption() {
        
    };
};
