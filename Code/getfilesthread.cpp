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
+   file : this thread is used to mentain the performance of Arab Renamer
-------------------------------------------------------------------------------*/
#include <vcl.h>
#include "getfilesthread.h"
#include "mainfrm.h"
#include "srchdlgfrm.h"

#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall getfiles::getfiles(bool CreateSuspended, bool getundo)
: TThread(CreateSuspended)
{
#ifndef _DEBUG
  Priority = tpTimeCritical;
#endif
  FreeOnTerminate = true;
  und = getundo;
}
//---------------------------------------------------------------------------

void __fastcall getfiles::Execute()
{
  try
  {
    try
    {
      if(und)
        undo();
      else
      {
        GetFilesNum(Form1->Edit1->Text);
        if(Terminated) return;
        if(srchdlg->Visible==true)
          srchdlg->Hide();
        if(msg.data())
          Synchronize(shwmsg);
        else
          if(int count = Form1->Files.size() + Form1->Folders.size())
          {
            Form1->Panel1->SendToBack();
            int i=0,x=0,Err=0;
            for(;i<signed(Form1->Files.size());i++,x++)
            {
              if(Form1->Files[i]=="newsub")
              {
                Form1->newFiles.push_back("newsub");
                continue;
              }
              if(Terminated) return;
              Err += file_rename(Form1->Files[i],'f');
              Form1->ProgressBar1->Position=((double)x/count)*100;
            }
            for(i=Form1->Folders.size()-1;i>=0;i--,x++)
            {
              if(Terminated) return;
              Err += file_rename(Form1->Folders[i],'d');
              Form1->ProgressBar1->Position=((double)x/count)*100;
            }
            Form1->ProgressBar1->Position=100;
            msg = (count-Err?(IntToStr(count-Err)+" Files renamed"):AnsiString(""))
              +(count-Err && Err?" and ":"")
              +(Err?IntToStr(Err)+" Errors Found.":AnsiString(""));
            Synchronize(shwmsg);
          }else{
            msg = "No arabic files found";
            Synchronize(shwmsg);
          }
      }
    }
    catch (Exception &E)
    {
      if (!E.ClassNameIs("EAbort"))
      {
        msg = "Error! : "+E.ClassName()+" -> "+E.Message;
        Synchronize(shwmsg);
      }
    }
  }
  __finally
  {
    Form1->Panel2->Enabled = true;
    if(srchdlg->Visible==true)
      srchdlg->Hide();
  }
}
//---------------------------------------------------------------------------
void __fastcall getfiles::shwmsg()
{
  ShowMessage(msg);
}
//---------------------------------------------------------------------------

void __fastcall getfiles::GetFilesNum(AnsiString path)
{
  if(strcmp(AnsiLastChar(path),"\\"))
    path +="\\";
  _finddata_t fd;
  long handle = _findfirst((path+"*").c_str(),&fd);
  try
  {
    if(handle>-1)
      do{
        if(Terminated) return;
        if(srchdlg->Visible==false)
        {
          Form1->Files.clear();
          Form1->Folders.clear();
          msg = "Search Aborted!";
          break;
        }
        if(strcmp(fd.name, ".") && strcmp(fd.name, "..") && strcmp(fd.name, "Recycled") && !(fd.attrib & _A_SYSTEM))
        {

          if(fd.attrib & _A_SUBDIR)
          {
            //Rename arabic folders
            if(Form1->CheckBox3->Checked && Form1->isArab(fd.name))
              Form1->Folders.push_back(path+fd.name);
            //include subfolders
            if(Form1->CheckBox1->Checked)
            {
              Form1->Files.push_back("newsub");
              GetFilesNum(path+fd.name);
            }
          }else if(Form1->isArab(fd.name))
            Form1->Files.push_back(path+fd.name);
        }
      }while(!_findnext(handle, &fd));
  }
  __finally
  {
    _findclose(handle);
  }
}
//---------------------------------------------------------------------------

int __fastcall getfiles::file_rename(AnsiString ara_name, char c)
{
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char file[_MAX_FNAME];
  char ext[_MAX_EXT];
  AnsiString nname;
  int Err=1;

  try
  {
    if(c=='f')
    {
      _splitpath(ara_name.c_str(),drive,dir,file,ext);
      if(!Form1->ListBox1->Count)
      {
        Form1->ListBox1->Items->Add("Renaming Files...");
      }
      if(Form1->newFiles.size())
        if(Form1->newFiles[Form1->newFiles.size()-1] == "newsub")
        {
          Form1->ListBox1->Items->Add("");
          Form1->ListBox1->Items->Add(AnsiString(drive)+AnsiString(dir));
        }
        strcpy(file,Form1->convrtit(file,Form1->CheckBox4->Checked).c_str());
        //limit new names letters
        if(Form1->CheckBox2->Checked && signed(strlen(file))>StrToInt(Form1->Edit2->Text))
          file[StrToInt(Form1->Edit2->Text)]='\0';
        nname.cat_printf("%s%s%s%s",drive,dir,file,ext);
    }else
    {
      if(!Form1->newFolders.size())
      {
        Form1->ListBox1->Items->Add("");
        Form1->ListBox1->Items->Add("Renaming Folders...");
      }
      strcpy(dir,ara_name.c_str());
      strcpy(file,strtok(strrchr(dir, '\\'),"\\"));
      dir[strlen(dir)-strlen(file)]='\0';
      strcpy(file,Form1->convrtit(file,Form1->CheckBox4->Checked).c_str());
      //limit new names letters
      if(Form1->CheckBox2->Checked && signed(strlen(file))>StrToInt(Form1->Edit2->Text))
        file[StrToInt(Form1->Edit2->Text)]='\0';
      nname.cat_printf("%s%s",dir,file);
    }

    if(rename(ara_name.c_str(), nname.c_str()))
    {
      if (errno==EEXIST)
        Form1->ListBox1->Items->Add("Permission denied: "+nname+" already exists.");
      if (errno==ENOENT)
        Form1->ListBox1->Items->Add(ara_name+" doesn't exist");
      if (errno==EACCES)
        Form1->ListBox1->Items->Add("Access Denied: "+nname+" in use");
    }else
    {
      if(c=='f') Form1->ListBox1->Items->Add(ExtractFileName(ara_name)+" -> "+file+ext);
      else       Form1->ListBox1->Items->Add(ExtractFileName(ara_name)+" -> "+file);
      Err=0;
    }
    if(Err)
      if(c=='f')  Form1->newFiles.push_back(""); else Form1->newFolders.insert(Form1->newFolders.begin(),"");
    else
      if(c=='f')  Form1->newFiles.push_back(nname); else Form1->newFolders.insert(Form1->newFolders.begin(),nname);
    if(Form1->ListBox1->Count>0) Form1->ListBox1->Selected[Form1->ListBox1->Count-1] = true;
  }
  catch (Exception &E)
  {
    if (!E.ClassNameIs("EAbort"))
    {
      msg = "  Error!: "+E.ClassName()+" -> "+E.Message;
      Synchronize(shwmsg);
    }
  }
  return Err;
}

//---------------------------------------------------------------------------

void __fastcall getfiles::undo()
{
  int i=0, n=0, x=0, err=0,fchk=0 , count = Form1->Folders.size()+Form1->Files.size();
  if(count)
  {
    for(;i<signed(Form1->Folders.size());i++,x++)
    {
      if(Terminated) return;
      Form1->ProgressBar1->Position=100-(((double)x/count)*100);
      if(Form1->newFolders[i].data())
      {
        if(!err++)
        {
          Form1->ListBox1->Clear();
          Form1->ListBox1->Items->Add("Renaming Folders...");
        }
        if(rename(Form1->newFolders[i].c_str(), Form1->Folders[i].c_str())){
          if (errno==EEXIST)
            Form1->ListBox1->Items->Add("Permission denied: "+Form1->Folders[i]+" already exists.");
          if (errno==ENOENT)
            Form1->ListBox1->Items->Add(Form1->newFolders[i]+" doesn't exist");
          if (errno==EACCES)
            Form1->ListBox1->Items->Add("Access Denied: "+Form1->Folders[i]+" in use");
        }else
        {
          Form1->ListBox1->Items->Add(ExtractFileName(Form1->newFolders[i])+" -> "+ExtractFileName(Form1->Folders[i]) );
          n++;
        }
        Form1->ListBox1->Selected[Form1->ListBox1->Count-1] = true;
      }
    }
    for(i=0;i<signed(Form1->Files.size());i++,x++)
    {
      if(Terminated) return;
      if(Form1->Files[i]=="newsub") continue;
      Form1->ProgressBar1->Position=100-(((double)x/count)*100);
      if(Form1->newFiles[i].data())
      {
        if(!err++) Form1->ListBox1->Clear();
        if(!fchk)
        {
          Form1->ListBox1->Items->Add("");
          Form1->ListBox1->Items->Add("Renaming Files...");
          fchk++;
        }
        if(Form1->Files[i-1]=="newsub")
        {
          Form1->ListBox1->Items->Add("");
          Form1->ListBox1->Items->Add(ExtractFileDir(Form1->Files[i]));
        }
        if(rename(Form1->newFiles[i].c_str(), Form1->Files[i].c_str())){
          if (errno==EEXIST)
            Form1->ListBox1->Items->Add("Permission denied: "+Form1->Files[i]+" already exists.");
          if (errno==ENOENT)
            Form1->ListBox1->Items->Add(Form1->newFiles[i]+" doesn't exist");
          if (errno==EACCES)
            Form1->ListBox1->Items->Add("Access Denied: "+Form1->Files[i]+" in use");
        }else
        {
          Form1->ListBox1->Items->Add(ExtractFileName(Form1->newFiles[i])+" -> "+ExtractFileName(Form1->Files[i]));
          n++;
        }
        Form1->ListBox1->Selected[Form1->ListBox1->Count-1] = true;
      }
    }
  }
  if(n)
  {
    Form1->ProgressBar1->Position=0;
    Form1->Files.clear();
    Form1->Folders.clear();
    Form1->newFiles.clear();
    Form1->newFolders.clear();
    msg = (n?(IntToStr(n)+" Files renamed"):AnsiString("")) +
      (n && err-n?" and ":"") +
      (err-n?IntToStr(err-n)+" Errors Found.":AnsiString(""));
    Synchronize(shwmsg);
  }else
  {
    if(Form1->ProgressBar1->Position!=100) Form1->ProgressBar1->Position=0;
    msg = "Rename some files first";
    Synchronize(shwmsg);
  }
}

