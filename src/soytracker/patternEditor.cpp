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

#include "patternEditor.h"

#include "PatternTools.h"
#include "XModule.h"

#include <iostream>
using namespace std;

namespace SoyTracker
{
  PatternEditor::PatternEditor()
  {
    m_pad = NULL;

    m_pattern = NULL;

    m_editorTools = new PatternEditorTools();
    cout << "size of PatternEditorTools: " << sizeof(PatternEditorTools) << endl;
  }

  PatternEditor::~PatternEditor()
  {
    delwin(m_pad);
    delete m_editorTools;
  }

  void PatternEditor::setPattern(TXMPattern *pattern)
  {
    m_pattern = pattern;

    delwin(m_pad);
    m_pad = newpad(pattern->rows, 10);

    m_editorTools->attachPattern(pattern);

    drawPattern();
  }

  void PatternEditor::drawPattern()
  {
    char *buffer = new char[4];
    pp_uint32 *dataPos = reinterpret_cast<pp_uint32 *>(m_pattern->patternData);
    for(int i = 0; i < m_pattern->rows; i++)
    {
      // print the note name
      PatternTools::getNoteName(buffer, *dataPos);
      mvwprintw(m_pad, i, 0, "%s", buffer);

      // print the instrument number
      dataPos += 1;
      if(*dataPos <= 0x0F)
      {
        sprintf(buffer, ".%X", *dataPos);
      }
      else
      {
        snprintf(buffer, 3, "%X", *dataPos);
      }
      wprintw(m_pad, "%s", buffer);

      // print the volume
      dataPos += 1;
      PatternTools::getVolumeName(buffer, *dataPos);
      wprintw(m_pad, "%s", buffer);

      // print the effect
      dataPos += 1;
      PatternTools::getEffectName(buffer, *dataPos);
      wprintw(m_pad, "%s", buffer);

      dataPos += 1;
    }
    delete [] buffer;
  }
}
