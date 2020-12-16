#version 400
varying vec2 textcoord;
uniform sampler2D texture;

void main() {
	vec4 color = texture2D(texture, textcoord);
	
	gl_FragColor = color;
}
