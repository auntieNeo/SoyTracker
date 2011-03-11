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

#include "patternEditor.cpp"

namespace SoyTracker
{
  PatternEditor::PatternEditor()
  {
    m_pad = NULL;
    m_tracks = new WINDOW*[256];
    memset(m_tracks, NULL, 256);

    m_editorTools = new PatternEditorTools();
  }

  PatternEditor::~PatternEditor()
  {
    delwin(m_pad);
    for(int i = 0; i < 256; i++)
    {
      if(m_tracks[i] != NULL)
      {
        delwin(m_tracks[i]);
      }
    }
    delete [] m_tracks;
  }

  void setPattern(TXMPattern *pattern)
  {
    m_editorTools->attachPattern(pattern);
  }

  void drawPattern(WINDOW *track, const TXMPattern *pattern)
  {
  }
}
