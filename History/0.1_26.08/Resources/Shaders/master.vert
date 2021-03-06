#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 Normal;

uniform mat4 modelMat;
uniform mat4 vpMat;

void main()
{
	gl_Position = vpMat * modelMat * vec4(aPos, 1.0);
	Normal = mat3(transpose(inverse(modelMat))) * aNorm;
}