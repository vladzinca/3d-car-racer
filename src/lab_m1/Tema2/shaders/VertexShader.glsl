#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=3) in vec3 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 frag_color;

void main()
{
    frag_color = normal;

    gl_Position = Projection * View * Model * vec4(position, 1);
    gl_Position.y =  gl_Position.y - length(gl_Position) * length(gl_Position) * 0.0125f;
}
