#ifndef COIN_SOWRITEACTION_H
#define COIN_SOWRITEACTION_H

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

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>

class SoVRMLPROTODef;
class SoVRMLEXTERNPROTODef;

#ifdef __PIVY__
%rename(SoWriteAction_out) SoWriteAction::SoWriteAction(SoOutput * out);

%feature("shadow") SoWriteAction::SoWriteAction %{
def __init__(self,*args):
   if len(args) == 1:
      self.this = apply(_pivy.new_SoWriteAction_out,args)
      self.thisown = 1
      return
   self.this = apply(_pivy.new_SoWriteAction,args)
   self.thisown = 1
%}

%rename(continueToApply_nod) SoWriteAction::continueToApply(SoNode * node);

%feature("shadow") SoWriteAction::continueToApply(SoPath * path) %{
def continueToApply(*args):
   if isinstance(args[1], SoNode):
      return apply(_pivy.SoWriteAction_continueToApply_nod,args)
   return apply(_pivy.SoWriteAction_continueToApply,args)
%}
#endif

class COIN_DLL_API SoWriteAction : public SoAction {
  typedef SoAction inherited;

  SO_ACTION_HEADER(SoWriteAction);

public:
  SoWriteAction(void);
  SoWriteAction(SoOutput * out);
  virtual ~SoWriteAction();

  static void initClass(void);

  SoOutput * getOutput(void) const;

  void continueToApply(SoNode * node);
  void continueToApply(SoPath * path);

protected:
  virtual void beginTraversal(SoNode * node);
  virtual SbBool shouldCompactPathLists(void) const;

private:
  void commonConstructor(SoOutput * out);

  SoOutput * outobj;
  SbBool localoutputalloc;
  SbBool continuing;
};

#endif // !COIN_SOWRITEACTION_H