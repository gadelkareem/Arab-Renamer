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
+   file :  the header file for the main form
-------------------------------------------------------------------------------*/
#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <StrUtils.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <io.h>
#include <stdio.h>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <vector>
#include <string>
#include <boost\regex.hpp>
#ifdef _DEBUG
#include <DateUtils.hpp>
#endif


#include "getfilesthread.h"
using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{

__published:	// IDE-managed Components
  TProgressBar *ProgressBar1;
  TListBox *ListBox1;
  TPanel *Panel1;
  TLabel *Label1;
  TImage *Image1;
  TLabel *Label2;
  TLabel *Label3;
  TPanel *Panel2;
  TEdit *Edit1;
  TCheckBox *CheckBox3;
  TCheckBox *CheckBox2;
  TCheckBox *CheckBox1;
  TButton *Button4;
  TButton *Button3;
  TButton *Button2;
  TButton *Button1;
  TEdit *Edit2;
  TUpDown *UpDown1;
  TButton *Button5;
  TPanel *Panel3;
  TButton *Button6;
  TMemo *Memo1;
  TButton *Button7;
  TButton *Button8;
  TButton *Button9;
  TButton *Button10;
  TButton *Button11;
  TCheckBox *CheckBox4;
  TCheckBox *CheckBox5;

  void __fastcall Button1Click(TObject *Sender);
  void __fastcall CheckBox2Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
  bool __fastcall isArab(string name);
  AnsiString __fastcall convrtit(AnsiString ara_name ,bool tskl);
  AnsiString __fastcall Specialwords(AnsiString ara_name);
  void __fastcall DoShowHint(System::AnsiString &HintStr, bool &CanShow, THintInfo &HintInfo);
  void __fastcall Button3Click(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall Label3Click(TObject *Sender);
  void __fastcall Image1Click(TObject *Sender);
  void __fastcall Edit1Change(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall Edit2Change(TObject *Sender);
  void __fastcall Button5Click(TObject *Sender);
  void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
  void __fastcall Button6Click(TObject *Sender);
  void __fastcall Button7Click(TObject *Sender);
  void __fastcall Button8Click(TObject *Sender);
  void __fastcall Button9Click(TObject *Sender);
  void __fastcall Button10Click(TObject *Sender);
  void __fastcall Button11Click(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);

private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
  vector <AnsiString> Files;
  vector <AnsiString> newFiles;
  vector <AnsiString> Folders;
  vector <AnsiString> newFolders;
  getfiles *strt;
  AnsiString undo;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

