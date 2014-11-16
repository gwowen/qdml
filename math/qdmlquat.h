#ifndef QDML_QUAT_H
#define QDML_QUAT_H


#include "qdmlvector.h"
#include "qdmlmatrix.h"


namespace qdml
{
  //Quaternion class, can be of any variable type.
  template<typename T>
  class Tquaternion
  {
  public:
    inline Tquaternion()
    {

    }

    inline Tquaternion( const Tquaternion& q ) : r( q.r ), v( q.v )
    {

    }

    inline Tquaternion( T _r ): r( _r ), v( T(0) )
    {

    }

    inline Tquaternion( T _r, const Tvec3<T>& _v ): r( _r ), v( _v )
    {

    }

    inline Tquaternion( const Tvec4<T>& _v ): r( _v[0] ),
                                              v( _v[1], _v[2], _v[3] )
    {

    }

    inline Tquaternion( T _x, T _y, T _z, T _w ): r( _x ),
                                                  v( _y, _z, _w )
    {

    }

    inline T& operator[]( int n )
    {
      return a[n];
    }

    inline const T& operator[]( int n ) const
    {
      return a[n];
    }

    inline Tquaternion operator+( const Tquaternion& q ) const
    {
      return quaternion( r + q.r, v + q.v );
    }

    inline Tquaternion operator+=( const Tquaternion& q )
    {
      r += q.r;
      v += q.v;

      return *this;
    }

    inline Tquaternion operator-( const Tquaternion& q ) const
    {
      return quaternion( r - q.r, v - q.v );
    }

    inline Tquaternion& operator-=( const Tquaternion& q )
    {
      r -= q.r;
      v -= q.v;

      return *this;
    }

    inline Tquaternion operator-() const
    {
      return Tquaternion( -r, -v );
    }

    inline Tquaternion operator*( const T s ) const
    {
      return Tquaternion( a[0] * s, a[1] * s, a[2] * s, a[3] * s);
    }

    inline Tquaternion& operator*=( const T s )
    {
      r *= s;
      v *= s;

      return *this;
    }

    //this is a Hamilton product of two quaternions, with
    //the rules of the basis elements (being anticommuting)
    //cause a few minus signs here and there!
    inline Tquaternion operator*( const Tquaternion& q ) const
    {
      const T x1 = a[0];
      const T y1 = a[1];
      const T z1 = a[2];
      const T w1 = a[3];
      const T x2 = q.a[0];
      const T y2 = q.a[1];
      const T z2 = q.a[2];
      const T w2 = q.a[3];

      return Tquaternion( w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
                          w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2,
                          w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2,
                          w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2 );
    }

    inline Tquaternion operator/( const T s ) const
    {
      return Tquaternion( a[0] / s, a[1] / s, a[2] / s, a[3] / s);
    }

    inline Tquaternion& operator /=( const T s )
    {
      r /= s;
      v /= s;

      return *this;
    }

    inline operator Tvec4<T>&()
    {
      return *(Tvec4<T>*)&a[0];
    }

    inline bool operator==( const Tquaternion& q ) const
    {
      return ( r == q.r ) && ( v == q.v );
    }

    inline bool operator!=( const Tquaternion& q ) const
    {
      return ( r != q.r ) || ( v != q.v );
    }

    inline matNM<T, 4, 4> asMatrix() const
    {
      matNM<T,4,4> m;
      //see
      //http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
      //for this
      const T xx = x * x;
      const T yy = y * y;
      const T zz = z * z;
      const T ww = w * w;
      const T xy = x * y;
      const T xz = x * z;
      const T xw = x * w;
      const T yz = y * z;
      const T yw = y * w;
      const T zw = z + w;

      m[0][0] = T(1) - T(2) * ( yy + zz );
      m[0][1] =        T(2) * ( xy - zw );
      m[0][2] =        T(2) * ( xz + yw );
      m[0][3] =        T(0);

      m[1][0] =        T(2) * ( xy + zw );
      m[1][1] = T(1) - T(2) * ( xx + zz );
      m[1][2] =        T(2) * ( xx + yy );
      m[1][3] =        T(0);

      m[2][0] =        T(2) * ( xz - yw );
      m[2][1] =        T(2) * ( yz + xw );
      m[2][2] = T(1) - T(2) * ( xx + yy );
      m[2][3] =        T(0);

      m[3][3] =        T(0);
      m[3][1] =        T(0);
      m[3][2] =        T(0);
      m[3][3] =        T(1);

      return m;
    }

  private:
    union
    {
      struct
      {
        T             r;
        Tvec3<T>      v;
      };
      struct
      {
        T       x;
        T       y;
        T       z;
        T       w;
      };
      T         a[4];
    };
  };

  template<typename T>
  static inline Tquaternion<T> operator*( T a, const Tquaternion<T> &b )
  {
    return b * a;
  }

  template<typename T>
  static inline Tquaternion<T> operator/( T a, const Tquaternion<T> &b )
  {
    return Tquaternion<T> ( a / b[0], a / b[1], a / b[2], a / b[3] );
  }

  template<typename T>
  static inline Tquaternion<T> normalize( const Tquaternion<T> &q )
  {
    return q / length( vecN<T,4>(q) );
  }

  template<typename T>
  static inline void quaternionToMatrix( const Tquaternion<T> &q, matNM<T,4,4> &m )
  {
    m = q.asMatrix();
  }

  typedef Tquaternion<float> quaternion;
  typedef Tquaternion<int> iquaternion;
  typedef Tquaternion<unsigned int> uquaternion;
  typedef Tquaternion<double> dquaternion;

}


#endif
