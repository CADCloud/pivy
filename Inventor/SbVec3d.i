%{
static void
convert_SbVec3d_array(PyObject *input, double temp[3])
{
  if (PySequence_Check(input) && (PySequence_Size(input) == 3) &&
      PyNumber_Check(PySequence_GetItem(input, 0)) && 
      PyNumber_Check(PySequence_GetItem(input, 1)) && 
      PyNumber_Check(PySequence_GetItem(input, 2))) {
    temp[0] = PyFloat_AsDouble(PySequence_GetItem(input, 0));
    temp[1] = PyFloat_AsDouble(PySequence_GetItem(input, 1));
    temp[2] = PyFloat_AsDouble(PySequence_GetItem(input, 2));
  } else {
    PyErr_SetString(PyExc_TypeError, "expected a sequence with 3 doubles");
    PyErr_Print();
  } 
}
%}

%typemap(in) double v[3] (double temp[3]) {
  convert_SbVec3d_array($input, temp);
  $1 = temp;
}

%typemap(typecheck) double v[3] {
  $1 = PySequence_Check($input) ? 1 : 0;
}

/* for some strange reason the %apply directive below doesn't work 
 * for this class on getValue(f,f,f)...
 * created this typemap for getValue(void) instead as a workaround.
 */
%typemap(out) double * {
  int i;
  $result = PyTuple_New(3);
  
  for (i=0; i<3; i++) {
    PyTuple_SetItem($result, i, PyFloat_FromDouble((double)(*($1+i))));
  }
}

%rename(SbVec3d_vec) SbVec3d::SbVec3d(const double v[3]);
%rename(SbVec3d_fff) SbVec3d::SbVec3d(const double x, const double y, const double z);
%rename(SbVec3d_pl_pl_pl) SbVec3d::SbVec3d(const SbPlane & p0, const SbPlane & p1, const SbPlane & p2);

%feature("shadow") SbVec3d::SbVec3d %{
def __init__(self,*args):
   newobj = None
   if len(args) == 1:
      if isinstance(args[0], SbVec3d):
         newobj = _coin.new_SbVec3d()
         newobj.setValue(args[0])
      else:
         newobj = apply(_coin.new_SbVec3d_vec,args)
   elif len(args) == 3:
      if isinstance(args[0], SbPlane):
         newobj = apply(_coin.new_SbVec3d_pl_pl_pl,args)
      else:
         newobj = apply(_coin.new_SbVec3d_fff,args)
   else:
      newobj = apply(_coin.new_SbVec3d,args)
   if newobj:
      self.this = newobj.this
      self.thisown = 1
      del newobj.thisown
%}

/* add operator overloading methods instead of the global functions */
%extend SbVec3d {
  SbVec3d __add__(const SbVec3d &u) { return *self + u; }
  SbVec3d __sub__(const SbVec3d &u) { return *self - u; }
  SbVec3d __mul__(const double d) { return *self * d; }
  SbVec3d __rmul__(const double d) { return *self * d; }
  SbVec3d __div__(const double d) { return *self / d; }
  int __eq__(const SbVec3d &u) { return *self == u; }
  int __nq__(const SbVec3d &u) { return *self != u; }
  // add a method for wrapping c++ operator[] access
  double __getitem__(int i) { return (self->getValue())[i]; }
  void  __setitem__(int i, double value) { (*self)[i] = value; }
}

%apply double *OUTPUT { double & x, double & y, double & z };

%ignore SbVec3d::getValue(double & x, double & y, double & z) const;
