/***************************************************************************
 *   Copyright 2012 Jonathan Glines.                                       *
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

#include "MilkyPlay.h"

#include "common.h"

#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdio.h>
#include <panel.h>

#include <iostream>
using namespace std;

using namespace SoyTracker;

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");

  // initilize screen and disable input line buffering and echoing
  // TODO: replace cbreak with raw in the future and catch control characters properly
  initscr(); start_color(); use_default_colors(); cbreak(); noecho();

  /*
  nonl();
  intrflush(stdscr, false);
  // enables reading of function keys and arrow keys
  keypad(stdscr, true);
  // causes getch to be a non-blocking call
  nodelay(stdscr, true);
  */

  // initilize the color pairs
  init_pair(CHANNEL_MARGIN_COLOR, -1, -1);
  init_pair(NOTE_COLOR, -1, -1);
  init_pair(INSTRUMENT_COLOR, COLOR_CYAN, -1);
  init_pair(VOLUME_COLOR, COLOR_GREEN, -1);
  init_pair(EFFECT_NAME_COLOR, COLOR_MAGENTA, -1);
  init_pair(EFFECT_OPERAND_COLOR, COLOR_YELLOW, -1);

  // create a test panel
  int lines = 10, cols = 20, y = 3, x = 5;
  // create a window for the panel
  WINDOW *testWindow = newwin(lines, cols, y, x);
  // draw a box around the window
  box(testWindow, 0, 0);
  // attach a panel to the window
  PANEL *testPanel = new_panel(testWindow);

  // update panels, keeping them in the correct stacking order
  update_panels();

  // update the screen
  doupdate();

  getch();
  endwin();  // end curses mode

  return 0;
}
