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

struct TextureCoordinate {
    F32 U;
    F32 V;
};

struct Vertex {
    Position position;
    Color color;
    TextureCoordinate textureCoordinate;

    void SetPosition(F32 x, F32 y) {
        position.x = x;
        position.y = y;
    }

    void SetColor(U8 r, U8 g, U8 b, U8 a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void SetTextureCoordinate(F32 u, F32 v) {
        textureCoordinate.U = u;
        textureCoordinate.V = v;
    }
};
