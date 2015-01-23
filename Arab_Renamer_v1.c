//**************************************
//     
// Name: Arab_Renamer_v1
// Description:Arab Renamer renames Arabic files to the same names but
//using English characters like the word 'Quran', so that files
//could be used on non-Arabic systems like Linux or on mp3players,
//also the program gives you the opportunity of limiting the
//files names during renaming.
//The program uses characters like 3, ', 6 and 7 which are popular
//characters used to replace specific Arabic letters.
//
//Copy the exe file inside the directory you want the files inside
//to be renamed and press 'a', you can get the old Arabic names
//back by pressing 'u' on your keyboard which undo all last changes.
//
//Another important possibility Arab Renamer presents is renaming files
//by reading the new names from a file called 'nnames.txt' in the same dir.
//This way you can edit names using regular expressions with a program like
//Jedit, editplus or Textpad.
//1st press 'd' to make 'onames.txt' which have the old names, or create it
//manually then press 'r' to start renaming. You can also undo this action
//as mentioned b4.
// By: Kurtubba@gawab.com
// Assumes:doesn't rename dirs & can work inside one dir only 
//
// Redistribution and use in source and binary forms, with or without
//modification, is permitted provided that you contact kurtubba@gawab.com   
//
//**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <errno.h>
#include <time.h>




void Intro(char*);
void ara_renamer(char*, int);
void renamer(char*);
char* convrtit(char ara_name[]);
char *Specialwords(char* ara_name);
char *_replace (char *source_str, char *search_str, char *replace_str);
void mkundo(char*,char*);
void undo();

int main(int argc, char* argv[])
{
	char pth[260]="";
	_splitpath(argv[0], NULL, NULL, pth, NULL);
	strcat(pth,".exe");
	Intro(pth);
}

void Intro(char* pth)
{
	char in;
	int prnt=0, mkfile=0, x;
	char ttl[]=" ###########################################################################\n"
		"## AAAAAA                       RRRRR                                       ##\n"
		"## A    A AAAAA  AAAAA AAAAA    R   R  RRRR RRRRR RRRRR RRRRRRR RRRR RRRRR  ##\n"
		"## AAAAAA A   A  A   A A   A    RRRRRR R    R   R R   R R  R  R R    R   R  ##\n"
		"## AA   A AAAAAA AAAAA AAAAAA   RR   R RRRR RR  R RRRRR RR R  R RRRR RRRRRR ##\n"
		"## AA   A AA   A AA  A AA   A   RR   R RR   RR  R RR  R RR R  R RR   RR   R ##\n"
		"## AA   A AA   A AA  A AAAAAA   RR   R RRRR RR  R RR  R RR R  R RRRR RR   R ##\n"
		"##              -----------By Kurtubba@gawab.com------------                ##\n";
	HANDLE hnd;

	hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Arab Renamer V 1 - By Kurtubba Software");
	SetConsoleTextAttribute(hnd, FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf(ttl);
	printf("##   To Rename files from nnames.txt press.... r                            ##\n");
	printf("##   To Make directory listing press.... d                                  ##\n");   
	printf("##   To Rename arabic files press.... a                                     ##\n");
	printf("##   To undo last changes press.... u                                       ##\n");
	printf("##   for help press ....h                                                   ##\n");
	printf("##   To exit press ...x                                                     ##\n");
	printf(" ###########################################################################\n");
	SetConsoleTextAttribute(hnd, COMMON_LVB_REVERSE_VIDEO | FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);

	do{
		if(prnt){
			SetConsoleTextAttribute(hnd, FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			printf(" ###########################################################################\n");
			printf("##   To Rename files from nnames.txt press.... r                            ##\n");
			printf("##   To Make directory listing press.... d                                  ##\n");   
			printf("##   To Rename arabic files press.... a                                     ##\n");
			printf("##   To undo last changes press.... u                                       ##\n");
			printf("##   for help press ....h                                                   ##\n");
			printf("##   To exit press ...x                                                     ##\n");
			printf(" ###########################################################################\n");
			SetConsoleTextAttribute(hnd, COMMON_LVB_REVERSE_VIDEO | FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
		}
		in=getch();
		in=toupper(in);
		fflush(stdin);
		switch (in)
		{
		case 'D':
			mkfile=1;
			ara_renamer(pth,mkfile);
			prnt=1;
			break;
		case 'R':
			printf("Renaming...\n\n");
			renamer(pth);
			prnt=1;
			break;
		case 'A':
			mkfile=0;
			printf("Renaming...\n\n");
			ara_renamer(pth,mkfile);
			prnt=1;
			break;
		case 'U':
			printf("Undoing last changes\n\n");
			undo();
			prnt=1;
			break;
		case 'H':
			printf("Diplaying help\n");
			system("cls");
			printf("\n");
			SetConsoleTextAttribute(hnd, FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			for(x=0;ttl[x]!='\0';x++){
				printf("%c",ttl[x]);
				_sleep((clock_t).1 * CLOCKS_PER_SEC);
			}
			printf(" ###########################################################################\n\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			SetConsoleTextAttribute(hnd, COMMON_LVB_REVERSE_VIDEO | FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
			printf("Arab Renamer renames Arabic files to the same names but\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("using English characters like the word 'Quran', so that files\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("could be used on non-Arabic systems like Linux or on mp3players,\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("also the program gives you the opportunity of limiting the\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("files names during renaming.\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("The program uses characters like 3, ', 6 and 7 which are popular\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("characters used to replace specific Arabic letters.\n\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("Copy the exe file inside the directory you want the files inside\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("to be renamed and press 'a', you can get the old Arabic names \n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("back by pressing 'u' on your keyboard which undo all last changes.\n\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("Another important possibility Arab Renamer presents is renaming files\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("by reading the new names from a file called 'nnames.txt' in the same dir.\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("This way you can edit names using regular expressions with a program like\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("Jedit, editplus or Textpad.\n");
			printf("1st press 'd' to make 'onames.txt' which have the old names, or create it\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("manually then press 'r' to start renaming. You can also undo this action \n");
			printf("as mentioned b4.\n");
			_sleep((clock_t)1 * CLOCKS_PER_SEC);
			printf("\n");
			printf("ENJOY!!\n");
			_sleep((clock_t).1 * CLOCKS_PER_SEC);
			printf("\n");
			printf("Email me for help or to request s.code <kurtubba@gawab.com>\n");
			_sleep((clock_t).1 * CLOCKS_PER_SEC);
			printf("\n");
			printf("\n");
			system("pause");
			prnt=1;
			break;
		case 'X':
			printf("Ending...\n\n");
			exit(0);
		default:
			prnt=0;
		}
	}while(in);
}

void undo()
{
	FILE* list;
	char buf[260]="",buf2[260]="", *nname,*oname;

	if(!(list=fopen("undo","r")))
	{
		printf("Can't find undo record file\n\n");
		return;
	}
	while(!feof(list))
	{
		oname=strtok(fgets(buf,260,list), "\n");
		nname=strtok(fgets(buf2,260,list), "\n");
		if(oname && nname)
		{
			if(rename(oname, nname)){
				if (errno==EEXIST)
					printf ("Permission denied: file %s already exists.\n", nname);
				if (errno==ENOENT)
					printf("%s doesn't exist\n", oname);
				if (errno==EACCES)
					printf("Access Denied: file %s in use\n", oname);
			}else
				printf("%s renamed to %s\n", oname, nname);
		}
	}
	//remove("undo");
	fclose(list);
	return;
}

void renamer(char* pth)
{
	FILE* fp, *fp2, *list;
	char buf[128]="",buf2[128]="";
	char *nname, *oname, in;

	fp2 = fopen("onames.txt", "r");
	if(!fp2){
		printf("onames.txt not found create one by pressing 'd'\n\n");
		return;
	}
	fp = fopen("nnames.txt", "r");
	if(!fp){
		fclose(fp2);
		printf("nnames.txt not found\n\n");
		return;

	}
	if((list=fopen("undo","r"))){
		fclose(list);
		printf("This will remove the last undo...Continue?\n");
		in=getch();
		in=toupper(in);
		if(in!='Y' && in!=' ' && in!='\r'){
			printf("NO\n\n");
			return;
		}else if(remove("undo")){
			if (errno==EACCES)
				printf("Access Denied: file undo in use\n\n");
			return;
		}else
			printf("YES\n\n");
	}


	while(!feof(fp2)){
		nname=strtok(fgets(buf, 127, fp), "\n");
		oname=strtok(fgets(buf2, 127, fp2), "\n");
		if (oname != NULL && nname != NULL && strcmp(nname,oname) ){
			if(rename(oname, nname)){
				if (errno==EEXIST)
					printf ("Permission denied: file %s already exists.\n", nname);
				if (errno==ENOENT)
					printf("%s doesn't exist\n", oname);
				if (errno==EACCES)
					printf("Access Denied: file %s in use\n", oname);

			}else{
				mkundo(oname,nname);
				printf ("%s renamed to %s\n", oname, nname);
			}
		}else if(oname != NULL){
			if (nname == NULL || !strcmp(nname,oname))
				printf("file %s No Change\n", oname);
		}
	}
	fclose(fp);
	fclose(fp2);
}

void ara_renamer(char* pth, int mkfile)
{
	struct _finddata_t x;
	char* oldname=x.name, ext[10]="", tmpname[260]="", newname[260]="", in=0;
	int done=0, lens=0;
	intptr_t handle;
	FILE* list;
	int s=0;

	handle = _findfirst( "*.*", & x);
	if(!mkfile)
	{
		if((list=fopen("undo","r"))){
			fclose(list);
			printf("This will remove the last undo...Continue?\n");
			in=getch();
			in=toupper(in);
			if(in!='Y' && in!=' ' && in!='\r'){
				printf("NO\n\n");
				return;
			}else if(remove("undo")){
				if (errno==EACCES)
					printf("Access Denied: file undo in use\n\n");
				return;
			}else
				printf("YES\n\n");
		}
		printf("do you want to limit the number of characters in the new names?\n");
		in=getch();
		in=toupper(in);
		if(in=='Y' || in==' ' || in=='\r'){
			printf("YES\n");
			while(!s){
				printf("Enter a number between 5 and 200\n");
				scanf("%d",&s);
				fflush( stdin );
				if(s<5 || s>200)
				{
					s=0;
					printf("Wrong Value. try again!..\n\n");
				}
			}
		}else
			printf("NO\n\n");
	}else if(mkfile){
		if((list=fopen("onames.txt","r"))){
			fclose(list);
			printf("File onames.txt aready exists...are you sure you want to overwrite?\n");
			in=getch();
			in=toupper(in);
			if(in!='Y' && in!=' ' && in!='\r'){
				printf("File not changed\n\n");
				return;
			}
		}
		list=fopen("onames.txt", "w+");
		if (!list){
			printf("Can't create file\n");
			return;
		}
		printf("Writing file...\n");
	}

	while ( !done )
	{
		if (strcmp(oldname,".") && strcmp(oldname,"..") && strcmp(oldname,pth) && !(x.attrib & _A_SUBDIR) && strcmp(x.name,"onames.txt") && strcmp(x.name,"nnames.txt") && strcmp(x.name,"undo"))
		{
			if(!mkfile)
			{
				ext[0]='\0';
				if(strrchr(oldname,'.'))
				{
					if((strlen(strrchr(oldname,'.')))<6)
						strcpy(ext, strrchr(oldname,'.'));
				}
				strncpy(tmpname,oldname,strlen(oldname)-strlen(ext));
				tmpname[strlen(oldname)-strlen(ext)]='\0';
				strcpy(newname, convrtit(tmpname));
				if (stricmp(tmpname, newname)){
					if (s){
						newname[s]='\0';
						tmpname[s]='\0';
					}
					if(ext)
						strcat(newname, ext);
					if(rename (oldname, newname)){
						if (errno==EEXIST)
							printf ("Permission denied: file %s already exists.\n", newname);
						if (errno==ENOENT)
							printf("%s doesn't exist\n", oldname);
						if (errno==EACCES)
							printf("Access Denied: file %s in use\n", oldname);
					}else{
						mkundo(oldname,newname);
						printf("%s renamed to %s\n", oldname, newname);
					}
				}else
					printf("File %s No Changes\n", oldname);
			}else if(mkfile){
				fprintf(list,"%s\n",oldname);
				printf("%s\n",oldname);

			}
		}
		done = _findnext( handle, & x );
	}
	_findclose(handle);
	if(mkfile)
	{
		fclose(list);
		CopyFileA("onames.txt","nnames.txt", 1);
		printf("\nfile onames.txt created successfully.\nEdit file nnames.txt to create new names\n\n");
	}
	return;
}

void mkundo(char* oldname,char *newname)
{
	FILE* list;

	if(list=fopen("undo","a"))
	{
		fprintf(list, "%s\n%s\n", newname, oldname);			
		fclose(list);
	}else
		printf("Can't create undo file\n");

}

char* convrtit(char ara_name[260])
{
	int n=0, v;
	char cnvr[3]="", eng_name[260]="";

	ara_name = Specialwords(ara_name);
	while (ara_name[n]){
		v=1;
		switch (ara_name[n])
		{
		case 'Ã':
		case 'Ç':
		case 'Â':
			cnvr[0]='a';
			break;
		case 'Å':
			cnvr[0]='e';
			break;
		case 'È':
			cnvr[0]='b';
			break;
		case 'Ê':
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
		case 'Ø':
			cnvr[0]='6';
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
		case 'É':
			cnvr[0]='h';
			break;
		case 'Ä':
			strcpy(cnvr, "u'");
			v=2;
			break;
		case 'æ':
			cnvr[0]='w';
			break;
		case 'í':
		case 'ì':
			cnvr[0]='y';
			break;
		case 'Á':
		case 'Æ':
			cnvr[0]='\'';
			break;
		case 'ò':
		case 'Ü':
			cnvr[0]='\0';
			break;
		default:
			cnvr[0]=ara_name[n];
			break;
		}

		if (v==1)
			cnvr[1]='\0';
		else
			cnvr[2]='\0';
		strcat(eng_name, cnvr);
		n++;
	}
	return eng_name;
}

char *Specialwords(char* ara_name)
{
	ara_name = _replace( ara_name, "ÇáäÇÓ", "An-Nas");
	ara_name = _replace( ara_name, "ÇáÝáÞ", "Al-Falaq");
	ara_name = _replace( ara_name, "ÇáÅÎáÇÕ", "Al-Ikhlas");
	ara_name = _replace( ara_name, "ÇáãÓÏ", "Al-Masadd");
	ara_name = _replace( ara_name, "ÇáäÕÑ", "An-Nasr");
	ara_name = _replace( ara_name, "ÇáßÇÝÑæä", "Al-Kafiroon");
	ara_name = _replace( ara_name, "ÇáßæËÑ", "Al-Kauther");
	ara_name = _replace( ara_name, "ÇáãÇÚæä", "Al-Ma3un");
	ara_name = _replace( ara_name, "ÞÑíÔ", "Quraish");
	ara_name = _replace( ara_name, "ÇáÝíá", "Al-Fil");
	ara_name = _replace( ara_name, "ÇáåãÒÉ", "Al-Humaza");
	ara_name = _replace( ara_name, "ÇáÚÕÑ", "Al-3asr");
	ara_name = _replace( ara_name, "ÇáÊßÇËÑ", "At-Takathur");
	ara_name = _replace( ara_name, "ÇáÞÇÑÚÉ", "Al-Qari3a");
	ara_name = _replace( ara_name, "ÇáÚÇÏíÇÊ", "Al-3adiyat");
	ara_name = _replace( ara_name, "ÇáÒáÒáÉ", "Az-Zalzala");
	ara_name = _replace( ara_name, "ÇáÈíäÉ", "Al-Bayyina");
	ara_name = _replace( ara_name, "ÇáÞÏÑ", "Al-Qadr");
	ara_name = _replace( ara_name, "ÇáÚáÞ", "Al-3alaq");
	ara_name = _replace( ara_name, "ÇáÊíä", "At-Tin");
	ara_name = _replace( ara_name, "ÇáÔÑÍ", "As-Sharh");
	ara_name = _replace( ara_name, "ÇáÖÍì", "Ad-Dhu7a");
	ara_name = _replace( ara_name, "Çááíá", "Al-Layl");
	ara_name = _replace( ara_name, "ÇáÔãÓ", "Ash-Shams");
	ara_name = _replace( ara_name, "ÇáÈáÏ", "Al-Balad");
	ara_name = _replace( ara_name, "ÇáÝÌÑ", "Al-Fajr");
	ara_name = _replace( ara_name, "ÇáÛÇÔíÉ", "Al-Ghashiya");
	ara_name = _replace( ara_name, "ÇáÃÚáì", "Al-A3la");
	ara_name = _replace( ara_name, "ÇáØÇÑÞ", "At-6ariq");
	ara_name = _replace( ara_name, "ÇáÈÑæÌ", "Al-Burooj");
	ara_name = _replace( ara_name, "ÇáÇäÔÞÇÞ", "Al-Inshiqaq");
	ara_name = _replace( ara_name, "ÇáãØÝÝíä", "Al-Mutaffifin");
	ara_name = _replace( ara_name, "ÇáÇäÝØÇÑ", "Al-Infi6ar");
	ara_name = _replace( ara_name, "ÇáÊßæíÑ", "At-Takwir");
	ara_name = _replace( ara_name, "ÚÈÓ", "3basa");
	ara_name = _replace( ara_name, "ÇáäÇÒÚÇÊ", "An-Nazi3at");
	ara_name = _replace( ara_name, "ÇáäÈÃ", "An-Nab'");
	ara_name = _replace( ara_name, "ÇáãÑÓáÇÊ.rm", "Al-Mursalat");
	ara_name = _replace( ara_name, "ÇáÅäÓÇä.rm", "Al-Insan");
	ara_name = _replace( ara_name, "ÇáÞíÇãÉ.rm", "Al-Qiyama");
	ara_name = _replace( ara_name, "ÇáãÏËÑ", "Al-Muddather");
	ara_name = _replace( ara_name, "ÇáãÒãá", "Al-Muzzammil");
	ara_name = _replace( ara_name, "ÇáÌä", "Al-Jinn");
	ara_name = _replace( ara_name, "äæÍ", "Noo7");
	ara_name = _replace( ara_name, "ÇáãÚÇÑÌ", "Al-Ma3arij");
	ara_name = _replace( ara_name, "ÇáÍÇÞÉ", "Al-7aaqqa");
	ara_name = _replace( ara_name, "ÇáÞáã", "Al-Qalam");
	ara_name = _replace( ara_name, "Çáãáß", "Al-Mulk");
	ara_name = _replace( ara_name, "ÇáÊÍÑíã", "At-Ta7rim");
	ara_name = _replace( ara_name, "ÇáØáÇÞ", "At-Talaq");
	ara_name = _replace( ara_name, "ÇáÊÛÇÈä", "At-Taghabun");
	ara_name = _replace( ara_name, "ÇáãäÇÝÞæä", "Al-Munafiqoon");
	ara_name = _replace( ara_name, "ÇáÌãÚÉ", "Al-Jumu3a");
	ara_name = _replace( ara_name, "ÇáÕÝ", "As-Saff");
	ara_name = _replace( ara_name, "ÇáããÊÍäÉ", "Al-Mumta7ana");
	ara_name = _replace( ara_name, "ÇáÍÔÑ", "Al-7ashr");
	ara_name = _replace( ara_name, "ÇáãÌÇÏáÉ", "Al-Mujadala");
	ara_name = _replace( ara_name, "ÇáÍÏíÏ", "Al-7adid");
	ara_name = _replace( ara_name, "ÇáæÇÞÚÉ", "Al-Waqi3a");
	ara_name = _replace( ara_name, "ÇáÑÍãä", "Ar-Ra7man");
	ara_name = _replace( ara_name, "ÇáÞãÑ", "Al-Qamar");
	ara_name = _replace( ara_name, "ÇáäÌã", "An-Najm");
	ara_name = _replace( ara_name, "ÇáØæÑ", "At-6ur");
	ara_name = _replace( ara_name, "ÇáÐÇÑíÇÊ", "Az-Zariyat");
	ara_name = _replace( ara_name, "ÇáÍÌÑÇÊ", "Al-7ujraat");
	ara_name = _replace( ara_name, "ÇáÝÊÍ", "Al-Fat7");
	ara_name = _replace( ara_name, "ãÍãÏ", "Muhammad");
	ara_name = _replace( ara_name, "ÇáÃÍÞÇÝ", "Al-A7qaf");
	ara_name = _replace( ara_name, "ÇáÌÇËíÉ", "Al-Jathiya");
	ara_name = _replace( ara_name, "ÇáÏÎÇä", "Ad-Dukhan");
	ara_name = _replace( ara_name, "ÇáÒÎÑÝ", "Az-Zukhruf");
	ara_name = _replace( ara_name, "ÇáÔæÑì", "Ash-Shura");
	ara_name = _replace( ara_name, "ÝÕáÊ", "Fussilat");
	ara_name = _replace( ara_name, "ÛÇÝÑ", "Ghafir");
	ara_name = _replace( ara_name, "ÇáÒãÑ", "Az-Zumar");
	ara_name = _replace( ara_name, "ÇáÕÇÝÇÊ", "As-Saaffat");
	ara_name = _replace( ara_name, "ÝÇØÑ", "Fa6er");
	ara_name = _replace( ara_name, "ÓÈÃ", "Saba'");
	ara_name = _replace( ara_name, "ÇáÃÍÒÇÈ", "Al-A7zab");
	ara_name = _replace( ara_name, "ÇáÓÌÏÉ", "As-Sajda");
	ara_name = _replace( ara_name, "áÞãÇä", "Luqman");
	ara_name = _replace( ara_name, "ÇáÑæã", "Ar-Room");
	ara_name = _replace( ara_name, "ÇáÚäßÈæÊ", "Al-3ankaboot");
	ara_name = _replace( ara_name, "ÇáÞÕÕ", "Al-Qasas");
	ara_name = _replace( ara_name, "Çáäãá", "An-Naml");
	ara_name = _replace( ara_name, "ÇáÔÚÑÇÁ", "Ash-Shu3ara'");
	ara_name = _replace( ara_name, "ÇáÝÑÞÇä", "Al-Furqan");
	ara_name = _replace( ara_name, "ÇáäæÑ", "An-Noor");
	ara_name = _replace( ara_name, "ÇáãÄãäæä", "Al-Mu'menoon");
	ara_name = _replace( ara_name, "ÇáÍÌ", "Al-7ajj");
	ara_name = _replace( ara_name, "ÇáÃäÈíÇÁ", "Al-Anbiya'");
	ara_name = _replace( ara_name, "ãÑíã", "Maryam");
	ara_name = _replace( ara_name, "ÇáßåÝ", "Al-Kahf");
	ara_name = _replace( ara_name, "ÇáÅÓÑÇÁ", "Al-Isra'");
	ara_name = _replace( ara_name, "ÇáäÍá", "An-Na7l");
	ara_name = _replace( ara_name, "ÇáÍÌÑ", "Al-7ijr");
	ara_name = _replace( ara_name, "ÅÈÑÇåíã", "Ibrahim");
	ara_name = _replace( ara_name, "ÇáÑÚÏ", "Ar-Ra3d");
	ara_name = _replace( ara_name, "íæÓÝ", "Yusuf");
	ara_name = _replace( ara_name, "åæÏ", "Hud");
	ara_name = _replace( ara_name, "íæäÓ", "Yunus");
	ara_name = _replace( ara_name, "ÇáÊæÈÉ", "At-Tawba");
	ara_name = _replace( ara_name, "ÇáÃäÝÇá", "Al-Anfal");
	ara_name = _replace( ara_name, "ÇáÃÚÑÇÝ", "Al-A3raf");
	ara_name = _replace( ara_name, "ÇáÃäÚÇã", "Al-An3aam");
	ara_name = _replace( ara_name, "ÇáãÇÆÏÉ", "Al-Ma'eda");
	ara_name = _replace( ara_name, "ÇáäÓÇÁ", "An-Nisa");
	ara_name = _replace( ara_name, "Âá ÚãÑÇä", "Aal-e-3imran");
	ara_name = _replace( ara_name, "ÇáÈÞÑÉ", "Al-Baqara");
	ara_name = _replace( ara_name, "ÇáÝÇÊÍÉ", "Al-Fatiha");
	ara_name = _replace( ara_name, "Çááå", "Allah");
	ara_name = _replace( ara_name, "ááå", "lelah");
	ara_name = _replace( ara_name, "ÇáÞÑÂä", "Al-Quran");
	ara_name = _replace( ara_name, "ÞÑÂä", "Quran");
	ara_name = _replace( ara_name, " Çá", " al-");

	/*buggy piece*/
	if(!strcmp(ara_name, "Þ"))
		ara_name = _replace( ara_name, "Þ", "Qaf");
	if(strstr(ara_name, " Þ"))
		if(!strcmp(strstr(ara_name, " Þ")+2, "") || !strcmp(strstr(ara_name, " Þ")+2, " "))
			ara_name = _replace( ara_name, " Þ", " Qaf");

	if(!strcmp(ara_name, "Õ"))
		ara_name = _replace( ara_name, "Õ", "Sad");
	if(strstr(ara_name, " Õ"))
		if(!strcmp(strstr(ara_name, " Õ")+2, "") || !strcmp(strstr(ara_name, " Õ")+2, " ") )
			ara_name = _replace( ara_name, " Õ", " Sad");

	if(!strcmp(ara_name, "íÓ") )
		ara_name = _replace( ara_name, "íÓ", "Ya-seen");
	if(strstr(ara_name, " íÓ"))
		if(!strcmp(strstr(ara_name, " íÓ")+3, "") || !strcmp(strstr(ara_name, " íÓ")+3, " ") )
			ara_name = _replace( ara_name, " íÓ", " Ya-seen");

	if(!strcmp(ara_name, "Øå") )
		ara_name = _replace( ara_name, "Øå", " 6aha");
	if(strstr(ara_name, " Øå"))
		if(!strcmp(strstr(ara_name, " Øå")+3, "") || !strcmp(strstr(ara_name, " Øå")+3, " ") )
			ara_name = _replace( ara_name, " Øå", " 6aha");
	/*buggy end*/


	return ara_name;
}

char *_replace (char *source_str, char *search_str, char *replace_str)
{
	char *p, *q, *s, *t, *newbuf = NULL;
	int count,newlen;
	int search_strlen = strlen (search_str);
	int replace_strlen = strlen (replace_str);
	int remainlen = 0;

	if(!source_str || !search_str || !replace_str)  
		return "Not enough arguments";
	if(!strstr(  source_str,  search_str ))  
		return source_str;
	for (count = 0, p = source_str; (q = strstr (p, search_str)) != NULL; p = q + search_strlen, count++) 
		;

	remainlen = strlen (p);
	if (count > 0) {
		newlen = strlen (source_str) + (count * strlen (replace_str) - count * search_strlen)+1;
		if ((newbuf = malloc (newlen)) != NULL)
		{
			memset (newbuf, '\0', newlen);
			for (s = p = source_str, t = newbuf; (q = strstr (p, search_str)) != NULL; ) 
			{
				memcpy (t, s, q - s);
				t += (q - s);
				memcpy (t, replace_str, replace_strlen);
				t += replace_strlen;
				s = p = q + search_strlen;
			}
			memcpy (t, s, remainlen);
			return newbuf;
		}
	}
	else
		return source_str;
} 

