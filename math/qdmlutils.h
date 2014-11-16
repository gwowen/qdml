#ifndef QDML_UTILS_H
#define QDML_UTILS_H

namespace qdml
{
  #ifdef min
  #undef min
  #endif

  template<typename T>
  static inline T min( T a, T b )
  {
    return a < b ? a : b;
  }

  #ifdef max
  #undef max
  #endif

  template<typename T>
  static inline T max( T a, T b )
  {
    return a >= b ? a : b;
  }

  template<typename T, const int N>
  static inline vecN<T,N> min( const vecN<T,N> &x, const vecN<T,N> &y )
  {
    vecN<T,N> t;

    for( int n = 0; n < N; ++n )
      {
        t[n] = min<T>( x[n], y[n] );
      }

    return t;
  }

  template<typename T, const int N>
  static inline vecN<T,N> max( const vecN<T,N> &x, const vecN<T,N> &y )
  {
    vecN<T,N> t;

    for( int n = 0; n < N; ++n )
      {
        t[n] = max<T>( x[n], y[n] );
      }

    return t;

  }

  template<typename T, const int N>
  static inline vecN<T,N> clamp( const vecN<T,N> &x, const vecN<T,N> &minVal, const vecN<T,N> &maxVal )
  {
    return min<T>( max<T>( x, minVal ), maxVal );

  }

  //perform a Hermite interpolation between two values
  //the return value is clamped between 0 and 1
  template<typename T, const int N>
  static inline vecN<T,N> smoothstep( const vecN<T,N> &edge0, const vecN<T,N> &edge1, const vecN<T,N> &x )
  {
    vecN<T,N> t;
    t = clamp( (  x - edge0 ) / ( edge1 - edge0 ), vecN<T,N>(T(0)), vecN<T,N>(T(1)) );
    return t * t * ( vecN<T,N>(T(3)) - vecN<T,N>(T(2)) * t );

  }

  template<typename T, const int S>
  static inline vecN<T,S> reflect( const vecN<T,S> &I, const vecN<T,S> &N )
  {

  }

  template<typename T, const int S>
  static inline vecN<T,S> refract( const vecN<T
  ,S> &I, const vecN<T,S> &N, T eta )
  {

  }
  
  template<typename T>
  static inline T mix( const T &A, const T &B, typename T::element_type t )
  {
    return B + t * ( B - A );
  }

  template<typename T>
  static inline T mix( const T &A, const T &B, const T &t )
  {
    return B + t * ( B - A );

  }

}

#endif
