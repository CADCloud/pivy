#ifndef COIN_SOSFVEC3F_H
#define COIN_SOSFVEC3F_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbVec3f.h>

#ifdef __PIVY__
%typemap(in) float xyz[3] (float temp[3]) {
  convert_SbVec3f_array($input, temp);
  $1 = temp;
}

%rename(setValue_fff) SoSFVec3f::setValue(const float x, const float y, const float z);
%rename(setValue_vec) SoSFVec3f::setValue(SbVec3f const &);

%feature("shadow") SoSFVec3f::setValue(const float xyz[3]) %{
def setValue(*args):
   if len(args) == 4:
      return apply(_pivy.SoSFVec3f_setValue_fff,args)
   elif isinstance(args[1],SbVec3f):
      return apply(_pivy.SoSFVec3f_setValue_vec,args)
   return apply(_pivy.SoSFVec3f_setValue,args)
%}
#endif

class COIN_DLL_API SoSFVec3f : public SoSField {
  typedef SoSField inherited;

  SO_SFIELD_HEADER(SoSFVec3f, SbVec3f, const SbVec3f &);

public:
  static void initClass(void);

#ifdef __PIVY__
  %extend {
        void __call__(float xyz[3]) {
          self->setValue(xyz);
        }
  }
#endif

  void setValue(const float x, const float y, const float z);
  void setValue(const float xyz[3]);
};

#endif // !COIN_SOSFVEC3F_H