#version 150

in vec2 position;
in vec4 color;

out vec4 fragmentColor;
out vec2 fragmentPosition;

void main() {
    // Set x and y to the position of the vertex
    gl_Position.xy = position;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    // Set the color of the vertex
    fragmentColor = color;
    fragmentPosition = position;
}
