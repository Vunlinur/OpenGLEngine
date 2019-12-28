#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_ModelViewProjectionMatrix;

void main()
{
	gl_Position = u_ModelViewProjectionMatrix * position;
	v_texCoord = texCoord;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
float power = 2;
float divider = 80;

in vec2 v_texCoord;

uniform float u_Time;
uniform sampler2D u_Texture;

void main()
{
	//simple gradients
	/* 
	color = vec4(
		gl_FragCoord.x *		gl_FragCoord.y	/ 307200,
		(640-gl_FragCoord.x) *	gl_FragCoord.y	/ 307200,
		1-(						gl_FragCoord.y	/ 480),
		1.0);
	*/
	//curly gradient stripes

	vec4 blendColor = vec4(
		sin( u_Time ) - mod(50* sin(0.3*u_Time)		-	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) +			gl_FragCoord.y) / divider, power)))) / 30 *			gl_FragCoord.x *	gl_FragCoord.y / 307200,
		(				mod(50* sin(0.3*u_Time)		+	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) + 640 -	gl_FragCoord.y) / divider, power)))) / 30 * 1 - (	gl_FragCoord.y /	480)					)- sin(u_Time),
		(				mod(50* sin(0.3*u_Time) +640 -	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) +			gl_FragCoord.y) / divider, power)))) / 30 * (640 -	gl_FragCoord.x) *	gl_FragCoord.y / 307200	)- sin(u_Time),
		1.0);

	//multimix gradients
	/*
	vec4 blendColor = vec4(
		sin(15 + (pow(		(gl_FragCoord.y) / divider, power) / 10) / 30 *			gl_FragCoord.x * gl_FragCoord.y / 307200),
		sin(15 + (pow(		(gl_FragCoord.y) / divider, power) / 10) / 30 * (640 -	gl_FragCoord.x) * gl_FragCoord.y / 307200),
		sin(15 + (pow((640 - gl_FragCoord.y) / divider, power) / 10) / 30 * 1 - (	gl_FragCoord.y					/ 480)),
		1.0);
	*/
	//chequered pixel pattern
	/*
	color = vec4(
		sin((				gl_FragCoord.x) / divider) + sin((					gl_FragCoord.y) / divider),
		sin((3 * divider +	gl_FragCoord.x) / divider) + sin((3 *	divider +	gl_FragCoord.y) / divider),
		sin((3 * divider +	gl_FragCoord.x) / divider) + sin((					gl_FragCoord.y) / divider),
		1.0); 
	*/

	vec4 texColor = texture(u_Texture, v_texCoord);
	color = texColor;
	//color = texColor - blendColor;
};