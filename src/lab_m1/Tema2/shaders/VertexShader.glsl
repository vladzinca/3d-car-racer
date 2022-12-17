#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal; // de facut si pentru culoare
layout(location=3) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 car_position;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = normal;

    vec3 pos = position;

//    pos.y = pos.y - pow(length(pos - car_position),2) * 0.01f;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(pos, 1);

}
