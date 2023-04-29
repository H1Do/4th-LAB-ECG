#ifndef SHADOW_MAP_TECHNIQUE_H
#define	SHADOW_MAP_TECHNIQUE_H

#include "technique.h"
#include "technique.cpp"
#include "math_3d.h"
#include "math_3d.cpp"

class ShadowMapTechnique : public Technique {

public:
    ShadowMapTechnique();
    virtual bool Init();
    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);

private:

    GLuint m_WVPLocation;
    GLuint m_textureLocation;
    const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
layout (location = 1) in vec2 TexCoord;                                             \n\
layout (location = 2) in vec3 Normal;                                               \n\
                                                                                    \n\
uniform mat4 gWVP;                                                                  \n\
                                                                                    \n\
out vec2 TexCoordOut;                                                               \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = gWVP * vec4(Position, 1.0);                                       \n\
    TexCoordOut = TexCoord;                                                         \n\
}";

    const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
in vec2 TexCoordOut;                                                                \n\
uniform sampler2D gShadowMap;                                                       \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    float Depth = texture(gShadowMap, TexCoordOut).x;                               \n\
    Depth = 1.0 - (1.0 - Depth) * 25.0;                                             \n\
    FragColor = vec4(Depth);                                                        \n\
}";
};

#endif	/* SHADOW_MAP_TECHNIQUE_H */
