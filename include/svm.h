#ifndef SVM_H
#define SVM_H


#ifdef __cplusplus
extern "C" {
#endif

  typedef double   Vector3d[3];
  typedef double   Vector4d[4];
  typedef Vector4d Matrix44d[4];

  void matrix44d_normal ( Matrix44d m44 );
  void matrix44d_write ( FILE* fptr, Matrix44d m44 );

  void matrix44d_mm ( Matrix44d, Matrix44d, Matrix44d );
  void matrix44d_mv ( Matrix44d, Vector3d, Vector3d );
  void matrix44d_xrotation_radians ( Matrix44d, double );
  void matrix44d_yrotation_radians ( Matrix44d, double );
  void matrix44d_zrotation_radians ( Matrix44d, double );
  void matrix44d_set_translate ( Matrix44d, double, double, double );
  void matrix44d_set_scale ( Matrix44d, double, double, double );

#ifdef __cplusplus
}
#endif
#endif /* SVM_H */
