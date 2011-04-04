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

#include "common.h"
#include "patternBuffer.h"
#include "patternEditor.h"

#include "PatternTools.h"
#include "XModule.h"

#define CHANNEL_WIDTH 10
#define CHANNEL_MARGIN 3

#include <iostream>
using namespace std;

namespace SoyTracker
{
  /**
   * \class PatternEditor
   * The PatternEditor provides a curses interface to edit the patterns in a module.
   *
   * PatternEditor derives from the TrackerWindow class to provide the interface.
   */
  PatternEditor::PatternEditor()
  {
    m_patternBuffer = NULL;

    m_editorTools = new PatternEditorTools();
  }

  PatternEditor::PatternEditor(PatternBuffer *patternBuffer)
  {
    m_editorTools = new PatternEditorTools();
    setPatternBuffer(patternBuffer);
  }

  PatternEditor::~PatternEditor()
  {
    delete m_editorTools;
  }

  void PatternEditor::setPatternBuffer(PatternBuffer *patternBuffer)
  {
    m_patternBuffer = patternBuffer;

    TXMPattern *pattern = m_patternBuffer->pattern();

    assert(pattern->effnum == 2);  // the code assumes two effects, one volume effect and one custom effect

    resizeEditorPad(pattern->rows, CHANNEL_WIDTH * pattern->channum + CHANNEL_MARGIN * (pattern->channum - 1));

    m_editorTools->attachPattern(pattern);

    struct PatternEditorTools::Position start = {0, 0, 1}, end = {pattern->channum, pattern->rows, 7};
    drawPattern(start, end);
  }

  void PatternEditor::drawPattern(const PatternEditorTools::Position &ss, const PatternEditorTools::Position &se)
  {
    PatternTools tools;
    TXMPattern *pattern = m_patternBuffer->pattern();
    char *buffer = new char[9];
    tools.setPosition(pattern, ss.channel, ss.row);
    for(int row = ss.row; row <= se.row; row++)
    {
      int inner = ss.inner;
      int pos = CHANNEL_WIDTH * ss.channel + CHANNEL_MARGIN * ss.channel;
      switch(inner)
      {
        case 7:
        case 5:
        case 6:
          pos += 1;
        case 4:
          pos += 2;
        case 3:
          pos += 2;
        case 2:
          pos += 3;
      }
      for(int chan = ss.channel; chan <= se.channel; chan++)
      {
        tools.setPosition(pattern, chan, row);
          if(chan != se.channel)
          {
            switch(inner)  // FIXME: milkytracker has only 6 columns for the inner selection value, but 7 is the highest value allowed for inner... figure out if this value is indexed from 0 or from 1
            {
              case 1:
                // print the note name
                PatternTools::getNoteName(buffer, tools.getNote());
                wcolor_set(editorPad(), NOTE_COLOR, NULL);
                mvwprintw(editorPad(), row, pos, "%s", buffer);
                pos += 3;
              case 2:
                {
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
                  wcolor_set(editorPad(), INSTRUMENT_COLOR, NULL);
                  mvwprintw(editorPad(), row, pos, "%s", buffer);
                  pos += 2;
                }
              case 3:
                {
                  // print the volume
                  pp_int32 effect, operand;
                  tools.getFirstEffect(effect, operand);
                  if(operand <= 0x0F)
                  {
                    sprintf(buffer, ".%X", operand);
                  }
                  else
                  {
                    snprintf(buffer, 3, "%X", operand);
                  }
                  //      PatternTools::getVolumeName(buffer, operand);
                  wcolor_set(editorPad(), VOLUME_COLOR, NULL);
                  mvwprintw(editorPad(), row, pos, "%s", buffer);
                  pos += 2;
                }
              case 4:
                {
                // print the effect
                  pp_int32 effect, operand;
                  tools.getNextEffect(effect, operand);
                  PatternTools::getEffectName(buffer, effect);
                  wcolor_set(editorPad(), EFFECT_NAME_COLOR, NULL);
                  mvwprintw(editorPad(), row, pos, "%s", buffer);
                  pos += 1;
                }
              case 5:
              case 6:
                // print the effect operand
                // TODO

                // print the margins
                wcolor_set(editorPad(), CHANNEL_MARGIN_COLOR, NULL);
                pos += 2;
                mvwprintw(editorPad(), row, pos, "|");
                pos += CHANNEL_MARGIN - 1;
                mvwprintw(editorPad(), row, pos, "|");
                pos += 1;
            };
          }
          else
          {
            switch(se.inner)  // FIXME: milkytracker has only 6 columns for the inner selection value, but 7 is the highest value allowed for inner... figure out if this value is indexed from 0 or from 1
            {
              case 5:
              case 6:
                // print the effect number
              case 4:
                // print the effect name
              case 3:
                // print the volume
              case 2:
                // print the instrument number
              case 1:
                // print the note name
                break;
            };
          }

        /*
        // print the hex values of each column in the pattern
        //      mvwprintw(editorPad(), i, 0, "row %d: ", i);
        for(int j = 0; j < 5; j++)
        {
        snprintf(buffer, 9, "%08X", *dataPos);
        //        wprintw(editorPad(), "0x%02X", *dataPos);
        mvwprintw(editorPad(), i, j * 12, "0x%s", buffer);
        if(j != 5)
        {
        mvwprintw(editorPad(), i, j * 12 + 10, ", ");
        }
        dataPos += 1;
        }
         */

        inner = 1;
      }
    }
    delete [] buffer;
  }
}
