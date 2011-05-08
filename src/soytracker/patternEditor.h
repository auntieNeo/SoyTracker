/***************************************************************************
 *   Copyright 2011 Jonathan Glines.                                       *
 *   auntieNeo@gmail.com                                                   *
 *                                                                         *
 *   This file is part of SoyTracker.                                      *
 *                                                                         *
 *   SoyTracker is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   SoyTracker is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with SoyTracker.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#ifndef PATTERN_EDITOR_H_
#define PATTERN_EDITOR_H_

#include "PatternEditorTools.h"
#include "trackerWindow.h"

namespace SoyTracker
{
  class PatternBuffer;

  class PatternEditor : public TrackerWindow
  {
    public:
      PatternEditor();
      PatternEditor(PatternBuffer *patternBuffer);
      ~PatternEditor();

      void setPatternBuffer(PatternBuffer *patternBuffer);
      PatternBuffer *patternBuffer() { return m_patternBuffer; }

    protected:
      void resizeEvent(int newLines, int newColumns);

    private:
      PatternBuffer *m_patternBuffer;

      PatternEditorTools *m_editorTools;

      int m_patternWidth, m_patternHeight;

      void drawPattern(int minrow, int mincol, int maxrow, int maxcol);
      void drawPattern(const PatternEditorTools::Position &ss, const PatternEditorTools::Position &se);
  };
}

#endif
