attribute vec3 position;
attribute vec2 texcoord;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

varying vec2 V_Texcoord;
void main()
{
    gl_PointSize = 600.0;
    V_Texcoord = texcoord;
    gl_Position = P*V*M*vec4(position,1.0);
}