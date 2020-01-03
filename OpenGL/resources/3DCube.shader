#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 v_Color;
out vec4 v_Position;

uniform mat4 u_ModelViewProjectionMatrix;

void main()
{
	v_Color = position;
	v_Position = u_ModelViewProjectionMatrix * position;
	gl_Position = v_Position;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec4 v_Position;

// depth
float near = 0.1;
float far = 10000.0;

float depth = (v_Position.z - near) / (far - near);


void main()
{
	depth = 1 - depth;
	color = vec4(
		(depth*v_Color.x + 250.0) / 500.0,
		(depth*v_Color.y + 250.0) / 500.0,
		(depth*v_Color.z + 250.0) / 500.0,
		1.0);

	//color = vec4(vec3(depth), 1.0);
};