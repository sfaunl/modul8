
#ifndef MODULATOR_H_
#define MODULATOR_H_

#include <complex>

typedef std::complex<float> cmplx;

typedef enum{
    MOD_BPSK,
    MOD_QPSK,
    MOD_8QAM,
    MOD_16QAM
} ModType;

typedef struct{
    int     dataLength;
    uint8_t *data;      // data [0 1]
    cmplx   *modData;   // modulated data (complex)
    uint8_t *demodData; // demodulated data [0 1]
    cmplx   *rxData;    // modulated data after channel
    
    float   noiseSNRdB; // channel noise SNR in dB
    float   bitErrorRate;
    float   symbolErrorRate;
    ModType modType;
} Mod;

int modulator_run(void *userArg);

Mod *modulator_init();

#endif /* MODULATOR_H_ */