#pragma once

#include <Common/Types.h>

struct Position {
    F32 x;
    F32 y;
};

struct Color {
    U8 r;
    U8 g;
    U8 b;
    U8 a;
};

struct Vertex {
    Position position;
    Color color;
};
