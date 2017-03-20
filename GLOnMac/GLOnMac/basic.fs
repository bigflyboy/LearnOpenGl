#version 330 core
out vec4 color;
in vec3 colorout;
void main()
{
    color = vec4(colorout.xyz, 1.0f);
}
