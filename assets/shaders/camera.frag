#version 400
varying vec2 textcoord;
uniform sampler2D texture;
uniform vec2 screen_resolution;
uniform float time;

void main() {
	vec4 color = texture2D(texture, textcoord);
	
	vec2 position = (gl_FragCoord.xy / screen_resolution) - 0.5;
	
	float a = abs(length(position));
	float v = clamp(1.0 / (abs(length(a)) * 2.0), 0, 1);
	
    vec3 av = ((color.rgb - 0.5) * (1.1)) + 0.5;
	
    gl_FragColor = vec4(av * pow(v, 2), color.a);
}