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

#include "moduleEditor.h"

namespace SoyTracker
{
  /**
   * \class ModuleEditor
   * The ModuleEditor class provides a curses interface for editing modules, the song format used by Milkyplay.
   *
   * The most visible part of the ModuleEditor's interface is the pattern editor, which is made up of one or more PatternEditor interfaces. Module editor also provides access to the interfaces for changing samples, instruments, and options related to the current module.
   * 
   * SoyTracker uses a buffer system akin to Vim's buffer system, so multiple modules can be edited at the same time, and the same module can be edited by multiple ModuleEditors at the same time. The ModuleBuffer class is used as the backend for this system.
   */
  ModuleEditor::ModuleEditor()
  {
  }

  ModuleEditor::~ModuleEditor()
  {
  }
}
