#version 460 core
out vec4 colour;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 ambientLightColor;

#define MAX_NUMBER_POINT_LIGHTS 128

struct PointLight {
    vec3 position;
    vec3 colour;
};

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform PointLight pointLights[MAX_NUMBER_POINT_LIGHTS];
uniform int numberPointLights;

uniform Material material;

uniform vec3 viewPos;


vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //32


    vec3 diffuse = diff * light.colour * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = material.specular * spec * light.colour;  


    return (diffuse+specular);
}

void main(){

    vec4 textureColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = normalize(Normal);


    vec3 lightingResult = ambientLightColor * vec3(texture(material.diffuse, TexCoord));

    for(int i = 0; i < numberPointLights; i++)
        lightingResult += calculatePointLight(pointLights[i], norm, FragPos, viewDir);
    
    colour = textureColor * vec4(lightingResult, 1.0);
    //colour = texture(vec4(lightingResult, 1.0), TexCoord);
} 