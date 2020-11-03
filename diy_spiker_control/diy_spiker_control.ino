/* DIY Spiker unit controller - v1.0
    10/26/2020:
    - Complete rewrite to match new hardware specifications
      with no code reuse. 
    - Optimized for high-performance analog readings.
    - Compatible with Arduino Uno and Arduino Nano.
*/


#define EMG_INPUT_PIN A0            // DO NOT CHANGE, optimizations for A0 port only
#define TRIGGER_HIGH 450            // High limit for trigger, adjust to change false-trigger rejection
#define TRIGGER_LOW 150             // Low limit for trigger, adjust to change false-trigger rejection
#define TRIGGER_WAIT_TIME_MS 50     // Delay between triggers, lower to increase speed of triggering
typedef unsigned char BYTE;

// global variables
int g_analog_level = 0;
BYTE g_logic_out = 0;


// Read analog input value and store in g_analog_level
// optimized for high-performance
inline void __attribute__((optimize("O3"))) update_reading(int *level) {

    // begin ADC conversion
    ADCSRA |= (1 << ADSC);

    // poll ADCSRA until end of conversion
    while((ADCSRA & (1 << ADSC)));

    // store analog reading
    *level = ADC;
    
    return;
}


// Process trigger (if needed)
// optimized for high-performance
inline void __attribute__((optimize("O3"))) update_output(const int level) {
    switch(g_logic_out) {
        case 0: {
            if(g_analog_level >= TRIGGER_HIGH) {
                Serial.write("T\n");                // write value and flush
                Serial.flush();
                g_logic_out = 1;
                PORTB |= 0x20;                      // toggle builtin LED pin
            }
            break;
        }
        case 1: {
            if(g_analog_level <= TRIGGER_LOW) {
                g_logic_out = 0;
                PORTB &= 0xDF;                      // toggle buitlin LED pin
                delay(TRIGGER_WAIT_TIME_MS);        // delay before next trigger
            }
            break;
        }
    }
    return;
}


void setup(void) {
    Serial.begin(9600);

    // indicator
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
   
    // setup analog input A0 for operation
    // optimized for high-performance
    ADMUX = (1 << REFS0);
    ADCSRA = 0x82;
}


// optimized for high-performance
void __attribute__((optimize("O3"), flatten)) loop(void) {
    update_reading(&g_analog_level);
    update_output(g_analog_level);
}
