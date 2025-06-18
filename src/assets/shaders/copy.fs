#version 410 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D Buffer;
void main()
{             
    vec3 color = texture(Buffer, TexCoords).rgb;
    FragColor = vec4(color, 1.0);
}  
