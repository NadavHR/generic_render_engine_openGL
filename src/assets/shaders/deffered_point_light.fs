#version 410 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D hdrBuffer;

uniform vec3 Position;
uniform vec3 Color;
uniform vec3 ViewPos;
uniform float quadratic, linear, lightThreshold;

const float e = exp(1); // the mathematical constant e
const float KSPEC = 0.00001; // the lower the value the softer the base lighting, 
// if at 0 the lighting will be completely uniform regardless of normal direction if the specular map is black
void main()
{             
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 BaseColor = texture(hdrBuffer, TexCoords).rgb;

    float dis = length(Position - FragPos);
    vec3 viewDir  = normalize(ViewPos - FragPos);

    // attenuation
    float attenuation = 1.0 / (1.0 + linear * dis + quadratic * dis * dis);
    vec3 color = Color * attenuation;
    
    // // diffuse
    vec3 lightDir = normalize(Position - FragPos);
    float lambertianDiffuse = max(dot(Normal, lightDir), 0.0);
    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float normDotHalfway = max(dot(Normal, halfwayDir), 0.0);
    float specular = ((1/(Specular + KSPEC )) + 1) * exp(-((1/(Specular + KSPEC)) * e) * pow((normDotHalfway - 1) , 2));
    vec3 lighting = color * Albedo * (specular + lambertianDiffuse);

    FragColor = vec4(BaseColor + lighting, 1.0);
    // FragColor = vec4(lambertianDiffuse + BaseColor, 1.0);
    // FragColor = vec4(lighting, 1.0);
    // FragColor = vec4(vec3(Specular), 1.0);
    // FragColor = vec4(vec3(Albedo), 1.0);
    // FragColor = vec4(vec3(Normal), 1.0);

    if (length(FragColor.rgb) > lightThreshold) {
        BrightColor = vec4(FragColor.rgb, 1.0);
    }
    else {
        BrightColor = vec4(0, 0, 0, 1);
    }
}  