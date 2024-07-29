varying vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;
uniform vec3 ambient;

void main()
{
    // Ambient light
    vec4 ambient_light = vec4(ambient.x, ambient.y, ambient.z, 1.0);
    
    // Convert light to view coords
    vec2 lightPosTransformed = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
    
    // Calculate the vector from light to pixel (Make circular)
    vec2 lightToFrag = lightPosTransformed - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;

    // Length of the vector (distance)
    float vecLength = clamp(length(lightToFrag) * 2.0, 0.0, 1.0);

    // Lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // Multiply it by the color and lighting
    if(hasTexture == true)
    {
        gl_FragColor = gl_Color * pixel * (clamp(ambient_light + vec4(1.0-vecLength, 1.0-vecLength, 1.0-vecLength, 1.0), 0.0, 1.0));
    }
    else
    {
        gl_FragColor = gl_Color;
    }
}
