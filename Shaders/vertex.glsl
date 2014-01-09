#version 110

//varying vec3 lightPos;

void main(void){
	vec3 lightPos = {0,1,5};
	float lightRadius = 5;
	gl_Position = ftransform();
	vec4 col = {0.5,1,0.7,0};
	float dist = distance(gl_Position.xyz, lightPos);
	
	float denom = (dist/lightRadius + 1);
	gl_FrontColor = (gl_Color * col * 2)/(denom*denom);
}
