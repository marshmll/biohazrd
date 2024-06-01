varying vec4 vert_pos;

void main()
{
    // Transform the vertex position
    vec4 transformedPos = gl_ModelViewProjectionMatrix * gl_Vertex;
    vert_pos = transformedPos;
    gl_Position = transformedPos;

    // Transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // Forward the vertex color
    gl_FrontColor = gl_Color;
}
