#include "engines/ags/lib/freetype-2.1.3/include/ft2build.h"
#include FT2_1_3_FREETYPE_H
#include FT2_1_3_TRIGONOMETRY_H

#include <math.h>
#include <stdio.h>

#define  PI   3.14159265358979323846
#define  SPI  (PI/FT2_1_3_ANGLE_PI)

/* the precision in 16.16 fixed float points of the checks. Expect */
/* between 2 and 5 noise LSB bits during operations, due to        */
/* rounding errors..                                               */
#define  THRESHOLD  64

  static  error = 0;

  static void
  test_cos( void )
  {
    FT2_1_3_Fixed  f1, f2;
    double    d1, d2;
    int       i;

    for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
    {
      f1 = FT2_1_3_Cos(i);
      d1 = f1/65536.0;
      d2 = cos( i*SPI );
      f2 = (FT2_1_3_Fixed)(d2*65536.0);

      if ( abs( f2-f1 ) > THRESHOLD )
      {
        error = 1;
        printf( "FT2_1_3_Cos[%3d] = %.7f  cos[%3d] = %.7f\n",
                (i >> 16), f1/65536.0, (i >> 16), d2 );
      }
    }
  }



  static void
  test_sin( void )
  {
    FT2_1_3_Fixed  f1, f2;
    double    d1, d2;
    int       i;

    for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
    {
      f1 = FT2_1_3_Sin(i);
      d1 = f1/65536.0;
      d2 = sin( i*SPI );
      f2 = (FT2_1_3_Fixed)(d2*65536.0);

      if ( abs( f2-f1 ) > THRESHOLD )
      {
        error = 1;
        printf( "FT2_1_3_Sin[%3d] = %.7f  sin[%3d] = %.7f\n",
                (i >> 16), f1/65536.0, (i >> 16), d2 );
      }
    }
  }


  static void
  test_tan( void )
  {
    FT2_1_3_Fixed  f1, f2;
    double    d1, d2;
    int       i;

    for ( i = 0; i < FT2_1_3_ANGLE_PI2-0x2000000; i += 0x10000 )
    {
      f1 = FT2_1_3_Tan(i);
      d1 = f1/65536.0;
      d2 = tan( i*SPI );
      f2 = (FT2_1_3_Fixed)(d2*65536.0);

      if ( abs( f2-f1 ) > THRESHOLD )
      {
        error = 1;
        printf( "FT2_1_3_Tan[%3d] = %.7f  tan[%3d] = %.7f\n",
                (i >> 16), f1/65536.0, (i >> 16), d2 );
      }
    }
  }


  static void
  test_atan2( void )
  {
    FT2_1_3_Fixed  c2, s2;
    double    l, a, c1, s1;
    int       i, j;

    for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
    {
      l  = 5.0;
      a  = i*SPI;

      c1 = l * cos(a);
      s1 = l * sin(a);

      c2 = (FT2_1_3_Fixed)(c1*65536.0);
      s2 = (FT2_1_3_Fixed)(s1*65536.0);

      j  = FT2_1_3_Atan2( c2, s2 );
      if ( j < 0 )
        j += FT2_1_3_ANGLE_2PI;

      if ( abs( i - j ) > 1 )
      {
        printf( "FT2_1_3_Atan2( %.7f, %.7f ) = %.5f, atan = %.5f\n",
                c2/65536.0, s2/65536.0, j/65536.0, i/65536.0 );
      }
    }
  }

  static void
  test_unit( void )
  {
    FT2_1_3_Vector  v;
    double     a, c1, s1;
    FT2_1_3_Fixed   c2, s2;
    int        i;

    for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
    {
      FT2_1_3_Vector_Unit( &v, i );
      a  = ( i*SPI );
      c1 = cos(a);
      s1 = sin(a);
      c2 = (FT2_1_3_Fixed)(c1*65536.0);
      s2 = (FT2_1_3_Fixed)(s1*65536.0);

      if ( abs( v.x-c2 ) > THRESHOLD ||
           abs( v.y-s2 ) > THRESHOLD )
      {
        error = 1;
        printf( "FT2_1_3_Vector_Unit[%3d] = ( %.7f, %.7f )  vec = ( %.7f, %.7f )\n",
                (i >> 16),
                v.x/65536.0, v.y/65536.0,
                c1, s1 );
      }
    }
  }


  static void
  test_length( void )
  {
    FT2_1_3_Vector  v;
    FT2_1_3_Fixed   l, l2;
    int        i;

    for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
    {
      l   = (FT2_1_3_Fixed)(500.0*65536.0);
      v.x = (FT2_1_3_Fixed)( l * cos( i*SPI ) );
      v.y = (FT2_1_3_Fixed)( l * sin( i*SPI ) );
      l2  = FT2_1_3_Vector_Length( &v );

      if ( abs( l2-l ) > THRESHOLD )
      {
        error = 1;
        printf( "FT2_1_3_Length( %.7f, %.7f ) = %.5f, length = %.5f\n",
                v.x/65536.0, v.y/65536.0, l2/65536.0, l/65536.0 );
      }
    }
  }


  static void
  test_rotate( void )
  {
    FT2_1_3_Fixed  c2, s2, c4, s4;
    FT2_1_3_Vector v;
    double    l, ra, a, c1, s1, cra, sra, c3, s3;
    int       i, j, rotate;

    for ( rotate = 0; rotate < FT2_1_3_ANGLE_2PI; rotate += 0x10000 )
    {
      ra  = rotate*SPI;
      cra = cos( ra );
      sra = sin( ra );

      for ( i = 0; i < FT2_1_3_ANGLE_2PI; i += 0x10000 )
      {
        l  = 500.0;
        a  = i*SPI;

        c1 = l * cos(a);
        s1 = l * sin(a);

        v.x = c2 = (FT2_1_3_Fixed)(c1*65536.0);
        v.y = s2 = (FT2_1_3_Fixed)(s1*65536.0);

        FT2_1_3_Vector_Rotate( &v, rotate );

        c3 = c1 * cra - s1 * sra;
        s3 = c1 * sra + s1 * cra;

        c4 = (FT2_1_3_Fixed)(c3*65536.0);
        s4 = (FT2_1_3_Fixed)(s3*65536.0);

        if ( abs( c4 - v.x ) > THRESHOLD ||
             abs( s4 - v.y ) > THRESHOLD )
        {
          error = 1;
          printf( "FT2_1_3_Rotate( (%.7f,%.7f), %.5f ) = ( %.7f, %.7f ), rot = ( %.7f, %.7f )\n",
                  c1, s1, ra,
                  c2/65536.0, s2/65536.0,
                  c4/65536.0, s4/65536.0 );
        }
      }
    }
  }


  int main( void )
  {
    test_cos();
    test_sin();
    test_tan();
    test_atan2();
    test_unit();
    test_length();
    test_rotate();

    if (!error)
      printf( "trigonometry test ok !\n" );

    return !error;
  }
