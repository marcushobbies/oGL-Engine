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

float specularStrength = 0.5;

void main(){

    vec4 textureColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    colour = textureColor * vec4(ambientLightColor+diffuse+specular, 1.0);
} 