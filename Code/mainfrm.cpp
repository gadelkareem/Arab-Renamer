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
+   file : the main form
-------------------------------------------------------------------------------*/
#include <vcl.h>
#include <stdlib.h>
#include "Aboutfrm.h"
#include "srchdlgfrm.h"
#include "getfilesthread.h"

#pragma hdrstop
#include "mainfrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


class StrUtil
{
public:
  static string __replace(string s, const string search, const string rep, bool replaceAll=true, bool ignoreCase=true)
  {
    string uppersource = s, uppersearch = search, upperrep = rep;

    if(ignoreCase)
      uppersource = strupr((char*)uppersource.c_str()), uppersearch = strupr((char*)uppersearch.c_str()), upperrep = strupr((char*)upperrep.c_str());

    string::size_type pos = uppersource.find(uppersearch);
    while(pos != string::npos){
      uppersource.replace(pos, uppersearch.length(), upperrep);
      s.replace(pos, search.length(), rep);
      if(!replaceAll)
        return s;
      pos = uppersource.find(uppersearch, pos);
    }
    return s;
  }
  static AnsiString __replace(AnsiString s, const AnsiString search, const AnsiString rep, bool replaceAll=true, bool ignoreCase=true)
  {
    return AnsiString(__replace(string(s.c_str()) ,search.c_str(), rep.c_str(), replaceAll, ignoreCase).c_str());
  }
};
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Application->HintPause = 0;
  Application->HintShortPause = 0;
  Application->HintHidePause = 10000000000;
  Application->OnShowHint = DoShowHint;
  Panel3->Visible = false;
  Width = 367;
  Edit1->Text = GetCurrentDir();
#ifdef _DEBUG
  Memo1->Lines->LoadFromFile("file");
#endif
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  AnsiString Directory = Edit1->Text;
  if(SelectDirectory("Select the folders with arabic files", "", Directory))
    Edit1->Text = Directory;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
  if(CheckBox2->Checked)
  {
    Edit2->Enabled = true;
    UpDown1->Enabled = true;
    Edit2->SetFocus();
  }else
    Edit2->Enabled = false;
  UpDown1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_RETURN)
    Button2Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  if(Edit1->Text.data())
  {
    Panel2->Enabled = false;
    ListBox1->Clear();
    ProgressBar1->Position=0;
    if(Files.size()+Folders.size()+newFiles.size()+newFolders.size()!=0)
    {
      Folders.clear();
      newFolders.clear();
      Files.clear();
      newFiles.clear();
    }
    strt = new getfiles(true,false);
    srchdlg->Show();
    srchdlg->Position = Position;
    strt->Resume();
  }else
  {
    ShowMessage("Choose the folder which contains the Arabic files");
    Edit1->SetFocus();
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  Panel2->Enabled = false;
  strt = new getfiles(false,true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label3Click(TObject *Sender)
{
  ShellExecute(0,"open","http://fly.to/kurtubba",0,0,SW_SHOWMAXIMIZED );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
  ShellExecute(0,"open","http://fly.to/kurtubba",0,0,SW_SHOWMAXIMIZED );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
  Edit1->MaxLength = _MAX_PATH;
  if(Canvas->TextWidth(Edit1->Text)>Edit1->ClientWidth)
    Edit1->Hint = Edit1->Text;
  else
    Edit1->Hint = "Includes the path for your folder which contains the arabic files";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(Panel2->Enabled == false)
  {
    if(MessageDlg( "Arab Renamer is renaming files\n Are you sure you want to cancel and close?", mtConfirmation, mbYesNoCancel, 0)== mrYes)
    {
      if(Panel2->Enabled == false) strt->Terminate();
    }
    else
      Action = caNone;
  }
#ifndef _DEBUG
  else
  {

    randomize();
    int r=random(4);
    if(r==1)
      ShellExecute(0,"open","http://fly.to/kurtubba",0,0,SW_SHOWMAXIMIZED );
  }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DoShowHint(System::AnsiString &HintStr, bool
                                   &CanShow, THintInfo &HintInfo)
{
  CanShow = true;
  if (HintInfo.HintControl == ListBox1 )
  {
    if( Mouse->Capture )
    {
      CanShow = false;
      return;
    }
    HintInfo.ReshowTimeout = 100;
    /*HintInfo.HintColor = clAqua;// Changes only for this hint*/

    TPoint pnt;
    SIZE strsize;
    int numstr = ListBox1->ItemAtPos(HintInfo.CursorPos,true);
    if(numstr<0)
    {
      CanShow = false;
      Application->HideHint ();
      return;
    }
    HintStr = ListBox1->Items->Strings[numstr];
    strsize = ListBox1->Canvas->TextExtent(HintStr);
    if(strsize.cx<=ListBox1->ClientWidth)
    {
      CanShow = false;
      Application->HideHint ();
      return;
    }
    pnt.x = -1;
    pnt.y = int(HintInfo.CursorPos.y/ListBox1->ItemHeight)*ListBox1->ItemHeight - 3;
    pnt = ListBox1->ClientToScreen(pnt);
    HintInfo.HintPos.x = pnt.x;
    HintInfo.HintPos.y = pnt.y;
    HintInfo.HintMaxWidth = Screen->Width-pnt.x;
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  Form2->Position = poMainFormCenter;
  Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
  if(Edit2->Text.data())
  {
    for(int i=1;i<=Edit2->Text.Length();i++)
    {
      if(!isdigit(Edit2->Text[i]))
      {
        if(i==1) Edit2->Text = Edit2->Text.SubString(2,3);
        else Edit2->Text=Edit2->Text.SetLength(i-1);
        break;
      }
    }
    if(Edit2->Text.ToInt()>200)
      Edit2->Text="200";
    if(Edit2->Text.ToInt()<5)
      Edit2->Text="5";
  }else
    Edit2->Text=5;
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::isArab(const string name)
{
  boost::regex e("[Á-ú]");
  if(boost::regex_search(name ,e ,boost::match_default ))
    return true;
  return false;
}
AnsiString __fastcall TForm1::convrtit(AnsiString ara_name ,bool tskl)
{
  char cnvr[3]="";
  AnsiString eng_name = "";
  boost::regex e;

  //remove Tashkeel if not useing it
  if(!tskl)
  {
    e.assign("[ð-ú]");
    ara_name = boost::regex_replace(string(ara_name.c_str()) ,e ,"" , boost::match_default | boost::format_all).c_str();
  }

  //Removing extra Arabic characters
  for(int n=1; n<=ara_name.Length(); n++)
  {
    switch(ara_name[n])
    {
    case 'Ü':
    case 'ú':
    case 'ø':
      cnvr[0] = '\0';
      break;
    case 'ì':
      cnvr[0] = 'í';
      break;
    default:
      cnvr[0] = ara_name[n];
      break;
    }
    eng_name += cnvr;
  }

  ara_name = Specialwords(eng_name);
  eng_name = "";

  int n=1;
  //converting letter by letter
  for(; n<=ara_name.Length(); n++){
    int v=1;
    switch (ara_name[n])
    {
    case 'Ç':
    case 'Ã':
      cnvr[0]='a';
      break;
    case 'Â':
      strcpy(cnvr, "aa");
      v=2;
      break;
    case 'Å':
      cnvr[0]='i';
      break;
    case 'È':
      cnvr[0]='b';
      break;
    case 'Ê':
    case 'Ø':
      cnvr[0]='t';
      break;
    case 'Ë':
      strcpy(cnvr, "th");
      v=2;
      break;
    case 'Ì':
      cnvr[0]='g';
      break;
    case 'Í':
      cnvr[0]='7';
      break;
    case 'Î':
      strcpy(cnvr, "kh");
      v=2;
      break;
    case 'Ï':
    case 'Ö':
      cnvr[0]='d';
      break;
    case 'Ð':
    case 'Ò':
    case 'Ù':
      cnvr[0]='z';
      break;
    case 'Ñ':
      cnvr[0]='r';
      break;
    case 'Ó':
    case 'Õ':
      cnvr[0]='s';
      break;
    case 'Ô':
      strcpy(cnvr, "sh");
      v=2;
      break;
    case 'Ú':
      cnvr[0]='3';
      break;
    case 'Û':
      strcpy(cnvr, "gh");
      v=2;
      break;
    case 'Ý':
      cnvr[0]='f';
      break;
    case 'Þ':
      cnvr[0]='q';
      break;
    case 'ß':
      cnvr[0]='k';
      break;
    case 'á':
      cnvr[0]='l';
      break;
    case 'ã':
      cnvr[0]='m';
      break;
    case 'ä':
      cnvr[0]='n';
      break;
    case 'å':
      cnvr[0]='h';
      break;
    case 'É':
      cnvr[0]='t';
      break;
    case 'Ä':
      strcpy(cnvr, "u'");
      v=2;
      break;
    case 'æ':
      cnvr[0]='w';
      break;
    case 'í':
      cnvr[0]='y';
      break;
    case 'Á':
      cnvr[0]='\'';
      break;
    case 'Æ':
      strcpy(cnvr, "'e");
      v=2;
      break;
      //Tashkeel
    case 'õ':
      cnvr[0]='u';
      break;
    case 'ó':
      cnvr[0]='a';
      break;
    case 'ö':
      cnvr[0]='e';
      break;
    case 'ñ':
      strcpy(cnvr, "un");
      v=2;
      break;
    case 'ð':
      strcpy(cnvr, "an");
      v=2;
      break;
    case 'ò':
      strcpy(cnvr, "en");
      v=2;
      break;
    default:
      cnvr[0]=ara_name[n];
      break;
    }

    if (v==1)
      cnvr[1]='\0';
    else
      cnvr[2]='\0';
    eng_name += cnvr;
  }
  //creating Capital letters
  for(n=2; n<=eng_name.Length(); n++)
    if(eng_name[n-1] == '-' && islower(eng_name[n]))
      eng_name[n] = toupper(eng_name[n]);

  return eng_name;
}

AnsiString __fastcall TForm1::Specialwords(AnsiString ara_name)
{
  string e;
  boost::regex exp;

  AnsiString ptrn_DB[][2] = {
    "ÇáäÇÓ", "An-Nas",         //known words
      "ÇáÝáÞ", "Al-Falaq",
      "ÇáãÓÏ", "Al-Masadd",
      "ÇáäÕÑ", "An-Nasr",
      "ÇáßÇÝÑæä", "Al-Kafiroon",
      "ÇáßæËÑ", "Al-Kauther",
      "ÇáãÇÚæä", "Al-Ma3un",
      "ÞÑíÔ", "Quraish",
      "ÇáÝíá", "Al-Fil",
      "ÇáÚÕÑ", "Al-3asr",
      "ÇáÊßÇËÑ", "At-Takathur",
      "ÇáÚÇÏíÇÊ", "Al-3adiyat",
      "ÇáÞÏÑ", "Al-Qadr",
      "ÇáÚáÞ", "Al-3alaq",
      "ÇáÊíä", "At-Tin",
      "ÇáÔÑÍ", "As-Sharh",
      "ÇáÖÍí", "Ad-Dhu7a",
      "Çááíá", "Al-Layl",
      "ÇáÔãÓ", "Ash-Shams",
      "ÇáÈáÏ", "Al-Balad",
      "ÇáÝÌÑ", "Al-Fajr",
      "ÇáØÇÑÞ", "At-6ariq",
      "ÇáÈÑæÌ", "Al-Burooj",
      "ÇáãØÝÝíä", "Al-Mutaffifin",
      "ÇáÊßæíÑ", "At-Takwir",
      "ÚÈÓ", "3basa",
      "ÇáäÇÒÚÇÊ", "An-Nazi3at",
      "ÇáãÑÓáÇÊ", "Al-Mursalat",
      "ÇáãÏËÑ", "Al-Muddather",
      "ÇáãÒãá", "Al-Muzzammil",
      "ÇáÌä", "Al-Jinn",
      "äæÍ", "Noo7",
      "ÇáãÚÇÑÌ", "Al-Ma3arij",
      "ÇáÞáã", "Al-Qalam",
      "Çáãáß", "Al-Mulk",
      "ÇáÊÍÑíã", "At-Ta7rim",
      "ÇáØáÇÞ", "At-Talaq",
      "ÇáÊÛÇÈä", "At-Taghabun",
      "ÇáãäÇÝÞæä", "Al-Munafiqoon",
      "ÇáÕÝ", "As-Saff",
      "ÇáÍÔÑ", "Al-7ashr",
      "ÇáÍÏíÏ", "Al-7adid",
      "ÇáÑÍãä", "Ar-Ra7man",
      "ÇáÞãÑ", "Al-Qamar",
      "ÇáäÌã", "An-Najm",
      "ÇáØæÑ", "At-6ur",
      "ÇáÐÇÑíÇÊ", "Az-Zariyat",
      "ÇáÍÌÑÇÊ", "Al-7ujraat",
      "ÇáÝÊÍ", "Al-Fat7",
      "ãÍãÏ", "Muhammad",
      "ÇáÏÎÇä", "Ad-Dukhan",
      "ÇáÒÎÑÝ", "Az-Zukhruf",
      "ÇáÔæÑí", "Ash-Shura",
      "ÝÕáÊ", "Fussilat",
      "ÛÇÝÑ", "Ghafir",
      "ÇáÒãÑ", "Az-Zumar",
      "ÇáÕÇÝÇÊ", "As-Saaffat",
      "ÝÇØÑ", "Fa6er",
      "áÞãÇä", "Luqman",
      "ÇáÑæã", "Ar-Room",
      "ÇáÚäßÈæÊ", "Al-3ankaboot",
      "ÇáÞÕÕ", "Al-Qasas",
      "Çáäãá", "An-Naml",
      "ÇáÔÚÑÇÁ", "Ash-Shu3ara'",
      "ÇáÝÑÞÇä", "Al-Furqan",
      "ÇáäæÑ", "An-Noor",
      "ÇáãÄãäæä", "Al-Mu'menoon",
      "ÇáÍÌ", "Al-7ajj",
      "ãÑíã", "Maryam",
      "ÇáßåÝ", "Al-Kahf",
      "ÇáäÍá", "An-Na7l",
      "ÇáÍÌÑ", "Al-7ijr",
      "ÇáÑÚÏ", "Ar-Ra3d",
      "íæÓÝ", "Yusuf",
      "åæÏ", "Hud",
      "íæäÓ", "Yunus",
      "ÇáäÓÇÁ", "An-Nisa",
      "Çááå", "Allah",
      "Çááóå","Allah",
      "ááå", "Lelah",
      "ÇÑÈ ÑíäíãÑ", "Arab Renamer",
      "æõ","æ",
      "ãÓáã", "Muslim",
      "åÏì", "Huda",
      NULL,NULL,
      "ÈÓÈ[ÃÅÇÂ]", "Saba'",        //diffrent characters for alef and hamza
      "ÇáäÈ[ÇÃÂÅ]", "An-Nab'",
      "Çá[ÃÅÇÂ]ÎáÇÕ", "Al-Ikhlas",
      "ÇáåãÒ[åÉ]", "Al-Humaza",
      "ÇáÞ[ÃÅÇÂ]ÑÚ[åÉ]", "Al-Qari3a",
      "ÇáÒáÒá[åÉ]", "Az-Zalzala",
      "ÇáÈíä[åÉ]", "Al-Bayyina",
      "ÇáÛ[ÃÅÇÂ]Ôí[åÉ]", "Al-Ghashiya",
      "Çá[ÃÅÇÂ]Úáí", "Al-A3la",
      "Çá[ÃÅÇÂ]äÝØÇÑ", "Al-Infi6ar",
      "Çá[ÃÅÇÂ]äÔÞÇÞ", "Al-Inshiqaq",
      "Çá[ÃÅÇÂ]äÓÇä", "Al-Insan",
      "ÇáÞíÇã[åÉ]", "Al-Qiyama",
      "ÇáÍ[ÃÅÇÂ]Þ[åÉ]", "Al-7aaqqa",
      "ÇáÌãÚ[åÉ]", "Al-Jumu3a",
      "ÇáããÊÍä[åÉ]", "Al-Mumta7ana",
      "ÇáãÌÇÏá[åÉ]", "Al-Mujadala",
      "ÇáæÇÞÚ[åÉ]", "Al-Waqi3a",
      "Çá[ÃÅÇÂ]ÍÞÇÝ", "Al-A7qaf",
      "ÇáÌÇËí[åÉ]", "Al-Jathiya",
      "Çá[ÃÅÇÂ]ÍÒÇÈ", "Al-A7zab",
      "ÇáÓÌÏ[åÉ]", "As-Sajda",
      "Çá[ÃÅÇÂ]äÈíÇÁ", "Al-Anbiya'",
      "Çá[ÃÅÇÂ]ÓÑ[ÃÅÇÂ]Á", "Al-Isra'",
      "[ÃÅÇÂ]ÈÑÇåíã", "Ibrahim",
      "ÇáÊæÈ[åÉ]", "At-Tawba",
      "Çá[ÃÅÇÂ]äÝÇá", "Al-Anfal",
      "Çá[ÃÅÇÂ]ÚÑÇÝ", "Al-A3raf",
      "Çá[ÃÅÇÂ]äÚÇã", "Al-An3aam",
      "ÇáãÇÆÏ[åÉ]", "Al-Ma'eda",
      "[ÃÅÇÂ]á ÚãÑÇä", "Aal-e-3imran",
      "ÇáÈÞÑ[åÉ]", "Al-Baqara",
      "ÇáÝÇÊÍ[åÉ]", "Al-Fatiha",
      "ÇáÞÑ[ÃÅÇÂ]ä", "Al-Quran",
      "ÞÑ[ÃÅÇÂ]ä", "Quran",
      NULL,NULL,
      "Þ","\\1Qaf\\2",      //small Quran names
      "Õ","\\1Sad\\2",
      "íÓ","\\1Ya-seen\\2",
      "Ø[åÉ]","\\1Taha\\2",
      "ÈÓã", "\\1Besm\\2",
      "æ", "\\1wa\\2",
      NULL,NULL,
      "ó([ÃÂÁÇ])","\\1",   //fat7a  //deplicated letters with Tashkeel
      "([ÃÂÁÇ])ó","\\1",
      "ö([Åí])","\\1",      //kasra
      "([Åí])ö","\\1",
      "õ([æÄ])","\\1",      //dama
      "([æÄ])õ","\\1",
      "(^|[^Á-ú])Çá([ØËÕÑÊÖÐäÏÓÙÒÔá])([Á-ú])","\\1A\\2-\\2\\3",       //AL- Ash-shamsya
      "(^|[^Á-ú])Çá([Á-ð])([Á-ú])","\\1Al-\\2\\3",       //AL- Al-Kamarya
      "([Á-ú])Ã","\\1a'",          //alef hamza if not in the begining or alone
      "([ÇÃóa])í", "\\1y",      //ya' if got (alef or a) before it
      "í([ÇÃóa])", "y\\1",      //ya' if got (alef or a) after it
      "([Á-ú])í", "\\1ee",      //ya' if not in the begining or alone
      "æ($|[^Á-ð])", "w\\1",      //waw when last letter
      "([ÇÃóa])æ", "\\1w",      //waw if got (alef or a) before it
      "([Á-ú])æÇ([^Á-ú])", "\\1u\\2",     //waw al-gama3a
      "æ([ÇÃóa])", "w\\1",      //waw if got (alef or a) after it
      "([Á-ú])æ", "\\1u",      //ya' if not in the begining or alone
      NULL,NULL
  };

  //regular replace
  int i=0;
  for( ; ptrn_DB[i][0] != NULL ; i++)
    if(strstr(ara_name.c_str(), ptrn_DB[i][0].c_str()))
      ara_name = StrUtil::__replace( ara_name, ptrn_DB[i][0], ptrn_DB[i][1]);

  //expression replace
  for(i++ ; ptrn_DB[i][0] != NULL ; i++)
  {
    exp.assign(ptrn_DB[i][0].c_str());
    ara_name = boost::regex_replace(string(ara_name.c_str()) ,exp ,string(ptrn_DB[i][1].c_str()) , boost::match_default | boost::format_all).c_str();
  }

  //shared expressions with grouping
  for(i++ ; ptrn_DB[i][0] != NULL ; i++)
  {
    e = "(^|[^Á-ú])"+ string(ptrn_DB[i][0].c_str())+ "($|[^Á-ú])";
    exp.assign(e);
    ara_name = boost::regex_replace(string(ara_name.c_str()) ,exp ,string(ptrn_DB[i][1].c_str()) , boost::match_default | boost::format_sed).c_str();
  }

  //other expressions with grouping
  for(i++ ; ptrn_DB[i][0] != NULL ; i++)
  {
    exp.assign(ptrn_DB[i][0].c_str());
    ara_name = boost::regex_replace(string(ara_name.c_str()) ,exp ,string(ptrn_DB[i][1].c_str()) , boost::match_default | boost::format_sed).c_str();
  }



  return ara_name;
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
#ifdef _DEBUG
  TDateTime t = TDateTime::CurrentTime();;
#endif
  if(isArab(Memo1->Text.c_str()))
  {
    undo = Memo1->Text;
    Memo1->Alignment = taLeftJustify;
    Memo1->Text = convrtit(Memo1->Text ,CheckBox5->Checked);
#ifdef _DEBUG
    ShowMessage(MilliSecondSpan(t,TDateTime::CurrentTime()));
#endif
  }else
    ShowMessage("No Arabic Letters Found");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3KeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_RETURN)
    Button5Click(this);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
  if(Panel3->Visible == true)
  {
    Panel3->Visible = false;
    Width = 367;
  }else
  {
    Panel3->Visible = true;
    Width = 710;
    Memo1->SetFocus();
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
  Memo1->SetFocus();
  Memo1->SelectAll();
  Memo1->CopyToClipboard();
}
//--------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
  if(undo.data())
  {
    Memo1->SetFocus();
    Memo1->Text = undo;
    Memo1->Alignment =  taRightJustify;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)
{
  Memo1->SetFocus();
  Memo1->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
  Memo1->SetFocus();
  Memo1->PasteFromClipboard();
  Memo1->Alignment =  taRightJustify;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{
  Memo1->Clear();
  Memo1->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
                                    TShiftState Shift)
{
  if(Key == VK_F1)
  {
    Form2->Show();
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Memo1KeyDown(TObject *Sender, WORD &Key,
                                     TShiftState Shift)
{
  Memo1->Alignment =  taRightJustify;
}
//---------------------------------------------------------------------------

