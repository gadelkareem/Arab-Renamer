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
+   file : the search dialog
-------------------------------------------------------------------------------*/
#include <vcl.h>
#include "srchdlgfrm.h"
#include "mainfrm.h"
#include "getfilesthread.h"

#pragma hdrstop
//----------------------------------------------------------------------------
#pragma resource "*.dfm"
Tsrchdlg *srchdlg;
//----------------------------------------------------------------------------
__fastcall Tsrchdlg::Tsrchdlg(TComponent *Owner)
: TForm(Owner)
{
}
//----------------------------------------------------------------------------
void __fastcall Tsrchdlg::FormShow(TObject *Sender)
{
  Animate1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall Tsrchdlg::FormHide(TObject *Sender)
{
  Animate1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall Tsrchdlg::FormKeyPress(TObject *Sender, char &Key)
{

  if(Key == VK_ESCAPE && Visible==true)
  {
    //Form1->strt->Suspend();
    Animate1->Active = false;
    if(MessageDlg( "Are you sure you want\nto abort the search?", mtConfirmation, mbAbortIgnore, 0)== mrAbort)
    {
      Hide();
      //Form1->strt->Resume();
    }
    else
    {
      //Form1->strt->Resume();
      Animate1->Active = true;
    }
  }
}
//---------------------------------------------------------------------------




void __fastcall Tsrchdlg::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action=caNone;
}
//---------------------------------------------------------------------------


