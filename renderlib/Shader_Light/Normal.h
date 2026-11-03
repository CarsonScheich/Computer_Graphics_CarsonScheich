#pragma once
#include "Shader.h"


class NormalShader: public Shader{
    public:

    NormalShader();

    bool needsLighting() const override {
    return false;
    }

    color raycolor(const HitRecord& rec) const override;

};