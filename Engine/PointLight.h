#pragma once

#include <memory>

#include "ILight.h"
#include "IWorldObject.h"

#include "Matrix.h"

class PointLight :
    public ILight, IWorldObject
{
public:
    PointLight(void);
    virtual ~PointLight(void);

     const Matrix& GetObjectMatrix() const override;
     void SetObjectMatrix(const Matrix&) override;

    void SetColour(const Colour& col) { m_colour.reset(new Colour(col)); }
    const Colour& GetColour() const { return *m_colour; }
    std::vector<Vector> Samples() const override;

private:
    std::shared_ptr<Matrix> m_objectMatrix;
    std::vector<Vector> m_point;
    std::shared_ptr<Colour> m_colour;
};

