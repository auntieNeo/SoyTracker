#include "patternBuffer.h"

namespace SoyTracker
{
  PatternBuffer::PatternBuffer(TXMPattern *pattern)
  {
    m_pattern = pattern;
  }

  PatternBuffer::~PatternBuffer()
  {
  }

  void attachEditor(PatternEditor *editor)
  {
    // TODO: attach an editor
  }
}
