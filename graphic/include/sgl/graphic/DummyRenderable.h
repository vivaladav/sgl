#pragma once

#include "Renderable.h"

namespace sgl
{
namespace graphic
{

class DummyRenderable : public Renderable
{
public:
    void Render() override;
};

} // namespace graphic
} // namespace sgl
