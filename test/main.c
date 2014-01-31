#include <stdlib.h>
#include <stdio.h>
#include "wgs.h"


int
main( int argc, char* argv[] )
{
  wgsWireframe* wf   = NULL;
  wgsObject*    obj  = NULL;
  FILE*         fptr = NULL;

  if ( argc < 2 )
    {
       fprintf( stderr, "Usage: wgsreader filename\n" );
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

  fprintf( stderr, "%s\n", wf->name );
  obj = wf->objects;
  while ( obj != NULL )
    {
       int i, j, k;

       fprintf( stderr, "\t%s\n", obj->name );
       matrix44d_write ( stderr, obj->matrix );
       for ( i = 0, k = 0; i < obj->nline; i++ )
         {
           for ( j = 0; j < obj->npnt; j++, k++ )
             {
               fprintf( stderr, "%12.5f %12.5f %12.5f ", obj->points[k][0], obj->points[k][1], obj->points[k][2] );
               if ( j%2 == 1 || j == obj->npnt-1 )
                 fprintf ( stderr, "\n" );
             }
         }
       obj = obj->next;
    }
  

  wgs_wireframe_free ( wf );

  return 0;
}
