#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 spriteColor;
uniform sampler2D image;

void main() {
    FragColor = vec4(spriteColor, 1.0f) * texture(image, TexCoord);
}