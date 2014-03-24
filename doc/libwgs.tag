<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>svm.c</name>
    <path>/home/bacon/Projects/ARISoftware/libwgs/src/</path>
    <filename>svm_8c</filename>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_identity</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a7582981fc49312318bbf2a68ee53c4c0</anchor>
      <arglist>(Matrix44d m44)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_write</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>acaeef2d55b408fa186e49b9f021c9ea1</anchor>
      <arglist>(FILE *fptr, Matrix44d m44)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_set_translate</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>ac39f1393d2f5a86af3637ef8b62c66b3</anchor>
      <arglist>(Matrix44d m44, double tx, double ty, double tz)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_set_scale</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a9866b8f35b4ed4638a6976e5bce74ec2</anchor>
      <arglist>(Matrix44d m44, double xscale, double yscale, double zscale)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_xrotation_radians</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a39148b2562bed6e9bfbe810a578fb566</anchor>
      <arglist>(Matrix44d m44, double phi)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_yrotation_radians</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>ae6d094067b5fbe7eb386bfd7f16009d5</anchor>
      <arglist>(Matrix44d m44, double theta)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_zrotation_radians</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a2fe9cc96d0a25cda7dbcfb140deb8f68</anchor>
      <arglist>(Matrix44d m44, double psi)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_mm</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a88a4be7531fdb64b41f2d886117c2e7d</anchor>
      <arglist>(Matrix44d a44, Matrix44d b44, Matrix44d c44)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>matrix44d_mv</name>
      <anchorfile>svm_8c.html</anchorfile>
      <anchor>a6c83a623ec3c288c820d6f58e135f09e</anchor>
      <arglist>(Matrix44d m44, Vector3d pin, Vector3d pout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>wgs.c</name>
    <path>/home/bacon/Projects/ARISoftware/libwgs/src/</path>
    <filename>wgs_8c</filename>
    <member kind="define">
      <type>#define</type>
      <name>TRUE</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>aa8cecfc5c5c054d2875c03e77b7be15d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FALSE</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>aa93f0eb578d23995850d61f7d61c55c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>afa99ec4acc4ecb2dc3c2d05da15d0e3f</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>M_PI</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>ae71449b1cc6e6250b91f539153a7a0d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wgs_read_name</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a40613a3ec80b6172b296d1af74b4fd02</anchor>
      <arglist>(FILE *fptr, char *name)</arglist>
    </member>
    <member kind="function">
      <type>wgsWireframe *</type>
      <name>wgs_wireframe_new</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>aca827bd3ee82263245de29cd904241b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wgs_wireframe_free</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>ac02680ab7c5def6b7753d7163356f0a2</anchor>
      <arglist>(wgsWireframe *wf)</arglist>
    </member>
    <member kind="function">
      <type>wgsWireframe *</type>
      <name>wgs_wireframe_read</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a3edd80afcf2812221ee5800cf95d8259</anchor>
      <arglist>(FILE *fptr)</arglist>
    </member>
    <member kind="function">
      <type>wgsObject *</type>
      <name>wgs_object_new</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a80555428160096300888bf440ed46f41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wgsObject *</type>
      <name>wgs_object_copy</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a00354bc4f9e11e9dfcdc217778fef4c6</anchor>
      <arglist>(wgsObject *obj, int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wgs_object_free</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a0c6368554f089ea0b5fb2fc758339739</anchor>
      <arglist>(wgsObject *object)</arglist>
    </member>
    <member kind="function">
      <type>Vector3d *</type>
      <name>wgs_object_allocate</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>abc29f4282912734b4df9c914f984b046</anchor>
      <arglist>(int nline, int npnt)</arglist>
    </member>
    <member kind="function">
      <type>Vector3d *</type>
      <name>wgs_object_reallocate</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a43cc589de9d411a8755fa8ae1971b1e6</anchor>
      <arglist>(Vector3d *p, int nline, int npnt)</arglist>
    </member>
    <member kind="function">
      <type>wgsObject *</type>
      <name>wgs_object_read</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>aab29ffb71cc92166de3ade05313f2ea5</anchor>
      <arglist>(FILE *fptr)</arglist>
    </member>
    <member kind="function">
      <type>wgsObject *</type>
      <name>wgs_object_reflect</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>ac688d5f7a1f30a22ff3dfbf13a2f6fdb</anchor>
      <arglist>(wgsObject *obj, int id)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wgs_object_needs_transform</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>af9c6d3f4fc32506c6806ed811fb4e1bf</anchor>
      <arglist>(wgsObject *obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wgs_object_transform</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a077abc770338b61fd902416b33580ed1</anchor>
      <arglist>(wgsObject *obj)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wgs_wireframe_convert_to_global</name>
      <anchorfile>wgs_8c.html</anchorfile>
      <anchor>a5cadd93880921b4c0289c19c5575e346</anchor>
      <arglist>(wgsWireframe *wf)</arglist>
    </member>
  </compound>
</tagfile>
