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

#include "MilkyPlay.h"

#include "common.h"
#include "patternEditor.h"

#include <curses.h>
#include <locale.h>
#include <unistd.h>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  if(argc != 2)
    return 1;

  setlocale(LC_ALL, "");

  // initilize screen and disable input line buffering and echoing
  initscr(); cbreak(); noecho();

  // some other settings recommended in the ncurses man page
  nonl();
  intrflush(stdscr, false);
  keypad(stdscr, true);

  clear();
  refresh();

  XModule *module = new XModule();
  module->loadModule(argv[1]);

  SoyTracker::PatternEditor *patternEditor = new SoyTracker::PatternEditor();
  patternEditor->setPattern(module->phead);

  prefresh(patternEditor->pad(), 0, 0, 0, 0, MIN(patternEditor->pattern()->rows, stdscr->_maxy), 100);
  refresh();
//  cout << "module->phead->patternData: " << module->phead->patternData << endl;

  sleep(-1);

  delete patternEditor;
  delete module;

  return 0;
}
