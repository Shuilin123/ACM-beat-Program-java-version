#include<Windows.h>
#include<stdio.h>
#include<commdlg.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
void Setting_envVar(){
	OPENFILENAME ofn;
	char FileName[MAX_PATH];
	memset(&ofn,0,sizeof(OPENFILENAME));
	memset(FileName,0,sizeof(char)*MAX_PATH); 
	ofn.lStructSize=sizeof(OPENFILENAME); 
	ofn.lpstrFilter=TEXT("All Files(*.*)\0*.*\0\0");
	ofn.lpstrFile=FileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=OFN_FILEMUSTEXIST;
	printf("Please select the java jdk path.\n");
	if(GetOpenFileName(&ofn)){
		  string str=FileName;
		  int index=str.find_last_of("\\"); 
		  string cmd1="setx \"JAVA_HOME\" \""+str.substr(0,index-1)+"\" /m";
		  string cmd2="setx \"PATH %PATH%;%JAVA_HOME%\\bin;%JAVA_HOME%\\jre\\bin\" /m";
		  const char* p = cmd1.data();
		  system(p);
		  cmd2="setx \"PATH %PATH%;%JAVA_HOME%\\bin\" /m";
		  p = cmd2.data();
		  system(p);cout<<p<<endl;
		  cmd2="setx \"PATH %PATH%;%JAVA_HOME%\\jre\\bin\" /m";
		  p = cmd2.data();
		  system(p);
		  string cmd3="setx \"ClassPath %ClassPath%;%JAVA_HOME%\\lib\\dt.jar\" /m";
		  p = cmd3.data();
		  system(p);
		  cmd3="setx \"ClassPath %ClassPath%;%JAVA_HOME%\\lib\\tools.jar\" /m";
		  p = cmd3.data();
		  system(p);  
	}
}
string run_java(int id){
	OPENFILENAME ofn;
	char FileName[MAX_PATH];
	memset(&ofn,0,sizeof(OPENFILENAME));
	memset(FileName,0,sizeof(char)*MAX_PATH);
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFilter=TEXT("Text Files(*java)\0*.java\0All Files(*.*)\0*.*\0\0");
	ofn.lpstrFile=FileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=OFN_FILEMUSTEXIST;
	string strx;
	if(GetOpenFileName(&ofn)){
	    string str=FileName;  
		string str0="javac "+str;
		const char* com=str0.data();
		system(com);
		int index=str.find_last_of("\\"); 
		string str1="cd "+str.substr(0,index);
		com=str1.data();
		system(com);
		int index2=str.find_last_of("."); 
		strx="java "+str.substr(index+1,index2-index-1)+" < ..\\data.in > ..\\answer"+to_string(id)+".out";
	    string strxx=str.substr(index+1,str.length()-index-1);
	    cout<<"The currently selected program is "<<strxx<<endl;
	}
	return strx;
}
string run_rand_data(){
	OPENFILENAME ofn;
	char FileName[MAX_PATH];
	memset(&ofn,0,sizeof(OPENFILENAME));
	memset(FileName,0,sizeof(char)*MAX_PATH);
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFilter=TEXT("Text Files(*java)\0*.java\0All Files(*.*)\0*.*\0\0");
	ofn.lpstrFile=FileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=OFN_FILEMUSTEXIST;
	string strx;
	if(GetOpenFileName(&ofn)){
	    string str=FileName;  
		string str0="javac "+str;
		const char* com=str0.data();
		system(com);
		int index=str.find_last_of("\\"); 
		string str1="cd "+str.substr(0,index);
		com=str1.data();
		system(com);
		int index2=str.find_last_of("."); 
		strx="java "+str.substr(index+1,index2-index-1);
		string strxx=str.substr(index+1,str.length()-index-1);
	    cout<<"The currently selected program is "<<strxx<<endl;
	}
	return strx;
}

int main(){
	//配置系统环境变量
	#ifdef ENV_VAR
	   Setting_envVar();
	#endif 
	//获取jdk路径
	//编译java1
	printf("Step1.Please select the program you want to compare 1(.java).\n"); 
	string strx=run_java(1);
	//编译java2
	printf("Step2.Please select the program you want to compare 2(.java).\n");  
	string stry=run_java(2);
	printf("Step3.Please select datator.\n");
	string strz=run_rand_data();
	const char*com1=strz.data();
	const char*com2=strx.data();
	const char*com3=stry.data();
	int cnt=0;
	printf("begin testing......\n");
	while(1){
		// 导入数据 
		system(com1);
	    system(com2);
	    system(com3);
	    cout<<"current id:"<<cnt<<endl;
	    if(++cnt>=1000){
	    	cout<<"test successful!"<<endl;
	    	break;
		}
	    if(system("fc ..\\answer1.out ..\\answer2.out")){
		  cout<<"find erro!"<<endl;
		  break;
	    }
	}
	printf("\nTranslation completion----by shuilin.\n"); 		
	system("pause");
    return 0;
}
