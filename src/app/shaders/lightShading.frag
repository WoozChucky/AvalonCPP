#version 410

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentTextCoord;

out vec4 color;

void main() {

    float distance = length(fragmentTextCoord);
    color = vec4(fragmentColor.rgb, fragmentColor.a * (pow(0.01, distance) - 0.01));

}
