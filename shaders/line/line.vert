//default grid vertex shader

#version 450 core

uniform mat4 u_modelTransform; //model matrix
uniform mat4 u_viewProjection; //view projection matrix

layout (location = 0) in vec3 vPos; //vertex input position

void main() {
    gl_Position = u_viewProjection * u_modelTransform * vec4(vPos, 1.0); //gl_Position is a built-in property of a vertex shader
}