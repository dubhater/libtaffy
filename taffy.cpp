#include <cstdint>


typedef struct {
    int width[4];
    int height[4];

    const void *srcp[4];
    void *dstp[4];

    int src_stride[4];
    int dst_stride[4];
} bleh;




template <typename T>
static void pack_4444(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T **srcp = (const T **)args->srcp;
    T *dstp = (T *)args->dstp[0];

    int src_stride[4] = args->src_stride;
    int dst_stride = args->dst_stride[0];

    if (srcp[0] == NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[x * 4 + 0] = 0;
                dstp[x * 4 + 1] = srcp[1][x];
                dstp[x * 4 + 2] = srcp[2][x];
                dstp[x * 4 + 3] = srcp[3][x];
            }

            srcp[1] += src_stride[1] / sizeof(T);
            srcp[2] += src_stride[2] / sizeof(T);
            srcp[3] += src_stride[3] / sizeof(T);

            dstp += dst_stride / sizeof(T);
        }
    } else if (srcp[3] == NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[x * 4 + 0] = srcp[0][x];
                dstp[x * 4 + 1] = srcp[1][x];
                dstp[x * 4 + 2] = srcp[2][x];
                dstp[x * 4 + 3] = 0;
            }

            srcp[0] += src_stride[0] / sizeof(T);
            srcp[1] += src_stride[1] / sizeof(T);
            srcp[2] += src_stride[2] / sizeof(T);

            dstp += dst_stride / sizeof(T);
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[x * 4 + 0] = srcp[0][x];
                dstp[x * 4 + 1] = srcp[1][x];
                dstp[x * 4 + 2] = srcp[2][x];
                dstp[x * 4 + 3] = srcp[3][x];
            }

            srcp[0] += src_stride[0] / sizeof(T);
            srcp[1] += src_stride[1] / sizeof(T);
            srcp[2] += src_stride[2] / sizeof(T);
            srcp[3] += src_stride[3] / sizeof(T);

            dstp += dst_stride / sizeof(T);
        }
    }
}


template <typename T>
static void unpack_4444(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T *srcp = (const T *)args->srcp[0];
    T **dstp = (T **)args->dstp;

    int src_stride = args->src_stride[0];
    int dst_stride[4] = args->dst_stride;

    if (dstp[0] == NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[1][x] = srcp[x * 4 + 1];
                dstp[2][x] = srcp[x * 4 + 2];
                dstp[3][x] = srcp[x * 4 + 3];
            }

            srcp += src_stride / sizeof(T);

            dstp[1] += dst_stride[1] / sizeof(T);
            dstp[2] += dst_stride[2] / sizeof(T);
            dstp[3] += dst_stride[3] / sizeof(T);
        }
    } else if (dstp[3] == NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[0][x] = srcp[x * 4 + 0];
                dstp[1][x] = srcp[x * 4 + 1];
                dstp[2][x] = srcp[x * 4 + 2];
            }

            srcp += src_stride / sizeof(T);

            dstp[0] += dst_stride[0] / sizeof(T);
            dstp[1] += dst_stride[1] / sizeof(T);
            dstp[2] += dst_stride[2] / sizeof(T);
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstp[0][x] = srcp[x * 4 + 0];
                dstp[1][x] = srcp[x * 4 + 1];
                dstp[2][x] = srcp[x * 4 + 2];
                dstp[3][x] = srcp[x * 4 + 3];
            }

            srcp += src_stride / sizeof(T);

            dstp[0] += dst_stride[0] / sizeof(T);
            dstp[1] += dst_stride[1] / sizeof(T);
            dstp[2] += dst_stride[2] / sizeof(T);
            dstp[3] += dst_stride[3] / sizeof(T);
        }
    }
}

// =================================================

template <typename T>
static void pack_444(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T **srcp = (const T **)args->srcp;
    T *dstp = (T *)args->dstp[0];

    int src_stride[4] = args->src_stride;
    int dst_stride = args->dst_stride[0];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            dstp[x * 3 + 0] = srcp[0][x];
            dstp[x * 3 + 1] = srcp[1][x];
            dstp[x * 3 + 2] = srcp[2][x];
        }

        srcp[0] += src_stride[0] / sizeof(T);
        srcp[1] += src_stride[1] / sizeof(T);
        srcp[2] += src_stride[2] / sizeof(T);

        dstp += dst_stride / sizeof(T);
    }
}


template <typename T>
static void unpack_444(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T *srcp = (const T *)args->srcp[0];
    T **dstp = (T **)args->dstp;

    int src_stride = args->src_stride[0];
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            dstp[0][x] = srcp[x * 3 + 0];
            dstp[1][x] = srcp[x * 3 + 1];
            dstp[2][x] = srcp[x * 3 + 2];
        }

        srcp += src_stride / sizeof(T);

        dstp[0] += dst_stride[0] / sizeof(T);
        dstp[1] += dst_stride[1] / sizeof(T);
        dstp[2] += dst_stride[2] / sizeof(T);
    }
}

// =================================================

template <typename T>
static void pack_422(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T **srcp = (const T **)args->srcp;
    T *dstp = (T *)args->dstp[0];

    int src_stride[4] = args->src_stride;
    int dst_stride = args->dst_stride[0];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            dstp[x * 2 + 0] = srcp[0][x];
            dstp[x * 2 + 1] = srcp[1][x / 2];
            dstp[x * 2 + 2] = srcp[0][x + 1];
            dstp[x * 2 + 3] = srcp[2][x / 2];
        }

        srcp[0] += src_stride[0] / sizeof(T);
        srcp[1] += src_stride[1] / sizeof(T);
        srcp[2] += src_stride[2] / sizeof(T);

        dstp += dst_stride / sizeof(T);
    }
}


template <typename T>
static void unpack_422(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T *srcp = (const T *)args->srcp[0];
    T **dstp = (T **)args->dstp;

    int src_stride = args->src_stride[0];
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            dstp[0][x] = srcp[x * 2 + 0];
            dstp[1][x / 2] = srcp[x * 2 + 1];
            dstp[0][x + 1] = srcp[x * 2 + 2];
            dstp[2][x / 2] = srcp[x * 2 + 3];
        }

        srcp += src_stride / sizeof(T);

        dstp[0] += dst_stride[0] / sizeof(T);
        dstp[1] += dst_stride[1] / sizeof(T);
        dstp[2] += dst_stride[2] / sizeof(T);
    }
}

// =================================================

template <typename T>
static void pack_422_uyvy(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T **srcp = (const T **)args->srcp;
    T *dstp = (T *)args->dstp[0];

    int src_stride[4] = args->src_stride;
    int dst_stride = args->dst_stride[0];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            dstp[x * 2 + 0] = srcp[1][x / 2];
            dstp[x * 2 + 1] = srcp[0][x];
            dstp[x * 2 + 2] = srcp[2][x / 2];
            dstp[x * 2 + 3] = srcp[0][x + 1];
        }

        srcp[0] += src_stride[0] / sizeof(T);
        srcp[1] += src_stride[1] / sizeof(T);
        srcp[2] += src_stride[2] / sizeof(T);

        dstp += dst_stride / sizeof(T);
    }
}


template <typename T>
static void unpack_422_uyvy(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const T *srcp = (const T *)args->srcp[0];
    T **dstp = (T **)args->dstp;

    int src_stride = args->src_stride[0];
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            dstp[1][x / 2] = srcp[x * 2 + 0];
            dstp[0][x] = srcp[x * 2 + 1];
            dstp[2][x / 2] = srcp[x * 2 + 2];
            dstp[0][x + 1] = srcp[x * 2 + 3];
        }

        srcp += src_stride / sizeof(T);

        dstp[0] += dst_stride[0] / sizeof(T);
        dstp[1] += dst_stride[1] / sizeof(T);
        dstp[2] += dst_stride[2] / sizeof(T);
    }
}

// =================================================

template <typename T>
static void pack_nv(bleh *args) {
    int width[4] = args->width;
    int height[4] = args->height;

    const T **srcp = (const T **)args->srcp;
    T **dstp = (T **)args->dstp;

    int src_stride[4] = args->src_stride;
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height[1]; y++) {
        for (int x = 0; x < width[1]; x++) {
            dstp[1][x * 2 + 0] = srcp[1][x];
            dstp[1][x * 2 + 1] = srcp[2][x];
        }

        srcp[1] += src_stride[1] / sizeof(T);
        srcp[2] += src_stride[2] / sizeof(T);

        dstp[1] += dst_stride[1] / sizeof(T);
    }

    if (src_stride[0] == dst_stride[0]) {
        memcpy(dstp[0], srcp[0], src_stride[0] * height[0]);
    } else {
        for (int y = 0; y < height[0]; y++) {
            memcpy(dstp[0], srcp[0], width[0] * sizeof(T));
            srcp[0] += src_stride[0] / sizeof(T);
            dstp[0] += dst_stride[0] / sizeof(T);
        }
    }
}


template <typename T>
static void unpack_nv(bleh *args) {
    int width[4] = args->width;
    int height[4] = args->height;

    const T **srcp = (const T **)args->srcp;
    T **dstp = (T **)args->dstp;

    int src_stride[4] = args->src_stride;
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height[1]; y++) {
        for (int x = 0; x < width[1]; x++) {
            dstp[1][x] = srcp[1][x * 2 + 0];
            dstp[2][x] = srcp[1][x * 2 + 1];
        }

        srcp[1] += src_stride[1] / sizeof(T);

        dstp[1] += dst_stride[1] / sizeof(T);
        dstp[2] += dst_stride[2] / sizeof(T);
    }

    if (src_stride[0] == dst_stride[0]) {
        memcpy(dstp[0], srcp[0], src_stride[0] * height[0]);
    } else {
        for (int y = 0; y < height[0]; y++) {
            memcpy(dstp[0], srcp[0], width[0] * sizeof(T));
            srcp[0] += src_stride[0] / sizeof(T);
            dstp[0] += dst_stride[0] / sizeof(T);
        }
    }
}

// =================================================

void pack_px16(bleh *args) {
    pack_nv<uint16_t>(args);
}


void unpack_px16(bleh *args) {
    unpack_nv<uint16_t>(args);
}

// =================================================

void pack_px10(bleh *args) {
    int width[4] = args->width;
    int height[4] = args->height;

    const uint16_t **srcp = (const uint16_t **)args->srcp;
    uint16_t **dstp = (uint16_t **)args->dstp;

    int src_stride[4] = args->src_stride;
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height[1]; y++) {
        for (int x = 0; x < width[1]; x++) {
            dstp[1][x * 2 + 0] = srcp[1][x] << 6;
            dstp[1][x * 2 + 1] = srcp[2][x] << 6;
        }

        srcp[1] += src_stride[1] / sizeof(uint16_t);
        srcp[2] += src_stride[2] / sizeof(uint16_t);

        dstp[1] += dst_stride[1] / sizeof(uint16_t);
    }

    for (int y = 0; y < height[0]; y++) {
        for (int x = 0; x < width[0]; x++) {
            dstp[0][x] = srcp[0][x] << 6;
        }

        srcp[0] += src_stride[0] / sizeof(uint16_t);
        dstp[0] += dst_stride[0] / sizeof(uint16_t);
    }
}


void unpack_px10(bleh *args) {
    int width[4] = args->width;
    int height[4] = args->height;

    const uint16_t **srcp = (const uint16_t **)args->srcp;
    uint16_t **dstp = (uint16_t **)args->dstp;

    int src_stride[4] = args->src_stride;
    int dst_stride[4] = args->dst_stride;

    for (int y = 0; y < height[1]; y++) {
        for (int x = 0; x < width[1]; x++) {
            dstp[1][x] = srcp[1][x * 2 + 0] >> 6;
            dstp[2][x] = srcp[1][x * 2 + 1] >> 6;
        }

        srcp[1] += src_stride[1] / sizeof(uint16_t);

        dstp[1] += dst_stride[1] / sizeof(uint16_t);
        dstp[2] += dst_stride[2] / sizeof(uint16_t);
    }

    for (int y = 0; y < height[0]; y++) {
        for (int x = 0; x < width[0]; x++) {
            dstp[0][x] = srcp[0][x] >> 6;
        }

        srcp[0] += src_stride[0] / sizeof(uint16_t);
        dstp[0] += dst_stride[0] / sizeof(uint16_t);
    }
}

// =================================================

void pack_v210(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    const uint16_t **srcp = (const uint16_t **)args->srcp;
    uint32_t *dstp = (uint32_t *)args->dstp[0];

    int src_stride[4] = args->src_stride;
    // explode if it's not the same as args->dst_stride[0] ?
    int dst_stride = ((16*((width + 5) / 6) + 127) & ~127)/4;

    for (int y = 0; y < height; y++) {
        const uint16_t *yline = srcp[0];
        const uint16_t *uline = srcp[1];
        const uint16_t *vline = srcp[2];
        uint32_t *dstline = dstp;
        for (int x = 0; x < width + 5; x += 6) {
            dstline[0] = (uline[0] | (yline[0] << 10) | (vline[0] << 20));
            dstline[1] = (yline[1] | (uline[1] << 10) | (yline[2] << 20));
            dstline[2] = (vline[1] | (yline[3] << 10) | (uline[2] << 20));
            dstline[3] = (yline[4] | (vline[2] << 10) | (yline[5] << 20));
            dstline += 4;
            yline += 6;
            uline += 3;
            vline += 3;
        }
        dstp += dst_stride;
        srcp[0] += src_stride[0] / 2;
        srcp[1] += src_stride[1] / 2;
        srcp[2] += src_stride[2] / 2;
    }
}


void unpack_v210(bleh *args) {
    int width = args->width[0];
    int height = args->height[0];

    int src_stride = ((16*((width + 5) / 6) + 127) & ~127)/4;
    int dst_stride[4] = args->dst_stride;

    const uint32_t *srcp = (const uint32_t *)args->srcp[0];
    uint16_t **dstp = (uint16_t **)args->dstp;

    const uint32_t mask = 1023; // lowest 10 bits

    for (int y = 0; y < height; y++) {
        uint16_t *yline = dstp[0];
        uint16_t *uline = dstp[1];
        uint16_t *vline = dstp[2];
        const uint32_t *srcline = srcp;

        for (int x = 0; x < width + 5; x += 6) {
            uline[0] = srcline[0] & mask;
            yline[0] = (srcline[0] >> 10) & mask;
            vline[0] = (srcline[0] >> 20) & mask;

            yline[1] = srcline[1] & mask;
            uline[1] = (srcline[1] >> 10) & mask;
            yline[2] = (srcline[1] >> 20) & mask;

            vline[1] = srcline[2] & mask;
            yline[3] = (srcline[2] >> 10) & mask;
            uline[2] = (srcline[2] >> 20) & mask;

            yline[4] = srcline[3] & mask;
            vline[2] = (srcline[3] >> 10) & mask;
            yline[5] = (srcline[3] >> 20) & mask;

            srcline += 4;
            yline += 6;
            uline += 3;
            vline += 3;
        }

        srcp += src_stride;

        dstp[0] += dst_stride[0] / 2;
        dstp[1] += dst_stride[1] / 2;
        dstp[2] += dst_stride[2] / 2;
    }
}

// =================================================

void pack_4444_uint8(bleh *args) {
    pack_4444<uint8_t>(args);
}

void unpack_4444_uint8(bleh *args) {
    unpack_4444<uint8_t>(args);
}


void pack_4444_uint16(bleh *args) {
    pack_4444<uint16_t>(args);
}

void unpack_4444_uint16(bleh *args) {
    unpack_4444<uint16_t>(args);
}


void pack_4444_uint32(bleh *args) {
    pack_4444<uint32_t>(args);
}

void unpack_4444_uint32(bleh *args) {
    unpack_4444<uint32_t>(args);
}

// =================================================


void pack_444_uint8(bleh *args) {
    pack_444<uint8_t>(args);
}

void unpack_444_uint8(bleh *args) {
    unpack_444<uint8_t>(args);
}


void pack_444_uint16(bleh *args) {
    pack_444<uint16_t>(args);
}

void unpack_444_uint16(bleh *args) {
    unpack_444<uint16_t>(args);
}


void pack_444_uint32(bleh *args) {
    pack_444<uint32_t>(args);
}

void unpack_444_uint32(bleh *args) {
    unpack_444<uint32_t>(args);
}

// =================================================


void pack_422_uint8(bleh *args) {
    pack_422<uint8_t>(args);
}

void unpack_422_uint8(bleh *args) {
    unpack_422<uint8_t>(args);
}


void pack_422_uint16(bleh *args) {
    pack_422<uint16_t>(args);
}

void unpack_422_uint16(bleh *args) {
    unpack_422<uint16_t>(args);
}


void pack_422_uint32(bleh *args) {
    pack_422<uint32_t>(args);
}

void unpack_422_uint32(bleh *args) {
    unpack_422<uint32_t>(args);
}

// =================================================


void pack_422_uyvy_uint8(bleh *args) {
    pack_422_uyvy<uint8_t>(args);
}

void unpack_422_uyvy_uint8(bleh *args) {
    unpack_422_uyvy<uint8_t>(args);
}


void pack_422_uyvy_uint16(bleh *args) {
    pack_422_uyvy<uint16_t>(args);
}

void unpack_422_uyvy_uint16(bleh *args) {
    unpack_422_uyvy<uint16_t>(args);
}


void pack_422_uyvy_uint32(bleh *args) {
    pack_422_uyvy<uint32_t>(args);
}

void unpack_422_uyvy_uint32(bleh *args) {
    unpack_422_uyvy<uint32_t>(args);
}

// =================================================


void pack_nv_uint8(bleh *args) {
    pack_nv<uint8_t>(args);
}

void unpack_nv_uint8(bleh *args) {
    unpack_nv<uint8_t>(args);
}


void pack_nv_uint16(bleh *args) {
    pack_nv<uint16_t>(args);
}

void unpack_nv_uint16(bleh *args) {
    unpack_nv<uint16_t>(args);
}


void pack_nv_uint32(bleh *args) {
    pack_nv<uint32_t>(args);
}

void unpack_nv_uint32(bleh *args) {
    unpack_nv<uint32_t>(args);
}

// =================================================

