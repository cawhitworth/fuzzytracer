#pragma once

#include "ILight.h"
#include "IWorldObject.h"
#include <memory>

// An area light is a rectangular light of h*w unit squares
// positioned on the x-z plane centred on the origin.
class AreaLight :
    public ILight, public IWorldObject
{
public:
    AreaLight(unsigned int w = 3, unsigned int h = 3, decimal fuzz = 1);

    virtual ~AreaLight(void);

    const Matrix& GetObjectMatrix() const override;
    void SetObjectMatrix(const Matrix& m) override;

    void SetColour(const Colour& col) { m_colour.reset(new Colour(col)); }
    const Colour& GetColour() const { return *m_colour; }
    std::vector<Vector> Samples() const override;

private:
    const decimal m_fuzz;
    const unsigned int m_w, m_h;
    std::shared_ptr<const Matrix> m_objectMatrix;
    std::shared_ptr<const Colour> m_colour;
};

