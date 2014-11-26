#ifndef QDML_MAT4X4_H
#define QDML_MAT4X4_H

#include "qdmlmatrix.h"
#include "qdmlvector.h"
#include "qdmlutils.h"


namespace qdml
{

template<typename T>
class Tmat4: public matNM<T, 4, 4>
{
public:
  typedef matNM<T,4,4> base;
  typedef Tmat4<T> matType;

  inline Tmat4() {}
  inline Tmat4( const matType& that ) : base( that ) {}
  inline Tmat4( const base& that ) : base( that ) {}
  inline Tmat4( const vecN<T,4> &v ) : base( v ) {}
  inline Tmat4( const vecN<T,4> &v0,
                const vecN<T,4> &v1,
                const vecN<T,4> &v2,
                const vecN<T,4> &v3 )
  {
    base::data[0] = v0;
    base::data[1] = v1;
    base::data[2] = v2;
    base::data[3] = v3;
  }
};

typedef Tmat4<float> mat4;
typedef Tmat4<int> imat4;
typedef Tmat4<unsigned int> umat4;
typedef Tmat4<double> dmat4;

static inline mat4 frustum( float left, float right, float bottom, float top, float near, float far )
{

  mat4 result( mat4::identity() );

  if( ( right == left ) ||
      ( top == bottom ) ||
      ( near == far ) ||
      ( near < 0.0 ) ||
      ( far < 0.0 )  )
    return result;


  result[0][0] = ( 2.0f  * near ) / ( right - left );
  result[1][1] = ( 2.0f * near ) / ( top - bottom );

  result[2][0] = ( right + left ) / ( right - left );
  result[2][1] = ( top + bottom ) / ( top - bottom );
  result[2][2] = -( far + near ) / ( far - near );
  result[2][3] = -1.0f;

  result[3][2] = -( 2.0f * far * near ) / (far - near );
  result[3][3] = 0.0f;

  return result;
}

static inline mat4 perspective( float fovy, float aspect, float near, float far )
{
    float q = 1.0f / tan( toRadians( 0.5 * fovy ) );
    float A = q / aspect;
    float B = ( near + far ) / ( near - far );
    float C = ( 2.0f * near * far ) / ( near - far );

    mat4 result;

    result[0] = vec4( A, 0.0f, 0.0f, 0.0f );
    result[1] = vec4( 0.0f, q, 0.0f, 0.0f );
    result[2] = vec4( 0.0f, 0.0f, B, -1.0f );
    result[3] = vec4( 0.0f, 0.0f, C, 0.0f );

    return result;

}

static inline mat4 ortho( float left, float right, float bottom, float top, float near, float far )
{
    return mat4( vec4( 2.0f / ( right - left ), 0.0f, 0.0f, 0.0f),
                 vec4( 0.0f, 2.0f / ( top - bottom ), 0.0f, 0.0f),
                 vec4( 0.0f, 0.0f, 2.0f / ( near - far), 0.0f ),
                 vec4( ( left + right ) / (left - right),
                       ( bottom + top ) / ( bottom - top ),
                       ( near + far ) / ( far - near ),
                       1.0f ) );
}

template<typename T>
static inline Tmat4<T> translate( T x, T y, T z )
{
  return Tmat4<T>(Tvec4<T>( 1.0f, 0.0f, 0.0f, 0.0f ),
                  Tvec4<T>( 0.0f, 1.0f, 0.0f, 0.0f ),
                  Tvec4<T>( 0.0f, 0.0f, 1.0f, 0.0f ),
                  Tvec4<T>( x, y, z, 1.0f ) );

}

template<typename T>
static inline Tmat4<T> translate( const vecN<T,3> &v )
{
   return translate( v[0], v[1], v[2] );
}

template<typename T>
static inline Tmat4<T> lookAt( const vecN<T,3> &eye, const vecN<T,3> &center, const vecN<T,3> &up )
{
    const Tvec3<T> f = normalize( center - eye );
    const Tvec3<T> upN = normalize( up );
    const Tvec3<T> s = cross( f, upN );
    const Tvec3<T> u = cross( s, f );
    const Tmat4<T> M = Tmat4<T>( Tvec4<T>( s[0], u[0], -f[0], T(0) ),
                                 Tvec4<T>( s[1], u[1], -f[1], T(0) ),
                                 Tvec4<T>( s[2], u[2], -f[2], T(0) ),
                                 Tvec4<T>( T(0), T(0), T(0), T(1) ) );

    return M * translate<T>(-eye);

}

template<typename T>
static inline Tmat4<T> scale( T x, T y, T z )
{
  return Tmat4<T>( Tvec4<T>( x, 0.0f, 0.0f, 0.0f ),
                   Tvec4<T>( 0.0f, y, 0.0f, 0.0f ),
                   Tvec4<T>( 0.0f, 0.0f, z, 0.0f ),
                   Tvec4<T>( 0.0f, 0.0f, 0.0f, 1.0f ) ) ;
}

template<typename T>
static inline Tmat4<T> scale( const Tvec3<T> &v )
{
  return scale( v[0], v[1], v[2] );
}

template<typename T>
static inline Tmat4<T> scale( T x )
{
    return Tmat4<T>( Tvec4<T>( x, 0.0f, 0.0f, 0.0f ),
                     Tvec4<T>( 0.0f, x, 0.0f, 0.0f ),
                     Tvec4<T>( 0.0f, 0.0f, x, 0.0f ),
                     Tvec4<T>( 0.0f, 0.0f, 0.0f, 1.0f ) ) ;
}

template<typename T>
static inline Tmat4<T> rotate( T angle, T x, T y, T z )
{
  Tmat4<T> result;
  const T x2 = x * x;
  const T y2 = y * y;
  const T z2 = z * z;

  float rads = float( angle ) * 0.0174532925f;

  const float c = cosf( rads );
  const float s = sinf( rads );
  const float omc = 1.0f - c;

  result[0] = Tvec4<T>( T( x2 * omc + c ), T( y * x * omc + z * s ), T( x * z * omc - y * s ), T( 0 ) );
  result[1] = Tvec4<T>( T ( x * y * omc - z * s ), T( y2 * omc + c ), T( y * z * omc + x * s ), T( 0 ) );
  result[2] = Tvec4<T>( T( x * z * omc + y * s ), T( y * z * omc - x * s ), T( z2 * omc + c ), T( 0 ) );
  result[3] = Tvec4<T>( T( 0 ), T( 0 ), T( 0 ), T( 1 ) );

  return result;
}

template<typename T>
static inline Tmat4<T> rotate( T angle, const vecN<T,3> &v )
{
  return rotate<T>( angle, v[0], v[1], v[2 ] );
}

template<typename T>
static inline Tmat4<T> rotate( T angle_x, T angle_y, T angle_z )
{
  return rotate( angle_z, 0.0f, 0.0f, 1.0f ) *
         rotate( angle_y, 0.0f, 1.0f, 0.0f ) *
         rotate( angle_x, 1.0f, 0.0f, 0.0f );
}

}



#endif
