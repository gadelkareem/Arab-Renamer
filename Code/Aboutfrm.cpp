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
+  file : the about form
-------------------------------------------------------------------------------*/
#include <vcl.h>
#pragma hdrstop

#include "Aboutfrm.h"
#include "mainfrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_ESCAPE)
    Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClick(TObject *Sender)
{
  Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label1Click(TObject *Sender)
{
  Hide();    
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label2Click(TObject *Sender)
{
  ShellExecute(0,"open","mailto:kurtubba@gawab.com",0,0,0 );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label3Click(TObject *Sender)
{
  ShellExecute(0,"open","http://gadelkareem.com/2006/10/13/arab-renamer-v2/",0,0,SW_SHOWMAXIMIZED );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1Click(TObject *Sender)
{
  ShellExecute(0,"open","http://gadelkareem.com/2006/10/13/arab-renamer-v2/",0,0,SW_SHOWMAXIMIZED );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label4Click(TObject *Sender)
{
  Hide();    
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormShow(TObject *Sender)
{
  Form1->Panel2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormHide(TObject *Sender)
{
  Form1->Panel2->Enabled = true;
}
//---------------------------------------------------------------------------


