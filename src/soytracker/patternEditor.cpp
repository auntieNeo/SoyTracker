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

    m_editorTools = new PatternEditorTools();  // FIXME: maybe just use this class as a local stack variable, since it's 8 bytes I could get rid of
//    cout << "size of PatternEditorTools: " << sizeof(PatternEditorTools) << endl;
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
//    m_pad = newpad(pattern->rows, 10);
    m_pad = newpad(pattern->rows, 100);

    m_editorTools->attachPattern(pattern);

    drawPattern();

    wprintw(m_pad, "test");
  }

  void PatternEditor::drawPattern()
  {
    /*
    cout << "m_pattern->rows: " << m_pattern->rows << endl;
    cout << "m_pattern->patternData: " << m_pattern->patternData << endl;
    */
    PatternTools tools;
    char *buffer = new char[9];
    for(int i = 0; i < m_pattern->rows; i++)
    {
      tools.setPosition(m_pattern, 0, i);
      // print the note name
      PatternTools::getNoteName(buffer, tools.getNote());
      mvwprintw(m_pad, i, 0, "%s", buffer);

      // print the instrument number
      pp_int32 instrument = tools.getInstrument();
      if(instrument <= 0x0F)
      {
        sprintf(buffer, ".%X", instrument);
      }
      else
      {
        snprintf(buffer, 3, "%X", instrument);
      }
      mvwprintw(m_pad, i, 3, "%s", buffer);

      // print the volume
      PatternTools::getVolumeName(buffer, 0);  // FIXME
      mvwprintw(m_pad, i, 5, "%s", buffer);

      // print the effect
      PatternTools::getEffectName(buffer, 0);  // FIXME
      mvwprintw(m_pad, i, 7, "%s", buffer);

      /*
      // print the hex values of each column in the pattern
//      mvwprintw(m_pad, i, 0, "row %d: ", i);
      for(int j = 0; j < 5; j++)
      {
        snprintf(buffer, 9, "%08X", *dataPos);
//        wprintw(m_pad, "0x%02X", *dataPos);
        mvwprintw(m_pad, i, j * 12, "0x%s", buffer);
        if(j != 5)
        {
          mvwprintw(m_pad, i, j * 12 + 10, ", ");
        }
        dataPos += 1;
      }
      */
    }
    delete [] buffer;
  }
}
