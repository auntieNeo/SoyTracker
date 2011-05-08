#include "trackerWindow.h"
#include "windowManager.h"

#include <curses.h>

#include <iostream>
using namespace std;

namespace SoyTracker
{
  WindowManager::WindowManager()
  {
  }

  WindowManager::~WindowManager()
  {
  }

  void WindowManager::addWindow(TrackerWindow *window)
  {
    window->setWindowManager(this);
    window->setVisible(true);
    m_windows.push_back(window);
  }

  void WindowManager::chEvent(int ch)
  {
    if(ch == KEY_RESIZE)
    {
      cout << "ch equals KEY_RESIZE";
      for(size_t i = 0; i < m_windows.size(); i++)
      {
        m_windows[i]->resizeEvent(LINES, COLS);
      }
    }
  }
}
