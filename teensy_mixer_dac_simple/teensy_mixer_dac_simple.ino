#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// GUItool: begin automatically generated code

#define   PIN_AN_FREQ       33
#define   PIN_AN_AMPL       34
#define   PIN_AN_PHASE      35

AudioSynthWaveformSine   sine1;          //xy=70,304
AudioSynthWaveformSine   sine2;          //xy=87,405
AudioSynthNoiseWhite     noise1;         //xy=100,194
AudioMixer4              mixer1;         //xy=255,240
AudioMixer4              mixer2;         //xy=268,381
AudioOutputAnalogStereo  dacs1;          //xy=499,297
AudioConnection          patchCord1(sine1, 0, mixer1, 0);
AudioConnection          patchCord2(sine2, 0, mixer2, 3);
AudioConnection          patchCord3(noise1, 0, mixer1, 1);
AudioConnection          patchCord4(noise1, 0, mixer2, 1);
AudioConnection          patchCord5(mixer1, 0, dacs1, 0);
AudioConnection          patchCord6(mixer2, 0, dacs1, 1);
// GUItool: end automatically generated code

struct sine_attribute{
  float freq;
  float amplitude;
  float phase;
};

struct sine_attribute sin_attr   = { .freq = 1000, .amplitude = 0.5, .phase = 0 };

void setup() {
  
  /* setup uart */
  Serial.begin(9600);
  Serial.println("Simple mixer/dac test");

  /* setup Synth */   
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
 
}

void loop() {
  // ADC resolution defaults to arduino (10 bits)
  // https://forum.pjrc.com/threads/41911-Teensy-3-6-ADC-resolution
  
  sin_attr.freq = 1000.0 + analogRead(PIN_AN_FREQ) * 10.0;  /* min 5 khz, max : 10k + 1024*10 = 20k */
  sin_attr.amplitude = 1.0 / 1024.0 * (float)analogRead(PIN_AN_AMPL); /* min = 0, max = 1 */
  sin_attr.phase = 1.0 / 360.0 * (float)analogRead(PIN_AN_PHASE); /* min = 0, max = 360 */

  AudioNoInterrupts();  // disable audio library momentarily
  sine1.frequency(sin_attr.freq);
  sine1.amplitude(sin_attr.amplitude);
  sine1.phase(sin_attr.phase);

  sine2.frequency(sin_attr.freq);
  sine2.amplitude(sin_attr.amplitude);
  sine2.phase(sin_attr.phase);
  AudioInterrupts();    // enable, both tones will start together

  Serial.print(sin_attr.freq, 0);
  Serial.print(" - ");
  Serial.print(sin_attr.amplitude, 2);
  Serial.print(" - ");
  Serial.print(sin_attr.phase, 0);
  Serial.println();
  
  delay(500);

}
