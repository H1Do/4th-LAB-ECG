#include "shadow_map_technique.h"

ShadowMapTechnique::ShadowMapTechnique()
{
}

bool ShadowMapTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, pVS)) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, pFS)) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_textureLocation = GetUniformLocation("gShadowMap");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_textureLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return true;
}

void ShadowMapTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void ShadowMapTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_textureLocation, TextureUnit);
}

