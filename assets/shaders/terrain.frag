#version 400
varying vec2 textcoord;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform int index_list[256];

uniform sampler2D texture_noise;
uniform float time;

void main() {
	vec2 coord = vec2(fract(textcoord.x), fract(textcoord.y));
	
	float x = (textcoord.x - coord.x);
	float y = (textcoord.y - coord.y);
	
	if (x > 16.0) {
		x -= 1;
	}
		
	if (y > 16.0) {
		y -= 1;
	}
	
	int index = int(x + y*16.0);
	
	vec4 color = vec4(1, 1, 1, 1);
	
	switch(index_list[index]) {
		case 0:
			color = texture2D(texture_0, coord);
			break;
			
		case 1:
			color = texture2D(texture_1, coord);
			break;
		
		case 2:
			vec4 n1color = texture2D(texture_noise, (textcoord.xy + vec2(time/4, time/6)) / 50.0);
			vec4 n2color = texture2D(texture_noise, (textcoord.yx + vec2(time/2, time/10)) / 50.0);
			vec4 ncolor = (n2color - n1color);
			
			coord.xy += ncolor.r/1.5;
			
			color = texture2D(texture_2, coord);
			color -= (ncolor)/7.0;
			
			break;
	}
	
	gl_FragColor = color;
}