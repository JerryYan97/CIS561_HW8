#include "pointlight.h"


Color3f PointLight::L(const Intersection &isect, const Vector3f &w) const
{
    return Color3f(0.f);
}

Color3f PointLight::Sample_Li(const Intersection &ref, const Point2f &xi,
                                     Vector3f *wi, Float *pdf) const
{
    *wi = glm::normalize(transform.position() - ref.point);
    *pdf = 1.f;
    return emittedLight / DistanceSquared(transform.position(), ref.point);
}

float PointLight::Pdf_Li(const Intersection &ref, const Vector3f &wi) const
{
    return 0;
}
