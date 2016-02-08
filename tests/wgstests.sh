#!/bin/bash
. functions

cat > main.c << EOF
#include <stdlib.h>
#include <stdio.h>
#include "wgs.h"


int
main( int argc, char* argv[] )
{
  wgsWireframe* wf   = NULL;
  wgsObject*    obj  = NULL;
  FILE*         fptr = NULL;
  FILE*         fout = NULL;

  if ( argc < 3 )
    {
       fprintf( stderr, "Usage: wgsreader filename.wgs filename.wir\n" );
       return 1;
    }

  fptr = fopen( argv[1], "r" );
  if ( fptr == NULL )
    {
       fprintf( stderr, "Unable to open the file: %s\n", argv[1] );
       return 1;
    }

  wf = wgs_wireframe_read ( fptr );
  fclose(fptr);

  if ( wf == NULL )
    {
       fprintf ( stderr, "Unable to read the file: %s\n", argv[1] );
       return 1;
    }

  wgs_wireframe_convert_to_global ( wf );

  fout = fopen ( argv[2], "w" );
  if ( fout == NULL )
    {
      fprintf ( stderr, "Unable to open the output file %s\n", argv[2] );
      fout = stdout;
    }

  /* Now, as a test, we write out a quick conversion to SPIRITS Wireframe format */
  fprintf ( fout, "%s\n", wf->name );
  fprintf ( fout, "CM 0\n" );
  fprintf ( fout, "-10000.000-10000.000-10000.000           10000.000 10000.000 10000.000\n" );
  fprintf ( fout, "%5d\n", 0 );

  for ( obj = wf->objects; obj != NULL; obj = obj->next )
    fprintf( fout, "%-40s%5d%5d%5d%5d%5d\n", obj->name, 1, 0, 0, 0, 0 );

  fprintf ( fout, "END PART NAMES\n" );
  for ( obj = wf->objects; obj != NULL; obj = obj->next )
    {
      int i, j, k;

      fprintf( fout, "%-40s%-40s\n", obj->name, obj->name );
      fprintf( fout, "%5d%5d%5d%5d%5d%5d%5d\n", 1, 0, 0, 0, 0, 0, 0 );
      fprintf( fout, "%5d%5d\n", obj->npnt, obj->nline );
      // matrix44d_write ( stderr, obj->matrix );
      for ( i = 0, k = 0; i < obj->nline; i++ )
        {
          for ( j = 0; j < obj->npnt; j++, k++ )
            {
              fprintf( fout, "%10.3f%10.3f%10.3f\n", obj->points[k][0], obj->points[k][1], obj->points[k][2] );
            }
        }
    }

  fprintf( fout, "END OF FILE\n" );

  if ( fout != stdout )
    fclose ( fout );

  wgs_wireframe_free ( wf );

  return 0;
}
EOF

gcc -o wgstests -Wall -g main.c -I../include -L../$SYSTEM-$ARCH/libwgs/lib/ -lwgs -lm >& wgstests.out

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/cylinders.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/cylinders.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for cylinders.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of cylinders.wir" wgstests.wir fa4f114261edb5c6d1a313c173a233366f19fd65
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/delta1.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/delta1.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for delta1.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of delta2.wir" wgstests.wir 79301f2745dc20ef491ce00be6a67b753eee53e9
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/make.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/make.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for make.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of make.wir" wgstests.wir 146b9d6ba898a0ca2eb82e85716df55c1b64b08c
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/sh.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/sh.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for sh.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of sh.wir" wgstests.wir f73e18eb2e1709a02def505ad908a1ef3132a7a0
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/tnd4211.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/tnd4211.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for tnd4211.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of tnd4211.wir" wgstests.wir 42933dd399cd1533f20e879c65f51c415041b5f2
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/tnd7505.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/tnd7505.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for tnd7505.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of tnd7505.wir" wgstests.wir ecdb1c35e36bf3a7874b21d67cc433195663c736
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/wbf.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/wbf.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for wbf.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of wbf.wir" wgstests.wir 5414d1a5f99434308ad35d5c0cded04f4f74375b
check_valgrind

if [[ $SYSTEM == "Linux" ]]; then
  $VALGRIND ./wgstests data/wdcase1.wgs wgstests.wir fail.wir >& wgstests.out
else
  ./wgstests data/wdcase1.wgs wgstests.wir fail.wir >& wgstests.out
fi

check_file "Check output for wdcase1.wgs" wgstests.out da39a3ee5e6b4b0d3255bfef95601890afd80709
check_file "Check wireframe of wdcase1.wir" wgstests.wir 17703fc1f5ac9152db4f6017a263230d504afe01
check_valgrind

print_summary
