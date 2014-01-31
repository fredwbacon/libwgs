#ifndef SVM_H
#define SVM_H


#ifdef __cplusplus
extern "C" {
#endif

  typedef double   Vector3d[3];
  typedef double   Vector4d[4];
  typedef Vector4d Matrix44d[4];

  void          matrix44d_normal ( Matrix44d m44 );
  void          matrix44d_write ( FILE* fptr, Matrix44d m44 );

#ifdef __cplusplus
}
#endif
#endif /* SVM_H */
