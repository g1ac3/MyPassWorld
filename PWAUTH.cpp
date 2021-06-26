#include <bits/stdc++.h>
#include <conio.h>
#include "PWAUTH.h"
const int N = 79;
std::string ofile = "pw.txt";
//パスワード入力させて入力した文字列を返す。
std::string PWAUTH_input(){
  std::string s;
  char c;
  std::cout<<"PW : ";
  while(1){
    if(kbhit()){
      if((c=getch())=='\r') break;
      std::cout<<"*";
      s+=c;
    }
  }
  std::cout<<"\n";
  return s;
}
//string型の平文のパスワードを受け取ってハッシュ化して返す。
std::string PWAUTH_hash(std::string s){
  const int M = 16;
  const int s_size1 = s.size();
  for(int i=0;i<M-s_size1;++i) s+=s[i%s_size1];
  //std::cout<<"\n"<<s<<"\n";
  std::vector<int> A,B;
  for(int i=0;i<M;i++) A.emplace_back((i+1)*5);
  for(int i=0;i<M;i++) A[i]+=(s[i]-'0');
  for(int i=0;i<M;i++) B.emplace_back(((A[i]^A[(i+1)%M])|A[(i+2)%M])&A[(i+3)%M]);
  std::string S;
  for(int x:B) S+=(x%N+'0');
  return S;
}
//パスワード変更
void PWAUTH_change(){
  std::cout<<"_";
  std::ofstream ofs(ofile);
  std::cout<<"Create New Password\n";
  ofs<<PWAUTH_hash(PWAUTH_input())<<"\n";
}
//パスワードをofileで指定した名前のテキストファイルから読み取り一致するか確認
bool PWAUTH_check(){
  std::ifstream fin;
  std::string line;
  fin.open(ofile,std::ios::in);
  std::getline(fin,line);
  fin.close();
  return line == PWAUTH_hash(PWAUTH_input());
}
