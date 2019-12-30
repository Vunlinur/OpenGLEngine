#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_ModelViewProjectionMatrix;

void main()
{
	gl_Position = u_ModelViewProjectionMatrix * position;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform float u_Power = 2;
uniform float u_Divider = 80;
uniform float u_Time;

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
		sin( u_Time ) - mod(50* sin(0.3*u_Time)		-	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) +			gl_FragCoord.y) / u_Divider, u_Power)))) / 30 *			gl_FragCoord.x *	gl_FragCoord.y / 307200,
		(				mod(50* sin(0.3*u_Time)		+	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) + 640 -	gl_FragCoord.y) / u_Divider, u_Power)))) / 30 * 1 - (	gl_FragCoord.y /	480)					)- sin(u_Time),
		(				mod(50* sin(0.3*u_Time) +640 -	gl_FragCoord.x,	(15 + (pow((50 * sin(u_Time) +			gl_FragCoord.y) / u_Divider, u_Power)))) / 30 * (640 -	gl_FragCoord.x) *	gl_FragCoord.y / 307200	)- sin(u_Time),
		1.0);

	//multimix gradients
	/*
	vec4 blendColor = vec4(
		sin(15 + (pow(		(gl_FragCoord.y) / u_Divider, u_Power) / 10) / 30 *			gl_FragCoord.x * gl_FragCoord.y / 307200),
		sin(15 + (pow(		(gl_FragCoord.y) / u_Divider, u_Power) / 10) / 30 * (640 -	gl_FragCoord.x) * gl_FragCoord.y / 307200),
		sin(15 + (pow((640 - gl_FragCoord.y) / u_Divider, u_Power) / 10) / 30 * 1 - (		gl_FragCoord.y					/ 480)),
		1.0);
	*/
	//chequered pixel pattern
	/*
	color = vec4(
		sin((					gl_FragCoord.x) / u_Divider) + sin((					gl_FragCoord.y) / u_Divider),
		sin((3 * u_Divider +	gl_FragCoord.x) / u_Divider) + sin((3 *	u_Divider +		gl_FragCoord.y) / u_Divider),
		sin((3 * u_Divider +	gl_FragCoord.x) / u_Divider) + sin((					gl_FragCoord.y) / u_Divider),
		1.0); 
	*/

	color = blendColor;
	//color = texColor - blendColor;
};