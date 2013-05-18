#version 110

varying vec3 lightPos;

void main(void){
	gl_Position = ftransform();
	vec4 col = {0,1,0.5,0};
	vec4 mul = {3,3,3,1};
	float dist = distance(gl_Position, gl_LightSource[0].position);
	
	gl_FrontColor = (gl_Color * col * 2)/dist;
}