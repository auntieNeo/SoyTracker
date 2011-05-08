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

    private:
      std::vector<TrackerWindow *> m_windows;
  };
}

#endif
