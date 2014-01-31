#ifndef WGS_H
#define WGS_H

#include "svm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _wgsObject  wgsObject;
typedef struct _wgsWireframe wgsWireframe;

struct _wgsObject {
   char         name[81];
   int          nobj;
   int          nline;
   int          npnt;
   int          isyml;
   double       rx;
   double       ry;
   double       rz;
   double       tx;
   double       ty;
   double       tz;
   double       xscale;
   double       yscale;
   double       zscale;
   int          isymg;
   Matrix44d    matrix;
   Vector3d*    points;
   wgsObject*   next;
};


struct _wgsWireframe {
  char        name[81];
  wgsObject*  objects;
};


  wgsWireframe* wgs_wireframe_new (  );
  void          wgs_wireframe_free ( wgsWireframe* );
  wgsWireframe* wgs_wireframe_read ( FILE* );

  wgsObject*    wgs_object_new ( );
  void          wgs_object_free ( wgsObject* );
  Vector3d*     wgs_object_allocate ( int, int );
  Vector3d*     wgs_object_reallocate ( Vector3d*, int, int );
  wgsObject*    wgs_object_read ( FILE* );

#ifdef __cplusplus
}
#endif
#endif /* WGS_H */
