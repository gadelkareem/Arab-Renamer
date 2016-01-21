/*---------------------------------------------------------------------------
+  Arab Renamer v 2.0
+  Descreption: Arab Renamer renames Arabic files to the same names but using
+  English characters like the word 'Quran', so that files could be used on
+  non-Arabic systems like Linux or on mp3 players, besides it can limit the
+  files names during renaming.
+  The program uses characters like 3, ', 6 and 7 which are popular characters
+  used to replace specific Arabic letters.
+  Copyright © 2004  Kurtubba Software Limited
+  Developed by Waleed Gadelkareem
+  http://gadelkareem.com/2006/10/13/arab-renamer-v2/
+  +201 215 78967
+  We welcome bug report and/or enhancement request:
+  gadelkareem@gmail.com
+
+  This program is free software; you can redistribute it and/or modify
+  it under the terms of the GNU General Public License as published by
+  the Free Software Foundation; either version 2 of the License, or
+  (at your option) any later version.
+
+  This program is distributed in the hope that it will be useful,
+  but WITHOUT ANY WARRANTY; without even the implied warranty of
+  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+  GNU General Public License for more details.
+
+  You should have received a copy of the GNU General Public License
+  along with this program; if not, write to the Free Software
+  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+
+   file :  the header file for the thread
-------------------------------------------------------------------------------*/
#ifndef getfilesthreadH
#define getfilesthreadH
#include <Classes.hpp>
//---------------------------------------------------------------------------
class getfiles : public TThread
{
private:
protected:
  void __fastcall Execute(void);
public:
  __fastcall getfiles(bool CreateSuspended, bool getundo);
  AnsiString msg;
  bool und;
  void __fastcall shwmsg();
  void __fastcall undo();
  void __fastcall GetFilesNum(AnsiString path);
  int  __fastcall file_rename(AnsiString ara_name, char c);
};
//---------------------------------------------------------------------------
#endif


