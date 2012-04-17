#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <vector>

namespace SoyTracker
{
  class TrackerWindow;

  class WindowManager
  {
    public:
      WindowManager();
      ~WindowManager();

      void addWindow(TrackerWindow *window);

      void chEvent(int ch);

      void drawWindows();

    private:
      std::vector<TrackerWindow *> m_windows;
      TrackerWindow *m_currentWindow;
  };
}

#endif
