#version 460 core
out vec4 FragColor;
  
in vec3 Normal;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
	//Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float diffuseStrength = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStrength * lightColor;

	//Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 result = (ambient + diffuse + specular) * objectColor;
//    FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(texCoord.x, texCoord.y)), 0.2);
	FragColor = vec4(result, 1.0);
} 