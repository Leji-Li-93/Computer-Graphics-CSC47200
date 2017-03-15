#version 330

in	vec2	a_Position;	// attribute variable: position vector
in	vec3	a_Color;	// attribute variable: color vector

out	vec4	v_Color;	// varying variable for passing color to fragment shader

uniform	mat4	u_Modelview;	// uniform variable for passing modelview  matrix
uniform	mat4	u_Projection;	// uniform variable for passing projection matrix
uniform	float	u_Theta;	// Theta parameter
uniform	int	u_Twist;	// Twist flag

void main() 
{
    /* 
    
    vec2 HW1b::rotTwist(vec2 p) {
        float d = m_twist ? sqrt(p[0]*p[0] + p[1]*p[1]) : 1;
        float sinTheta = sin(d*m_theta);
        float cosTheta = cos(d*m_theta);
        return vec2(p[0]*cosTheta - p[1]*sinTheta, p[0]*sinTheta + p[1]*cosTheta);
    }
    
    */ // Code to rotate from HW1B
    
    /*
    float d = 0.0;
    if (u_Twist == 1) 
        d = sqrt((a_Position.x * a_Position.x) + (a_Position.y * a_Position.y));
    else
        d = 1.0;
    float sinTheta = sin(d*u_Theta);
    float cosTheta = cos(d*u_Theta);
	gl_Position = u_Modelview * u_Projection * vec4((a_Position.x*cosTheta - a_Position.y*sinTheta, a_Position.x*sinTheta + a_Position.y*cosTheta), 0, 1);
    v_Color	= vec4(a_Color, 1);
    */
    gl_Position = u_Modelview * u_Projection * vec4(a_Position, 0, 1);
    v_Color	= vec4(a_Color, 1);
    
}
