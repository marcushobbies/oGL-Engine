#version 460 core
out vec4 colour;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 ambientLightColor;

uniform vec3 lightColor;
uniform vec3 lightPos; //Temporary; should be changed so multiple light sources may be used.

uniform vec3 viewPos;

void main(){

    vec4 textureColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);
    colour = textureColor;
} 