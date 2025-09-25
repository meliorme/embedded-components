#include "r_buffer.h"
#include <string.h>
#include <stdlib.h>


r_buf_t *r_buf_create(uint16_t capacity)
{
    if(capacity <= 0) {
        return NULL;
    }
    r_buf_t *cb = (r_buf_t *)malloc(sizeof(r_buf_t));
    cb->r_buf = (uint8_t *)malloc(capacity * sizeof(uint8_t));
    cb->capacity = capacity;
    cb->cur_cnt = 0;
    cb->r_idx = 0;
    cb->w_idx = 0;
    
    return cb;
}

void r_buf_destroy(r_buf_t *_r)
{
    free(_r->r_buf);
    free(_r);
}

uint16_t r_buf_write(uint8_t *data, uint16_t length, r_buf_t *_r)
{
    if(_r->cur_cnt == _r->capacity) {
        return 0;
    }
    uint16_t len_tmp = (length > (_r->capacity - _r->cur_cnt)) \
                        ? (_r->capacity - _r->cur_cnt) : length;
    
    if((_r->w_idx + len_tmp) <= _r->capacity) {
        memcpy(_r->r_buf + _r->w_idx, data, len_tmp);
    } 
    else {
        uint16_t first_len = _r->capacity - _r->w_idx;
        memcpy(_r->r_buf + _r->w_idx, data, first_len);
        memcpy(_r->r_buf, data + first_len, len_tmp - first_len);
    }
    _r->w_idx = (_r->w_idx + len_tmp) & (_r->capacity - 1);
    _r->cur_cnt += len_tmp;
    
    return len_tmp;
}

uint16_t r_buf_read(uint8_t *data, uint16_t length, r_buf_t *_r)
{
    if(_r->cur_cnt == 0) {
        return 0;
    }
    uint16_t r_len = (_r->cur_cnt > length) ? length : _r->cur_cnt;
    if((_r->r_idx + r_len) <= _r->capacity) {
        memcpy(data, _r->r_buf + _r->r_idx, r_len);
    }
    else {
        uint16_t first_len = _r->capacity - _r->r_idx;
        memcpy(data, _r->r_buf + _r->r_idx, first_len);
        memcpy(data + first_len, _r->r_buf, r_len - first_len);
    }
    _r->r_idx = (_r->r_idx + r_len) & (_r->capacity - 1);
    _r->cur_cnt -= r_len;
    
    return r_len;
}

