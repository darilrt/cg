#version 400
varying vec2 textcoord;
uniform sampler2D texture;
uniform bool use_texture;

in float life_time;
in vec4 color;

void main() {
	vec4 text_color = vec4(1, 1, 1, 1);
	
	if (use_texture) {
		text_color = texture2D(texture, textcoord);
	}
	
	gl_FragColor = text_color * color;
}
