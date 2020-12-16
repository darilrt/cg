#version 400
varying vec2 textcoord;

void main() {
	textcoord = gl_MultiTexCoord0.xy;
	
	vec4 vertex = gl_Vertex;
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vertex;
}
