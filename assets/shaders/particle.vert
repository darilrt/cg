#version 400
layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec4 position;
layout (location = 2) in vec2 size_rot;
layout (location = 3) in vec4 current_color;

out float life_time;
out vec4 color;

varying vec2 textcoord;

mat4 rotationX(in float angle ) {
	return mat4(1.0,          0,           0, 0,
				  0, cos(angle), -sin(angle), 0,
				  0, sin(angle),  cos(angle), 0,
				  0,          0,           0, 1);
}

mat4 rotationY(in float angle ) {
	return mat4( cos(angle),   0, sin(angle), 0,
						  0, 1.0,		   0, 0,
				-sin(angle),   0, cos(angle), 0,
						  0,   0,		   0, 1);
}

mat4 rotationZ(in float angle ) {
	return mat4(cos(angle),	-sin(angle), 0,	0,
				sin(angle),	 cos(angle), 0,	0,
						0,	 		  0, 1,	0,
						0,			  0, 0,	1);
}

void main() {
	textcoord = gl_MultiTexCoord0.xy;
	life_time = position.w;
	color = current_color;
	
	vec4 vertex = vertex_position * rotationZ(size_rot.y);
	vertex.xyz *= size_rot.x;
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(position.xyz, 1);
	gl_Position += gl_ProjectionMatrix * vertex;
}
