#pragma once

#include "sgl/graphic/Particle.h"
#include "sgl/graphic/TexturedRenderable.h"

namespace sgl
{
namespace graphic
{

class TexturedParticle : public Particle
{
public:
    TexturedParticle() = default;
    TexturedParticle(Texture * tex);

    void Render() override;

protected:
    TexturedRenderable mRenderable;
};

// ==================== INLINE FUNCTIONS ====================

inline TexturedParticle::TexturedParticle(Texture * tex) { mRenderable.SetTexture(tex); }
inline void TexturedParticle::Render() { mRenderable.Render(); }

} // namespace graphic
} // namespace sgl
