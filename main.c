#include <msp430.h>

#include "music.h"

#define APP_WAIT_MODE 0
#define APP_PLAY_MODE 1

#define SPEAKER BIT7
#define SPEAKER_DIR P1DIR
#define SPEAKER_OUT P1OUT

#define BUTTON BIT3
#define BUTTON_DIR P1DIR
#define BUTTON_IN P1IN

#define PHOTOSENSOR BIT0
#define PHOTOSENSOR_DIR P1DIR
#define PHOTOSENSOR_IN P1IN

unsigned char applicationMode = APP_WAIT_MODE;
unsigned short first_measurement = 1;

void setup_timer_for_playing() {
    SPEAKER_DIR |= SPEAKER;
    SPEAKER_OUT &= ~SPEAKER;
    TACTL |= TASSEL_2 | ID_0 | MC_2 | TAIE;
    TACCTL0 |= CCIE;
    TACCTL1 |= CCIE;
    WRITE_SR(GIE);
}

void setup_photoresistor() {
    BCSCTL1 |= DIVA_1;

    /* Configure analog input */
    ADC10CTL1 = INCH_0 + ADC10DIV_0;
    ADC10CTL0 = SREF_0 + ADC10SHT_0 + ADC10ON + ADC10IE;
    ADC10AE0 |= BIT0;

    PHOTOSENSOR_DIR &= ~PHOTOSENSOR;
}
void init() {

    WDTCTL = WDTPW | WDTHOLD;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;

    BUTTON_DIR &= ~BUTTON;

    setup_timer_for_playing();
    setup_photoresistor();
    __enable_interrupt();
}

unsigned int read_photo_value() {
    ADC10CTL0 &= ~ENC;
    while(ADC10CTL1 & BUSY);
    ADC10CTL0 |= ENC + ADC10SC;
    return ADC10MEM;
}

void __attribute__((interrupt (TIMERA0_VECTOR))) timer_sound_isr() {


    // TACCTL1 &= ~CCIFG;

    if(applicationMode == APP_WAIT_MODE) {
        __delay_cycles(1000); 
        if(read_photo_value() < 600) {
            if(!first_measurement) {
                applicationMode = APP_PLAY_MODE;
            } else {
                first_measurement = 0;
            }
        }
    } else if (applicationMode == APP_PLAY_MODE) {
        TACCR0 += current_note;
        if(sound_enabled) {
            SPEAKER_OUT ^= SPEAKER;
        }
        return;
    }

    __delay_cycles(1000); 
    __bic_SR_register_on_exit(CPUOFF);
}

void __attribute__((interrupt (TIMERA1_VECTOR))) ta1_isr() {
    if(applicationMode == APP_PLAY_MODE) {
        switch(TAIV) {
            case 2: /* CCR1 */
                TACCR1 += 1000;
                ms_elapsed++;
                break;
        }
    }
}

int main() {
    init();

    for(;;) {
        if(applicationMode == APP_WAIT_MODE) {
            __bis_SR_register(CPUOFF + GIE); 
            __no_operation(); 
        } else if(applicationMode == APP_PLAY_MODE) {
            song_play();
            SPEAKER_OUT &= ~SPEAKER;
            applicationMode = APP_WAIT_MODE;
        }
    }

    return 0;
}
