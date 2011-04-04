#include "trackerWindow.h"

#include <iostream>
using namespace std;

namespace SoyTracker
{
  TrackerWindow::TrackerWindow()
  {
    m_editorPad = NULL;
    m_lines = 0;
    m_columns = 0;
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
}
