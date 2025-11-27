/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "Arduino.h"
#include <driver/ledc.h>
#include "buzzer.h"

const int buzzerPin = 40;
const int channel   = 5;

void setup_pwm_buzzer(void) {
    ledcSetup(channel, 4000, 8);        // 配置PWM通道：通道0，频率3000Hz，分辨率8位
    ledcAttachPin(buzzerPin, channel);  // 将PWM通道绑定到GPIO
}

void buzzer_sound(uint32_t frequency, uint32_t duration_ms) {
    ledcWriteTone(channel, frequency);
    ledcWrite(channel, 127);

    vTaskDelay(duration_ms / portTICK_PERIOD_MS);

    ledcWriteTone(channel, 0);
    digitalWrite(channel, 0);
}

void beep(void) {
    buzzer_sound(4000, 100);
}

void songs_of_storms_tone_1_oct_d_short(void) {
    struct {
        uint32_t freq;
        uint32_t duration;
    } notes[] = {

        {293, 180},   // D4
        {349, 180},   // F4
        {587, 450},   // D5

        {293, 180},   // D4
        {349, 180},   // F4
        {587, 450},   // D5

        {659, 400},   // E5
        {698, 200},   // F5
        {659, 180},   // E5
        {698, 180},   // F5
        {659, 180},   // E5
        {523, 180},   // C5
        {440, 400},   // A4

        {440, 300},   // A4
        {293, 300},   // D4
        {349, 200},   // F4
        {392, 200},   // G4
        {440, 600},   // A4

        {440, 300},   // A4
        {293, 300},   // D4
        {349, 200},   // F4
        {392, 200},   // G4
        {330, 600},   // E4
    };

    int num_notes = sizeof(notes) / sizeof(notes[0]);
    
    for (int i = 0; i < num_notes; i++) {
        if (notes[i].freq == 0) {
            // Rest: just delay
            vTaskDelay(notes[i].duration / portTICK_PERIOD_MS);
        } else {
            buzzer_sound(notes[i].freq, notes[i].duration);
        }
    }
}

void default_tone(void) {
    buzzer_sound(NOTE_D1, 200);
    buzzer_sound(NOTE_D5, 200);
    buzzer_sound(NOTE_D3, 200);
    buzzer_sound(NOTE_D4, 200);
}
void start_tone(void) {
    //default_tone();
    songs_of_storms_tone_1_oct_d_short();
}
