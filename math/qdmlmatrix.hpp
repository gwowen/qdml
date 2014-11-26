#ifndef QDML_MATRIX_H
#define QDML_MATRIX_H

#include "qdmlvector.h"

namespace qdml
{
  template<typename T, const int w, const int h>
  class matNM
  {
  public:
    typedef class matNM<T,w,h> matType;
    typedef class vecN<T,h> vecType;

    //default constructor does nothing
    inline matNM()
    {
      //uninitialized variable
    }

    //copy constructor
    inline matNM( const matNM& that )
    {
      assign( that );
    }

    //construction from element type
    //explicit to prevent assignment from T
    explicit inline matNM( T f )
    {
      for( int n = 0; n < w; ++n )
        {
          data[n] = f;
        }
    }

    //assignment operator
    inline matNM& operator=( const matType &that )
    {
      assign( that );
      return *this;
    }

    inline matNM operator+( const matType &that ) const
    {
      matType result;
      for( int n = 0; n < w; ++n )
        result.data[n] = data[n] + that.data[n];
      return result;
    }

    inline matType& operator+=( const matType &that )
    {
      return ( *this = *this + that );
    }

    inline matType operator-( const matType &that ) const
    {
      matType result;
      for( int n = 0; n < w; ++n )
        result.data[n] = data[n] - that.data[n];
      return result;
    }

    inline matType& operator -=( const matType &that )
    {
      return( *this = *this - that );
    }

    inline matType operator*( const T& that ) const
    {
      matType result;
      for( int n = 0; n < w; ++n )
        data[n] = data[n] * that;
      return result;
    }

    inline matType& operator*=( const T& that )
    {
      for( int n = 0; n < w; ++n )
        data[n] = data[n] * that;
      return *this;
    }

    //matrix multiplication
    //only works for square matrices but will fix
    //when I can be arsed
    inline matType operator*( const matType &that ) const
    {
      matType result(0);

      for( int j = 0; j < w; ++j )
      {
        for( int i = 0; i < h; ++i )
        {
            T sum(0);

            for( int n = 0; n < w; ++n )
            {
              sum += data[n][i] * that[j][n];
            }

            result[j][i] = sum;
        }
      }

      return result;
    }

    inline matType operator*=( const matType &that )
    {
      return ( *this = *this * that );
    }

    inline vecType& operator[]( int n ) { return data[n]; }
    inline const vecType& operator[]( int n ) const { return data[n]; }
    inline operator T*() { return &data[0][0]; }
    inline operator const T*() const { return &data[0][0]; }

    inline matNM<T,h,w> transpose( void ) const
    {
        matNM<T,h,w> result;

        for( int y = 0; y < w; ++y )
          {
            for( int x = 0; x < h; ++x )
              {
                result[x][y] = data[y][x];
              }
          }

        return result;

    }

    static inline matType identity()
    {
      matType result(0);

      for( int i = 0; i < w; ++i )
      {
        result[i][i] = 1.0f;
      }

      return result;
    }

    static inline int width(void) { return w; }
    static inline int height(void) { return h; }

  protected:
    //column major data (essentially array of vectors)
    //as OpenGL is column major... should I do something
    //for DirectX in future?
    vecN<T,h> data[w];

    //assignment function - called from assignment operator and
    //copy constructors
    inline void assign( const matNM& that )
    {
      for( int n = 0; n < w; ++n )
        data[n] = that.data[n];
    }
  };

  template<typename T, const int N, const int M>
  static inline matNM<T,N,M> matrixCompMult( const matNM<T,N,M> &x, const matNM<T,N,M> &y )
  {
    matNM<T,N,M> result;

    for( int j = 0; j < M; ++j )
      {
        for( int i = 0; i < N; ++i )
          {
            result[i][j] = x[i][j] * y[i][j];
          }
      }

    return result;
  }
}


#endif
