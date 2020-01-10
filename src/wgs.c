/* 
 *  Copyright (C) 2016 Aerodyne Research - All Rights Reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "wgs.h"

#ifdef WIN32
#define snprintf  _snprintf
#endif

#ifndef TRUE
#define TRUE   1
#endif
#ifndef FALSE
#define FALSE  0
#endif

#ifdef MAX
#undef MAX
#endif
#define MAX(a,b)  (a)>(b) ? (a) : (b)

#ifndef M_PI
#define M_PI  3.1412592653589793238462643383
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
           if ( i != 0 && i < 80 )
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

      wf->maxid = MAX(wf->maxid,obj->nobj);

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

   matrix44d_identity ( object->matrix );

   return object;   
}


wgsObject*
wgs_object_copy ( wgsObject* obj, int id )
{
  int        nl, np;
  Vector3d*  points = NULL;
  wgsObject* nobj = NULL;
  
  if ( obj == NULL )
    return nobj;

  nobj = wgs_object_new (  );
  if ( nobj == NULL )
    return nobj;

  nl = obj->nline;
  np = obj->npnt;

  points = (Vector3d*)malloc( nl * np * sizeof(Vector3d) );
  if ( points == NULL )
    {
      wgs_object_free ( nobj );
      return NULL;
    }

  memcpy( nobj->name, obj->name, 81 );
  memcpy( points, obj->points, nl*np*sizeof(Vector3d) );
  memcpy( nobj->matrix, obj->matrix, sizeof(Matrix44d) );

  nobj->nobj   = id;
  nobj->nline  = obj->nline;
  nobj->npnt   = obj->npnt;
  nobj->isyml  = obj->isyml;
  nobj->rx     = obj->rx;
  nobj->ry     = obj->ry;
  nobj->rz     = obj->rz;
  nobj->tx     = obj->tx;
  nobj->ty     = obj->ty;
  nobj->tz     = obj->tz;
  nobj->xscale = obj->xscale;
  nobj->yscale = obj->yscale;
  nobj->zscale = obj->zscale;
  nobj->isymg  = obj->isymg;

  nobj->points = points;

  return nobj;
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


wgsObject*
wgs_object_reflect ( wgsObject* obj, int id )
{
  char       tmp[81];
  int        i, J, N, len, nl, np, j1, j2;
  wgsObject* refobj = NULL;
  Vector3d*  points;

  if ( obj->isyml <= 0 || obj->isyml > 3 )
    return refobj;

  refobj = wgs_object_copy ( obj, id );
  if ( refobj == NULL )
    return refobj;

  points = refobj->points;
  nl = obj->nline;
  np = obj->npnt;
  N = nl * np;

  /* We need to deal with duplicate object names */
  snprintf( tmp, 81, "%s", obj->name );
  len = strlen ( tmp );
  if ( len > 78 )
    {
       for ( i = 43; i < 81; i++ )
         tmp[i-2] = tmp[i];
    }

  snprintf( obj->name, 81, "%s#%d", tmp, 1 );
  snprintf( refobj->name, 81, "%s#%d", tmp, 2 );

  switch ( obj->isyml )
    {
    case 1: J = 1; break;
    case 2: J = 2; break;
    case 3: J = 0; break;
    default: J = 1; break;
    } 

  /* Apply the symmetry operation. */
  for ( i = 0; i < N; i++ )
    points[i][J] = -points[i][J];

  /* Now we need to swap the order of the points in each line 
   * so that the surface isn't inside out. */
  for ( i = 0; i < nl; i++ )
    {
      for ( j1 = 0, j2 = np-1; j1 <= j2; j1++, j2-- )
        {
          double x = points[i*np+j1][0];
          double y = points[i*np+j1][1];
          double z = points[i*np+j1][2];

          points[i*np+j1][0] = points[i*np+j2][0];
          points[i*np+j1][1] = points[i*np+j2][1];
          points[i*np+j1][2] = points[i*np+j2][2];

          points[i*np+j2][0] = x;
          points[i*np+j2][1] = y;
          points[i*np+j2][2] = z;
        }
    }

  return refobj;
}

int
wgs_object_needs_transform ( wgsObject* obj )
{
  if ( obj == NULL )
    return FALSE;

  if ( obj->rx != 0.0 || obj->ry != 0.0 || obj->rz != 0.0 )
    return TRUE;

  if ( obj->tx != 0.0 || obj->ty != 0.0 || obj->tz != 0.0 )
    return TRUE;

  if ( obj->xscale != 1.0 || obj->yscale != 1.0 || obj->zscale != 1.0 )
    return TRUE;

  return FALSE;
}

void
wgs_object_transform ( wgsObject* obj )
{
  int       i, N;
  Vector3d* points = NULL; 
  if ( obj == NULL )
    return;

  if ( !wgs_object_needs_transform ( obj ) )
    return;

  points = obj->points;
  if ( points == NULL )
    return;

  N = obj->nline * obj->npnt;

  for ( i = 0; i < N; i++ )
    matrix44d_mv ( obj->matrix, points[i], points[i] );

  /* Since we've already applied the transform, set the transform to the identity. */
  obj->rx = 
  obj->ry = 
  obj->rz = 
  obj->tx = 
  obj->ty = 
  obj->tz = 0.0;

  obj->xscale =
  obj->yscale =
  obj->zscale = 1.0;

  matrix44d_identity ( obj->matrix );
}


void
wgs_wireframe_convert_to_global ( wgsWireframe* wf )
{
  int        id;
  wgsObject* obj    = NULL;
  wgsObject* refobj = NULL;

  if ( wf == NULL )
    return;

  id = wf->maxid;

  /* Let's traverse the list of objects and see if they need to be transformed */
  for ( obj = wf->objects; obj != NULL; obj = obj->next )
    {
      /* See if there is a local symmetry plane and apply it. */
      if ( obj->isyml != 0 )
        {
          refobj = wgs_object_reflect ( obj, ++id );
          if ( refobj != NULL )
            {
              /* We've already applied our symmetry, so 
               * set both objects to have no symmetry. */
              refobj->isyml = 0;
              obj->isyml    = 0;

              /* We're going to play a little trick here.
               * We're inserting the new (reflected) object into
               * the list after the current object.  Then we transform
               * the current object, and set the current object to be
               * the newly reflected object. */
              refobj->next = obj->next;
              obj->next = refobj;
              wgs_object_transform ( obj );
              obj = refobj;
            }
        }
      
      /* If there was no symmetry plane, then this object is 
       * the same as we started with.  If there was a reflection,
       * then this is actually the object's reflection. */
      wgs_object_transform ( obj );
    }
}
