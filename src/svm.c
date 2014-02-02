#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "svm.h"

void
matrix44d_identity ( Matrix44d m44 )
{
   memset ( m44, 0, sizeof( Matrix44d ) );
   m44[0][0] =
   m44[1][1] =
   m44[2][2] = 
   m44[3][3] = 1.0;
}


void
matrix44d_write ( FILE* fptr, Matrix44d m44 )
{
  FILE *out = fptr;

  if ( out == NULL )
    out = stdout;

  fprintf( out, "\t%12.5f %12.5f %12.5f %12.5f\n", m44[0][0], m44[0][1], m44[0][2], m44[0][3] );
  fprintf( out, "\t%12.5f %12.5f %12.5f %12.5f\n", m44[1][0], m44[1][1], m44[1][2], m44[1][3] );
  fprintf( out, "\t%12.5f %12.5f %12.5f %12.5f\n", m44[2][0], m44[2][1], m44[2][2], m44[2][3] );
  fprintf( out, "\t%12.5f %12.5f %12.5f %12.5f\n", m44[3][0], m44[3][1], m44[3][2], m44[3][3] );
}



void
matrix44d_set_translate ( Matrix44d m44, double tx, double ty, double tz )
{
  m44[0][3] = tx;
  m44[1][3] = ty;
  m44[2][3] = tz;
}


void
matrix44d_set_scale ( Matrix44d m44, double xscale, double yscale, double zscale )
{
  m44[3][0] = xscale;
  m44[3][1] = yscale;
  m44[3][2] = zscale;
}


void
matrix44d_xrotation_radians ( Matrix44d m44, double phi )
{
   matrix44d_identity ( m44 );
 
   m44[1][1] = cos(phi);
   m44[2][2] = cos(phi);
   m44[1][2] = sin(phi);
   m44[2][1] = -sin(phi);
}


void
matrix44d_yrotation_radians ( Matrix44d m44, double theta )
{
  matrix44d_identity ( m44 );
  
  m44[0][0] = cos(theta);
  m44[2][2] = cos(theta);
  m44[0][2] = sin(theta);
  m44[2][0] = -sin(theta);
}


void
matrix44d_zrotation_radians ( Matrix44d m44, double psi )
{
  matrix44d_identity ( m44 );

  m44[0][0] = cos(psi);
  m44[1][1] = cos(psi);
  m44[0][1] = sin(psi);
  m44[1][0] = -sin(psi);
}


void
matrix44d_mm ( Matrix44d a44, Matrix44d b44, Matrix44d c44 )
{
  int i;
  Matrix44d t44;

  for ( i = 0; i < 4; i++ )
    {
      t44[i][0] = a44[i][0]*b44[0][0] + a44[i][1]*b44[1][0] + a44[i][2]*b44[2][0] + a44[i][3]*b44[3][0];
      t44[i][1] = a44[i][0]*b44[0][1] + a44[i][1]*b44[1][1] + a44[i][2]*b44[2][1] + a44[i][3]*b44[3][1];
      t44[i][2] = a44[i][0]*b44[0][2] + a44[i][1]*b44[1][2] + a44[i][2]*b44[2][2] + a44[i][3]*b44[3][2];
      t44[i][3] = a44[i][0]*b44[0][3] + a44[i][1]*b44[1][3] + a44[i][2]*b44[2][3] + a44[i][3]*b44[3][3]; 
    }

  memcpy ( c44, t44, sizeof(Matrix44d) );
}


void
matrix44d_mv ( Matrix44d m44, Vector3d pin, Vector3d pout )
{
   Vector3d tmp;

   tmp[0] = m44[0][0] * pin[0] + m44[0][1] * pin[1] + m44[0][2] * pin[2] + m44[0][3];
   tmp[1] = m44[1][0] * pin[0] + m44[1][1] * pin[1] + m44[1][2] * pin[2] + m44[1][3];
   tmp[2] = m44[2][0] * pin[0] + m44[2][1] * pin[1] + m44[2][2] * pin[2] + m44[2][3];
   
   memcpy ( pout, tmp, sizeof(Vector3d) );
}

