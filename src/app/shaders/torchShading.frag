#version 410

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentTextCoord;

out vec4 color;

uniform float time;  // Add a uniform variable for time

void main() {
    // Calculate the distance from the fragment to the center (assuming the center is the torch)
    float distance = length(fragmentTextCoord);

    // Calculate a time-dependent factor to modulate the intensity of the flame
    float flameIntensity = abs(sin(time)) * 0.8 + 0.8;  // Adjust the coefficients as needed

    // Define the colors for red, orange, and yellow
    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 orange = vec3(0.8, 0.3, 0.0);

    // Interpolate between red and orange based on flame intensity
    vec3 flameColor = mix(red, orange, flameIntensity);

    // Modify the alpha component of the color based on distance and flame intensity
    color = vec4(flameColor, fragmentColor.a * (pow(0.01, distance) - 0.01) * flameIntensity);
}
