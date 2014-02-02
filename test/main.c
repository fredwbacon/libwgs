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

#if 0
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
#endif
  
  wgs_wireframe_convert_to_global ( wf );

  fprintf ( stdout, "%s\n", wf->name );
  fprintf ( stdout, "CM 0\n" );
  fprintf ( stdout, "-10000.000-10000.000-10000.000           10000.000 10000.000 10000.000\n" );
  fprintf ( stdout, "%5d\n", 0 );

  for ( obj = wf->objects; obj != NULL; obj = obj->next )
    fprintf( stdout, "%-40s%5d%5d%5d%5d%5d\n", obj->name, 1, 0, 0, 0, 0 );

  fprintf ( stdout, "END PART NAMES\n" );
  for ( obj = wf->objects; obj != NULL; obj = obj->next )
    {
      int i, j, k;

      fprintf( stdout, "%-40s%-40s\n", obj->name, obj->name );
      fprintf( stdout, "%5d%5d%5d%5d%5d%5d%5d\n", 1, 0, 0, 0, 0, 0, 0 );
      fprintf( stdout, "%5d%5d\n", obj->npnt, obj->nline );
      // matrix44d_write ( stderr, obj->matrix );
      for ( i = 0, k = 0; i < obj->nline; i++ )
        {
          for ( j = 0; j < obj->npnt; j++, k++ )
            {
              fprintf( stdout, "%10.3f%10.3f%10.3f\n", obj->points[k][0], obj->points[k][1], obj->points[k][2] );
            }
        }
    }

  fprintf( stdout, "END OF FILE\n" );

  wgs_wireframe_free ( wf );

  return 0;
}
