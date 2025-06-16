#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

float textureSize;

in vec2 TexCoords;
in vec3 FragPos;
uniform mat4 ViewRot;
uniform vec3 ViewPos;

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gAlbedoSpec;
uniform vec2 Texel;
uniform vec3 AmbientColor;
uniform float AmbientStrength;

void main()
{             
    // retrieve data from G-buffer
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    vec3 Position = texture(gPosition, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    // this is a very rough estimate for ambient occlusion  
    vec2 texelOffsetx = vec2(Texel.x, 0.0);
    vec2 texelOffsety = vec2(0.0, Texel.y);
    vec3 normalxp = texture(gNormal, TexCoords + texelOffsetx).rgb;
    vec3 normalxn = texture(gNormal, TexCoords - texelOffsetx).rgb;
    vec3 normalyp = texture(gNormal, TexCoords + texelOffsety).rgb;
    vec3 normalyn = texture(gNormal, TexCoords - texelOffsety).rgb;
    float AmbientOcclusion = max(0, min(1.0, 
        1.0 - (1 * (
        dot(normalxp, vec3(-texelOffsetx, 0)) +
        dot(normalxn, vec3(texelOffsetx, 0))) +
        dot(normalyp, vec3(-texelOffsety, 0)) +
        dot(normalyn, vec3(texelOffsety, 0)))));
    
    vec3 lighting = AmbientColor * AmbientStrength * Albedo * AmbientOcclusion; 
    
    FragColor = vec4(lighting, 1.0);
    // FragColor = vec4(Albedo, 1.0);
    // FragColor = vec4(Normal, 1.0);
    // Position.z *= -(1.0/150.0);
    // FragColor = vec4(Position, 1.0);
}  