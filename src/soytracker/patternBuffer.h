#ifndef PATTERN_BUFFER_H_
#define PATTERN_BUFFER_H_

#include "XModule.h"

namespace SoyTracker
{
  class PatternEditor;

  class PatternBuffer
  {
    public:
      PatternBuffer(TXMPattern *pattern);
      ~PatternBuffer();

      TXMPattern *pattern() const { return m_pattern; }

      void attachEditor(PatternEditor *editor);

    private:
      TXMPattern *m_pattern;
//      vector<PatternEditor *editors> m_attachedEditors;
  };
}

#endif

