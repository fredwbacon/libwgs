#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "wgs.h"


#ifndef TRUE
#define TRUE   1
#endif
#ifndef FALSE
#define FALSE  0
#endif



void 
wgs_read_name ( FILE* fptr, char* name )
{
  int  i, done = FALSE;
  char c, c2;

  i = 0;
  while ( !done )
    {
      if ( feof(fptr) )
        {
          name[i] = 0;
          done = TRUE;
          continue;
        }

       c = fgetc ( fptr );
       switch ( c )
         {
         case 0x0D:
           c2 = fgetc ( fptr );
           if ( c2 != 0x0A )
             ungetc( c2, fptr);
         case 0x0A:
           name[i] = 0;
           done = TRUE;
           break;
         case '\'':
         case ' ':
           if ( i != 0 )
             name[i++] = c;
           break;
         default:
           if ( i < 80 )
             name[i++] = c;
           break;
         }
    }

  /* If there was a trailing ' and/or space, kill it */
  if ( i > 0 )
    {
      i--;
      while ( name[i] == '\'' || name[i] == ' ' )
        name[i--] = 0;
    }
}

wgsWireframe*
wgs_wireframe_new (  )
{
  wgsWireframe* wf = NULL;

  wf = (wgsWireframe*)malloc( sizeof( wgsWireframe) );
  if ( wf == NULL )
    return wf; 

  memset ( wf, 0, sizeof( wgsWireframe ) );

  return wf;
}


void
wgs_wireframe_free ( wgsWireframe* wf )
{
  if ( wf == NULL )
    return;

  while ( wf->objects != NULL )
    {
      wgsObject* obj = wf->objects;
      wf->objects = obj->next;
      obj->next = 0;
      wgs_object_free ( obj );
    }
  
  /* Clean our memory and free it */ 
  memset ( wf, 0, sizeof(wgsWireframe) );
 
  free ( (void*)wf );
}


wgsWireframe*
wgs_wireframe_read ( FILE* fptr )
{
  int           done = FALSE;
  wgsWireframe* wf = NULL;
  wgsObject*    obj = NULL;
  wgsObject*    current = NULL;

  if ( fptr == NULL )
    return wf;

  wf = wgs_wireframe_new ();   
  if ( wf == NULL )
    return wf;

  wgs_read_name ( fptr, wf->name );

  while ( !done )
    {
      obj = wgs_object_read ( fptr );
      if ( obj == NULL )
        {
          done = TRUE;
          continue;
        }

      if ( wf->objects == NULL )
        wf->objects = obj;
      else
        current->next = obj;
        
      current = obj;

      if ( feof( fptr ) )
        done = TRUE;
    }
   
  return wf;
}



wgsObject*
wgs_object_new ( )
{
   wgsObject* object = NULL;

   object = (wgsObject*)malloc(sizeof(wgsObject));
   if ( object == NULL )
     return object;

   /* Make sure that everything is properly zeroed out */
   memset( object, 0, sizeof(wgsObject) );

   matrix44d_normal ( object->matrix );

   return object;   
}


void
wgs_object_free ( wgsObject* object )
{
  if ( object == NULL )
    return;

  if ( object->points != NULL )
    {
      free((void*)object->points);
      object->points = NULL;
    }

  memset ( object, 0, sizeof(wgsObject) );
  
  free( (void*)object );
}



Vector3d*
wgs_object_allocate ( int nline, int npnt )
{
  if ( nline <= 0 || npnt <= 0 )
    return NULL;

  return (Vector3d*)malloc( nline * npnt * sizeof(Vector3d) );
}


Vector3d*
wgs_object_reallocate ( Vector3d* p, int nline, int npnt )
{
   if ( nline <= 0 || npnt <= 0 )
     return NULL;

   return (Vector3d*)realloc( (void*)p, nline * npnt * sizeof(Vector3d) );
}


wgsObject*
wgs_object_read ( FILE* fptr )
{
  int       i, cnt; 
  Matrix44d tmp;

  wgsObject* object = wgs_object_new ( ); 

  if ( object == NULL )
    return object;
   
  wgs_read_name ( fptr, object->name );

  /* Now we want to read the object data */
  cnt = fscanf ( fptr, "%d %d %d %d ", &(object->nobj), &(object->nline), &(object->npnt), &(object->isyml) );
  if ( cnt < 4 )
    {
      wgs_object_free( object );
      return NULL;
    }
                 
  cnt = fscanf ( fptr, "%lf %lf %lf ", &object->rx, &object->ry, &object->rz );
  if ( cnt < 3 )
    {           
      wgs_object_free( object );
      return NULL;
    }

  cnt = fscanf ( fptr, "%lf %lf %lf ", &object->tx, &object->ty, &object->tz );
  if ( cnt < 3 )
    { 
      wgs_object_free( object );
      return NULL;
    }
  
  cnt = fscanf ( fptr, "%lf %lf %lf ", &object->xscale, &object->yscale, &object->zscale );
  if ( cnt < 3 )
    { 
      wgs_object_free( object );
      return NULL;
    }
  
  cnt = fscanf( fptr, "%d \n", &object->isymg );

  if ( object->nline <= 0 || object->npnt <= 0 )
    {
       wgs_object_free ( object );
       return NULL;
    }

  object->points = wgs_object_allocate ( object->nline, object->npnt );
  if ( object->points == NULL )
    {
       wgs_object_free ( object );
       return NULL;
    }

  /* Start reading the coordinate data */
  for ( i = 0; i < object->nline * object->npnt; i++ )
    {
       cnt = fscanf( fptr, "%lf %lf %lf ", &object->points[i][0], &object->points[i][1], &object->points[i][2] );
       if ( cnt < 3 )
         continue; 
    }

  if ( i != object->nline*object->npnt )
    {
      wgs_object_free( object ); 
      object = NULL;
    }

  /* Now we want to compute the transformation matrix */
  matrix44d_xrotation_radians ( tmp, (object->rx)*M_PI/180.0 ); 
  matrix44d_mm ( tmp, object->matrix, object->matrix );

  matrix44d_yrotation_radians ( tmp, (object->ry)*M_PI/180.0 );
  matrix44d_mm ( tmp, object->matrix, object->matrix );

  matrix44d_zrotation_radians ( tmp, (object->rz)*M_PI/180.0 );
  matrix44d_mm ( tmp, object->matrix, object->matrix );

  matrix44d_set_translate ( object->matrix, object->tx, object->ty, object->tz ); 
  matrix44d_set_scale ( object->matrix, object->xscale, object->yscale, object->zscale );

  return object;
}

