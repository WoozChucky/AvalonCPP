#pragma once

#include <Common/Types.h>

struct Position {
    Position() : x(0), y(0) {}
    Position(F32 x, F32 y) : x(x), y(y) {}
    F32 x;
    F32 y;
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) {}
    ColorRGBA8(U8 r, U8 g, U8 b, U8 a) : r(r), g(g), b(b), a(a) {}
    U8 r;
    U8 g;
    U8 b;
    U8 a;
};

struct TextureCoordinate {
    TextureCoordinate() : U(0), V(0) {}
    TextureCoordinate(F32 u, F32 v) : U(u), V(v) {}
    F32 U;
    F32 V;
};

struct Vertex {
    Position position;
    ColorRGBA8 color;
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
