#pragma once

#include <Common/Types.h>

struct Vertex {
    struct {
        F32 x;
        F32 y;
    } position;
    struct {
        U8 r;
        U8 g;
        U8 b;
        U8 a;
    } color;
};
