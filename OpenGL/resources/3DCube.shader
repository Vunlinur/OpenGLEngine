#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 v_Color;

uniform mat4 u_ModelViewProjectionMatrix;

void main()
{
	gl_Position = u_ModelViewProjectionMatrix * position;
	v_Color = position;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC 
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	color = vec4(
		(v_Color.x + 250.0) / 500.0,
		(v_Color.y + 250.0) / 500.0,
		(v_Color.z + 250.0) / 500.0,
		1.0);
};