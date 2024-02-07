#version 450

in vec2 position;
in vec4 color;
in vec2 textCoord;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentTextCoord;

void main() {
    // Set x and y to the position of the vertex
    gl_Position.xy = position;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    // Set the color of the vertex
    fragmentColor = color;
    fragmentPosition = position;
    fragmentTextCoord = vec2(textCoord.x, 1.0 - textCoord.y); // Invert the y-axis since OpenGL uses a different coordinate system and the texture is upside down
}
