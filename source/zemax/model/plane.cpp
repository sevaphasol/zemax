// #include "zemax/model/plane.hpp"
// #include "gfx/core/vector3.hpp"
//
// namespace zemax {
// namespace model {
//
// Plane::Plane( const Material&            material,
//               const gfx::core::Vector3f& base_point,
//               const gfx::core::Vector3f& normal )
//     : Primitive( material ), base_point_( base_point ), normal_( normal )
// {
// }
//
// void
// Plane::move( const gfx::core::Vector3f& delta )
// {
// }
//
// bool
// Plane::intersectRay( const Ray& ray ) const
// {
//     return scalarMul( ray.getDir(), normal_ ) != 0;
// }
//
// gfx::core::Vector3f
// Plane::calcRayIntersection( const Ray& ray ) const
// {
//     if ( !intersectRay( ray ) )
//     {
//         return gfx::core::Vector3f::Nan;
//     }
//
//     auto  r0 = ray.getBasePoint();
//     auto  a  = ray.getDir();
//     auto  rp = base_point_;
//     auto  n  = normal_;
//     float t  = scalarMul( r0 - rp, n ) / scalarMul( a, n );
//
//     return ( t < 0 ) ? gfx::core::Vector3f::Nan : r0 + a * t;
// }
//
// gfx::core::Vector3f
// Plane::normal( const gfx::core::Vector3f& point ) const
// {
//     return normal_;
// }
//
// } // namespace model
// } // namespace zemax
