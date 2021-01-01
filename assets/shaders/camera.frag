#version 400
varying vec2 textcoord;
uniform sampler2D texture;
uniform vec2 screen_resolution;
uniform float time;

void main() {
	vec4 color = texture2D(texture, textcoord);
	
    gl_FragColor = color;
}