#version 150

in vec2 position;

void main() {
    gl_Position.xy = position;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}
