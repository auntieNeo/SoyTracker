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

#ifndef TRACKER_WINDOW_H_
#define TRACKER_WINDOW_H_

#include <curses.h>
#include <string>

namespace SoyTracker
{
  class TrackerWindow
  {
    public:
      TrackerWindow();
      ~TrackerWindow();

      WINDOW *editorPad() { return m_editorPad; }

    protected:
      void resizeEditorPad(int lines, int columns);

      std::string windowName();

      virtual void cursorMoveEvent();
      virtual void keyPressEvent();

    private:
      WINDOW *m_editorPad;
      int m_lines, m_columns;
  };
}

#endif
