#version 460 core

in vec2 uv;
out vec4 FragColor;
uniform sampler2D sampler;

uniform int invulnerable=0;


void main()
{
	vec4 tmp_color = texture(sampler, uv);
	if(invulnerable==1)
	{
		if(tmp_color.a>0.1)
			FragColor = vec4(1.0,0.0,0.0,0.4);
        else
			FragColor = vec4(0.0,0.0,0.0,0.0);
	}
	else
		FragColor = tmp_color;
}