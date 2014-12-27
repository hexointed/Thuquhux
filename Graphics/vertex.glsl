#version 110

//varying vec3 lightPos;

void main(void){
	vec3 lightPos = vec3(0.0, 1.0, 5.0);
	float lightRadius = 5.0;
	gl_Position = ftransform();
	vec4 col = vec4(1.0, 1.0, 1.0, 0.0);
	float dist = distance(gl_Position.xyz, lightPos);
	float denom = (dist/lightRadius + 1.0);
	vec4 c = normalize(gl_Color + vec4(1.0,1.0,1.0,1.0));
	gl_FrontColor = (c * col * 2.0)/(denom*denom);
}
