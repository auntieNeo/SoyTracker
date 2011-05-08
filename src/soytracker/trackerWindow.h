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
  class WindowManager;

  class TrackerWindow
  {
    friend class WindowManager;
    public:
      TrackerWindow();
      ~TrackerWindow();

      WINDOW *editorPad() { return m_editorPad; }
      WindowManager *windowManager() { return m_windowManager; }

      int lines() { return m_lines; }
      int columns() { return m_columns; }

      int lineOffset() { return m_lineOffset; }
      int columnOffset() { return m_columnOffset; }

      bool isVisible() { return m_visible; }
      void setVisible(bool visible) { m_visible = visible; }

    protected:
      void resizeEditorPad(int lines, int columns);

      std::string windowName();

      virtual void cursorMoveEvent();
      virtual void keyPressEvent();

      virtual void resizeEvent(int newLines, int newColumns);
      void drawWindow(int minrow, int mincol, int maxrow, int maxcol);

    private:
      WINDOW *m_editorPad;
      int m_lines, m_columns;
      int m_lineOffset, m_columnOffset;
      bool m_visible;
      WindowManager *m_windowManager;

      void setWindowManager(WindowManager *windowManager) { m_windowManager = windowManager; }
  };
}

#endif
