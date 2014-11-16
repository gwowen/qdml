#ifndef QDML_VECTOR_H
#define QDML_VECTOR_H

#include <cmath>

namespace qdml
{
  //vecN - an N-dimensional vector which serves as the base
  //class for 2, 3 and 4-vectors of various types.
  //Also contains operators for the vector, which are implemented
  //once in template form so we don't have to repeatedly implement
  //for vec2, vec3, etc.
  template<typename T, const int len>
  class vecN
  {
    public:
      typedef class vecN<T,len> my_type;
      typedef T element_type;

      //default constructor, does nothing
      inline vecN()
      {

      }

      //copy constructor
      inline vecN( const vecN& that )
      {
        assign( that );
      }


      //construct a vector from a scalar
      inline vecN( T s )
      {
        for( int n = 0; n < len; ++n )
        {
          data[n] = s;
        }
      }

      //assignment operator for a vector
      inline vecN& operator=( const vecN& that )
      {
        assign( that );
        return *this;
      }

      inline vecN& operator=( const T& that )
      {
        for( int n = 0; n < len; ++n )
        {
          data[n] = that;
        }

        return *this;
      }

      //addition operator
      inline vecN operator+( const vecN& that ) const
      {
        my_type result;
        for( int n = 0; n < len; n++ )
        {
          result.data[n] = data[n] + that.data[n];
        }
          return result;
      }

      //compound sum
      inline vecN& operator+=( const vecN& that )
      {
        return( *this = *this + that );
      }

      inline vecN operator -() const
      {
        my_type result;
        for( int n = 0; n < len; ++n )
        {
          result.data[n] = -data[n];
        }

        return result;
      }

    //subtraction operator
      inline vecN operator-( const vecN& that ) const
      {
        my_type result;
        for( int n = 0; n < len; ++n )
        {
          result.data[n] = - that.data[n];
        }

        return result;
      }

      inline vecN operator -=( const vecN& that )
      {
        return( *this = *this - that );
      }

      inline vecN operator*( const vecN& that ) const
      {
        my_type result;
        for( int n = 0; n < len; ++n )
        {
          result.data[n] = data[n] * that.data[n];
        }

        return result;
      }

      inline vecN& operator *=( const T& that )
      {
        assign( *this * that );

        return *this;
      }

      inline vecN operator/( const vecN& that ) const
      {
        my_type result;
        for( int n = 0; n < len; ++n )
        {
          result.data[n] = data[n] / that.data[n];
        }

        return result;
      }

      inline vecN operator/=( const vecN& that )
      {
       assign( *this / that );

       return *this;
      }

      inline vecN operator/( const T& that ) const
      {
        my_type result;
        for( int n = 0; n < len; ++n )
        {
          result.data[n] = data[n] / that;
        }

        return result;
      }

      inline vecN operator/=( const T& that )
      {
       assign( *this / that );

       return *this;
      }

      inline T& operator[]( int n ) { return data[n]; }
      inline const T& operator[]( int n ) const { return data[n]; }

      inline static int size( void ) { return len; }

      inline operator const T* () const { return &data[0]; }


    protected:
      T data[len];

      inline void assign( const vecN& that )
      {
        for( int n = 0; n < len; ++n )
          data[n] = that.data[n];
      }
  };

  //2-dimensional vector. Derived from vecN, can be
  //float, int, etc. and inherits the operators of
  //vecN.
  template <typename T>
  class Tvec2 : public vecN<T, 2>
  {
  public:
    typedef vecN<T, 2> base;

    //uninitialized constructor
    inline Tvec2() {}

    //copy constructor
    inline Tvec2( const base& v ) : base( v ) {}

    //vec2( x, y )
    inline Tvec2( T x, T y)
    {
      base::data[0] = x;
      base::data[1] = y;
    }
  };


  //3-dimensional vector, derived from vecN. Inherits the operators from vecN,
  //can be vector of type float, int, etc.
  template <typename T>
  class Tvec3 : public vecN<T, 3>
  {
  public:
    typedef vecN<T,3> base;

    //uninitialized constructor
    inline Tvec3() {}

    //copy constructor
    inline Tvec3( const base& v) : base( v ) {}

    //vec3( x, y, z )
    inline Tvec3( T x, T y, T z )
    {
      base::data[0] = x;
      base::data[1] = y;
      base::data[2] = z;
    }

    //vec3( v, z )
    inline Tvec3( const Tvec2<T>& v, T z )
    {
      base::data[0] = v[0];
      base::data[1] = v[1];
      base::data[2] = z;
    }

    //vec3( x, v)
    inline Tvec3( T x , const Tvec2<T>& v )
    {
      base::data[0] = x;
      base::data[1] = v[0];
      base::data[2] = v[1];
    }

  };

  template<typename T>
  class Tvec4 : public vecN<T, 4>
  {
  public:

    typedef vecN<T,4> base;

    //uninitialized constructor
    inline Tvec4() {}

    //copy constructor
    inline Tvec4( const base& v ) : base( v ) {}

    //vec4( x, y, z, w )
    inline Tvec4( T x, T y, T z, T w)
    {
      base::data[0] = x;
      base::data[1] = y;
      base::data[2] = z;
      base::data[3] = w;
    }

    //vec4( v, x, w)
    inline Tvec4( const Tvec2<T>& v, T z, T w )
    {
      base::data[0] = v[0];
      base::data[1] = v[1];
      base::data[2] = z;
      base::data[3] = w;
    }

    //vec4( x, v, w)
    inline Tvec4( T x, const Tvec2<T>& v, T w )
    {
      base::data[0] = x;
      base::data[1] = v[0];
      base::data[2] = v[1];
      base::data[3] = w;
    }

    //vec4( x, y, v )
    inline Tvec4( T x, T y, const Tvec2<T>& v  )
    {
      base::data[0] = x;
      base::data[1] = y;
      base::data[2] = v[0];
      base::data[3] = v[1];
    }

    //vec4( u, v )
    inline Tvec4( const Tvec2<T>& u,  const Tvec2<T>& v )
    {
      base::data[0] = u[0];
      base::data[1] = u[1];
      base::data[2] = v[0];
      base::data[3] = v[1];
    }

    //vec4( v, w )
    inline Tvec4( const Tvec3<T>& v, T w )
    {
      base::data[0] = v[0];
      base::data[1] = v[1];
      base::data[2] = v[2];
      base::data[3] = w;
    }

    //vec4( x , v )
    inline Tvec4( T x, const Tvec3<T>& v )
    {
      base::data[0] = x;
      base::data[1] = v[0];
      base::data[2] = v[1];
      base::data[3] = v[2];
    }

  };

  //Define types of vector for different kinds of
  //variable based on above classes.
  typedef vecN<float, 1> vec1;
  typedef vecN<int, 1> ivec1;
  typedef vecN<unsigned int, 1> uvec1;
  typedef vecN<double, 1> dvec1;

  typedef Tvec2<float> vec2;
  typedef Tvec2<int> ivec2;
  typedef Tvec2<unsigned int> uvec2;
  typedef Tvec2<double> dvec2;

  typedef Tvec3<float> vec3;
  typedef Tvec3<int> ivec3;
  typedef Tvec3<unsigned int> uvec3;
  typedef Tvec3<double> dvec3;

  typedef Tvec4<float> vec4;
  typedef Tvec4<int> ivec4;
  typedef Tvec4<unsigned int> uvec4;
  typedef Tvec4<double> dvec4;


  //operators

  //scalar multiplication
  template<typename T, int n>
  static inline const vecN<T,n> operator * ( T x, const vecN<T,n>& v )
  {
    return v * x;
  }

  template<typename T>
  static inline const Tvec2<T> operator / ( T x, const Tvec2<T>& v )
  {
    return Tvec2<T>( x / v[0], x / v[1] );
  }

  template<typename T>
  static inline const Tvec3<T> operator / ( T x, const Tvec3<T>& v )
  {
    return Tvec3<T>( x / v[0], x / v[1], x / v[2] );
  }

  template<typename T>
  static inline const Tvec4<T> operator / ( T x, const Tvec4<T>& v )
  {
    return Tvec3<T>( x / v[0], x / v[1], x / v[2], x / v[3]  );
  }

  template<typename T, int len>
  static inline T dot( const vecN<T,len>& a, const vecN<T,len>& b )
  {
    T total = T(0);
    for( int n = 0; n < len; ++n )
    {
      total += a[n] * b[n];
    }
    return total;

  }

  template<typename T>
  static inline vecN<T,3> cross( const vecN<T,3>& a, const vecN<T,3>& b)
  {
    return Tvec3<T>( a[1] * b[2] - b[1] * a[2],
                     a[2] * b[0] - b[2] * a[0],
                     a[0] * b[1] - b[0] * a[1] );

  }

  template<typename T, int len>
  static inline T length( const vecN<T,len>& v )
  {
    T result(0);

    for( int i = 0; i < v.size(); ++i )
    {
      result += v[i] * v[i];
    }

    return (T)sqrt(result);
  }

  template<typename T, int len>
  static inline vecN<T,len> normalize( const vecN<T,len>& v)
  {
    return v / length(v);
  }

  template<typename T, int len>
  static inline T distance( const vecN<T,len>& a, const vecN<T,len>& b )
  {
    return length( b - a );
  }

  template<typename T, int len>
  static inline T angle( const vecN<T,len>& a, const vecN<T,len>& b )
  {
    return arccos( dot( a, b) );
  }

}



#endif
