/// @author gm
/// @copyright gm 2018
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Lesser Public License for more details.
///
/// You should have received a copy of the GNU Lesser Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=288,286
AudioSynthWaveformModulated waveformMod1;   //xy=488,286
AudioOutputUSB           usb1;           //xy=717,303
AudioOutputI2S           i2s1;           //xy=780,420
AudioConnection          patchCord1(dc1, 0, waveformMod1, 0);
AudioConnection          patchCord2(waveformMod1, 0, usb1, 0);
AudioConnection          patchCord3(waveformMod1, 0, usb1, 1);
AudioConnection          patchCord4(waveformMod1, 0, i2s1, 0);
AudioConnection          patchCord5(waveformMod1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=336,538
// GUItool: end automatically generated code

constexpr float c_modRange = 8.0;
// log(5)
constexpr float c_factor = c_modRange * 0.69897000433601880478626110527551;
constexpr float c_baseFreq = 220.0;

float computeLevelFromExpectedPitch(const float expected, const float base) {
  return log(expected / base) / c_factor;
}

void setup() {
  AudioMemory(16);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.25);

  waveformMod1.begin(0.5, c_baseFreq, WAVEFORM_SINE);
  waveformMod1.frequencyModulation(c_modRange);

  dc1.amplitude(1.0);
}

void loop() {
  if (Serial.available()) {
    const String valueStr = Serial.readString();
    const float value = valueStr.toFloat();
    //Serial.println(value);
    //dc1.amplitude(value);
    const float level = computeLevelFromExpectedPitch(value, c_baseFreq);
    Serial.println(level);
    dc1.amplitude(level);
  }
}

