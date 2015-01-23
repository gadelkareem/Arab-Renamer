/*---------------------------------------------------------------------------
+  Arab Renamer v 2.0
+  Descreption: Arab Renamer renames Arabic files to the same names but using
+  English characters like the word 'Quran', so that files could be used on
+  non-Arabic systems like Linux or on mp3 players, besides it can limit the
+  files names during renaming.
+  The program uses characters like 3, ', 6 and 7 which are popular characters
+  used to replace specific Arabic letters.
+  Copyright © 2004  Kurtubba Software Limited
+  Developed by Walid Aly
+  http://fly.to/kurtubba
+  +201 215 78967
+  We welcome bug report and/or enhancement request:
+  kurtubba@gawab.com
+
+  This program is free software; you can redistribute it and/or modify
+  it under the terms of the GNU General Public License as published by
+  the Free Software Foundation.
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
+   file : project source
-------------------------------------------------------------------------------*/
#include <vcl.h>
#include "Aboutfrm.h"

#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mainfrm.cpp", Form1);
USEFORM("Aboutfrm.cpp", Form2);
USEFORM("srchdlgfrm.cpp", srchdlg);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = "Arab Renamer";
    Application->CreateForm(__classid(TForm1), &Form1);
    Application->CreateForm(__classid(TForm2), &Form2);
    Application->CreateForm(__classid(Tsrchdlg), &srchdlg);
    Form2->Show();
    Form2->Update();
#ifndef _DEBUG
    Sleep(3000);
#endif
    Form2->Hide();
    Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  catch (...)
  {
    try
    {
      throw Exception("Plz Visit http://fly.to/kurtubba for updates");
    }
    catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------

