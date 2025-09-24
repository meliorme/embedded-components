#ifndef __R_BUFFER_H__
#define __R_BUFFER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct {
    uint8_t *r_buf;
    uint16_t capacity;
    volatile uint16_t r_idx;
    volatile uint16_t w_idx;
}r_buf_t;

r_buf_t *r_buf_create(uint16_t capacity);
void r_buf_destroy(r_buf_t *_r);
uint16_t r_buf_read(uint8_t *data, uint16_t length, r_buf_t *_r);
uint16_t r_buf_write(uint8_t *data, uint16_t length, r_buf_t *_r);


#ifdef __cplusplus
}
#endif

#endif /* __R_BUFFER_H__ */


