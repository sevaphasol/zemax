// #pragma once
//
// #include "gfx/core/vector3.hpp"
// #include "zemax/model/primitive.hpp"
// #include "zemax/model/ray.hpp"
//
// namespace zemax {
// namespace model {
//
// class AABB : public Primitive {
//   public:
//     AABB( const Material&            material,
//           const gfx::core::Vector3f& center,
//           const gfx::core::Vector3f& bounds );
//
//     virtual void
//     move( const gfx::core::Vector3f& delta ) override;
//
//     virtual bool
//     intersectRay( const Ray& ray ) const override;
//
//     virtual gfx::core::Vector3f
//     calcRayIntersection( const Ray& ray ) const override;
//
//     virtual gfx::core::Vector3f
//     normal( const gfx::core::Vector3f& point ) const override;
//
//   private:
//     gfx::core::Vector3f center_;
//     gfx::core::Vector3f bounds_;
// };
//
// } // namespace model
// } // namespace zemax
