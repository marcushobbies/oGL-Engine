#version 460 core
out vec4 colour;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
    colour = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);
} 