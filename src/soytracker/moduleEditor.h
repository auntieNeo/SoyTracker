#ifndef MODULE_EDITOR_H_
#define MODULE_EDITOR_H_

#include "XModule.h"

namespace SoyTracker
{
  class ModuleEditor
  {
    public:
      ModuleEditor();
      ~ModuleEditor();

    private:
      XModule *m_module;
  };
}

#endif
