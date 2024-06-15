#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float blurAmount;

const float offset = 1.0 / 300.0; // Adjust this based on your texture size for a more subtle effect

void main() {
    vec4 color = texture(screenTexture, TexCoords);
    if (blurAmount > 0.01) { // Ensure we have a threshold that must be surpassed to start blurring
        for (int x = -2; x <= 2; x++) {
            for (int y = -2; y <= 2; y++) {
                color += texture(screenTexture, TexCoords + vec2(x, y) * offset * blurAmount) * 0.111;
            }
        }
        color /= 25.0;
    }
    FragColor = color;
}


















