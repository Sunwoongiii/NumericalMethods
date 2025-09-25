#ifndef MULLER_H
#define MULLER_H
#ifdef __cplusplus
extern "C" {
#endif
float muller(float (*func)(float), float x1, float x2, float xacc);
long  get_muller_iterations(void);
#ifdef __cplusplus
}
#endif
#endif
