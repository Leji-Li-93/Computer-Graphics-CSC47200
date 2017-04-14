#version 330

in  vec4 v_Color;	// varying variable for passing color from vertex shader
out vec4 fragColor;	// legacy version would have used gl_FragColor instead

void main() 
{
	// legacy version: gl_FragColor = v_Color;
	fragColor = v_Color;
}
