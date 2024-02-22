#pragma once

#include <Common/Types.h>
#include <random>

struct Position {
    Position() : x(0), y(0) {}
    Position(F32 x, F32 y) : x(x), y(y) {}
    F32 x;
    F32 y;
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) {}
    ColorRGBA8(U8 r, U8 g, U8 b, U8 a) : r(r), g(g), b(b), a(a) {}

    static ColorRGBA8 White() { return ColorRGBA8(255, 255, 255, 255); }
    static ColorRGBA8 Black() { return ColorRGBA8(0, 0, 0, 255); }
    static ColorRGBA8 Red() { return ColorRGBA8(255, 0, 0, 255); }
    static ColorRGBA8 Green() { return ColorRGBA8(0, 255, 0, 255); }
    static ColorRGBA8 Blue() { return ColorRGBA8(0, 0, 255, 255); }
    static ColorRGBA8 Yellow() { return ColorRGBA8(255, 255, 0, 255); }
    static ColorRGBA8 Magenta() { return ColorRGBA8(255, 0, 255, 255); }
    static ColorRGBA8 Cyan() { return ColorRGBA8(0, 255, 255, 255); }
    static ColorRGBA8 Gray() { return ColorRGBA8(128, 128, 128, 255); }
    static ColorRGBA8 Orange() { return ColorRGBA8(255, 165, 0, 255); }
    static ColorRGBA8 Purple() { return ColorRGBA8(128, 0, 128, 255); }
    static ColorRGBA8 Pink() { return ColorRGBA8(255, 192, 203, 255); }
    static ColorRGBA8 Brown() { return ColorRGBA8(165, 42, 42, 255); }
    static ColorRGBA8 Olive() { return ColorRGBA8(128, 128, 0, 255); }
    static ColorRGBA8 Teal() { return ColorRGBA8(0, 128, 128, 255); }
    static ColorRGBA8 Navy() { return ColorRGBA8(0, 0, 128, 255); }
    static ColorRGBA8 Transparent() { return ColorRGBA8(0, 0, 0, 0); }
    static ColorRGBA8 Random() {
        return ColorRGBA8::Random(255);
    }
    static ColorRGBA8 Random(U8 a = 255) {
        std::random_device rd;
        // Create a Mersenne Twister random number generator
        std::mt19937 gen(rd());
        // Create a uniform distribution over the range [0, 255]
        std::uniform_int_distribution<short> distribution(0, 255);
        return ColorRGBA8(distribution(gen), distribution(gen), distribution(gen), a);
    }


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
