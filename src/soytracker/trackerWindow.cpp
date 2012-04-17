#include "common.h"
#include "trackerWindow.h"
#include "windowManager.h"

#include <iostream>
using namespace std;

namespace SoyTracker
{
  TrackerWindow::TrackerWindow()
  {
    m_editorPad = NULL;
    m_lines = 0;
    m_columns = 0;
    m_lineOffset = 0;
    m_columnOffset = 0;
    m_windowManager = NULL;
    m_visible = false;
  }

  TrackerWindow::~TrackerWindow()
  {
    delwin(m_editorPad);
  }

  void TrackerWindow::resizeEditorPad(int lines, int columns)
  {
    m_lines = lines;
    m_columns = columns;
    if(m_editorPad == NULL)
    {
      m_editorPad = newpad(lines, columns);
      return;
    }
    // TODO: figure out how to resize this thing
  }

  void TrackerWindow::cursorMoveEvent()
  {
    return;
  }

  void TrackerWindow::keyPressEvent()
  {
    return;
  }
  
  void TrackerWindow::resizeEvent(int newLines, int newColumns)
  {
    if(windowManager() != NULL && isVisible())
    {
      if(newLines > lines())
      {
        drawWindow(lines(), 0, newLines - 1, columns() - 1);
      }
      if(newColumns > columns())
      {
        drawWindow(0, columns(), newLines - 1, newColumns - 1);
      }
    }
    m_lines = newLines;
    m_columns = newColumns;
  }

  void TrackerWindow::drawWindow(int minrow, int mincol, int maxrow, int maxcol)
  {
    pnoutrefresh(editorPad(), minrow, mincol, lineOffset(), columnOffset(), MAX(maxrow, LINES - 1), MAX(maxcol, COLS - 1));
  }
}
