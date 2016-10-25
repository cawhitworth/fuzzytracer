#pragma once

#include <memory>
#include "IIntersectable.h"
#include "IWorldObject.h"

class Plane :
    public IIntersectable,
    public IWorldObject
{
public:
    Plane(void);
    ~Plane(void);

    void SetColour(const Colour& col);

    bool Intersect(const Vector& rayOrigin, const Vector& rayDirection, decimal& t) const override;
    Vector Normal(const Vector& intersectPoint) const override;
    Colour ColourAt(const Vector& intersectPoint) const override;

    const Matrix& GetObjectMatrix() const override;
    void SetObjectMatrix(const Matrix&) override;

private:
    std::shared_ptr<const Matrix> m_objectMatrix;
    std::shared_ptr<const Matrix> m_objectMatrixInverse;
    std::shared_ptr<const Vector> m_normalVector;
    std::shared_ptr<const Colour> m_colour;
};

