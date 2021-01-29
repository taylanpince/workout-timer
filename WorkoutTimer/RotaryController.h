// Rotary Encoder controller
// Supports interrupt-driven encoder events
// Monitors click and double click events


enum RotaryControllerAction {
    RotaryActionNone = 0,
    RotaryActionForwards = 1,
    RotaryActionBackwards = 2,
    RotaryActionClick = 3,
    RotaryActionDoubleClick = 4,
    RotaryActionPress = 5,
};


class RotaryController {
private:
    uint8_t encoderPinA;
    uint8_t encoderPinB;
    uint8_t buttonPin;

    volatile byte aFlag = 0;
    volatile byte bFlag = 0;
    volatile byte encoderPos = 0;
    volatile byte oldEncPos = 0;
    volatile byte reading = 0;

    uint8_t buttonState = HIGH;
    uint8_t lastButtonState = HIGH;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

public:
    RotaryController(uint8_t encoderPinA, uint8_t encoderPinB, uint8_t buttonPin) {
        this->encoderPinA = encoderPinA;
        this->encoderPinB = encoderPinB;
        this->buttonPin = buttonPin;
    };

    void init() {
        pinMode(encoderPinA, INPUT_PULLUP);
        pinMode(encoderPinB, INPUT_PULLUP);
        pinMode(buttonPin, INPUT_PULLUP);

        pinMode(buttonPin, INPUT);
        digitalWrite(buttonPin, HIGH);
    };

    RotaryControllerAction checkState() {
        // Update encoder state
        if (oldEncPos != encoderPos) {
            if (oldEncPos > encoderPos) {
                // Move forward
                return RotaryActionForwards;
            } else {
                // Move backwards
                return RotaryActionBackwards;
            }

            oldEncPos = encoderPos;
        }

        // Check button state
        uint8_t newButtonState = digitalRead(buttonPin);

        if (lastButtonState != newButtonState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (newButtonState != buttonState) {
                buttonState = newButtonState;

                if (newButtonState == LOW) {
                    // Button clicked
                    return RotaryActionClick;
                }
            }
        }

        lastButtonState = newButtonState;

        return RotaryActionNone;
    }

    void triggerPinA() {
        cli(); //stop interrupts happening before we read pin values

        reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
        
        if (reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
            encoderPos--; //decrement the encoder's position count
            bFlag = 0; //reset flags for the next turn
            aFlag = 0; //reset flags for the next turn
        } else if (reading == B00000100) {
            bFlag = 1;
        } //signal that we're expecting pinB to signal the transition to detent from free rotation

        sei(); //restart interrupts
    };

    void triggerPinB() {
      cli(); //stop interrupts happening before we read pin values

      reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values

      if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
        encoderPos++; //increment the encoder's position count
        bFlag = 0; //reset flags for the next turn
        aFlag = 0; //reset flags for the next turn
      } else if (reading == B00001000) {
        aFlag = 1;
      } //signal that we're expecting pinA to signal the transition to detent from free rotation

      sei(); //restart interrupts
    };
};
