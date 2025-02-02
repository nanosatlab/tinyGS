#include "RFM95.h"
#if !defined(RADIOLIB_EXCLUDE_RFM9X)

RFM95::RFM95(Module* mod) : SX1278(mod) {

}

int16_t RFM95::begin(float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain) {
  // execute common part
  int16_t state = SX127x::begin(RFM9X_CHIP_VERSION_OFFICIAL, syncWord, preambleLength);
  if(state == ERR_CHIP_NOT_FOUND) {
    // SX127X_REG_VERSION might be set 0x12
    state = SX127x::begin(RFM9X_CHIP_VERSION_UNOFFICIAL, syncWord, preambleLength);
    RADIOLIB_ASSERT(state);
  } else if(state != ERR_NONE) {
    // some other error
    return(state);
  }
  RADIOLIB_DEBUG_PRINTLN(F("M\tSX1278"));
  RADIOLIB_DEBUG_PRINTLN(F("M\tRFM95"));

  // configure publicly accessible settings
  state = setFrequency(freq);
  RADIOLIB_ASSERT(state);

  state = setBandwidth(bw);
  RADIOLIB_ASSERT(state);

  state = setSpreadingFactor(sf);
  RADIOLIB_ASSERT(state);

  state = setCodingRate(cr);
  RADIOLIB_ASSERT(state);

  state = setOutputPower(power);
  RADIOLIB_ASSERT(state);

  state = setGain(gain);

  return(state);
}

int16_t RFM95::setFrequency(float freq) {
  RADIOLIB_CHECK_RANGE(freq, 862.0, 1020.0, ERR_INVALID_FREQUENCY);

  // set frequency
  return(SX127x::setFrequencyRaw(freq));
}

#endif
