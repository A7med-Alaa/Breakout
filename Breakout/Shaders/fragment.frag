#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

layout (location = 0 ) uniform sampler2D Texture;

void main() {
    FragColor = texture(Texture, TexCoord);
}