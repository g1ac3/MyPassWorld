#include <bits/stdc++.h>
#include <conio.h>
#include "PWAUTH.h"
int N;
std::vector<std::vector<std::string>> S;
std::string MENU[8] ={"exit","TAG","ADD","TAG to Mail","TAGALL","CHANGE_PW","EDIT","ERASE"};
static const std::string DL = "=============\n";
static const int M=4;
//関数==================================================
//このアプリへのログイン================================
bool LogIn(){
  std::ifstream fin; //ファイル読み取り
  std::string line; //ファイルから読み取った文字列
  std::string pw; //パスワード入力させる
  fin.open("pw.txt",std::ios::in);
  std::getline(fin,line);
  return PWAUTH_check();
}
//上のパスワードの変更==================================
void CHA_PW(){
  std::string pw; //パスワード入力用文字列
  std::ofstream ofs("pw.txt"); //ファイルを開く
  std::cout<<"new pw : ";
  std::cin>>pw;
  ofs<<pw<<"\n";
  ofs.close();
}
//ファイルから配列に読み込み============================
void make_V(){
  std::ifstream fin;
  std::string line;
  fin.open("all.txt",std::ios::in);
  std::getline(fin,line);
  N = std::stoi(line); //アカウントの個数を読み取る
  S.clear(); //配列を初期化
  S.resize(N);
  for(int i=0;i<N;i++) for(int j=0;j<M;j++){ //順に読み取って行く
    std::getline(fin,line);
    S[i].emplace_back(line);
  }
  fin.close();
}
//追加==================================================
void ADD_INF(){
  std::ofstream ofs("all.txt");
  ofs<<std::to_string(N+1)<<"\n"; //個数+1してファイルに出力
  for(int i=0;i<N;i++)for(int j=0;j<M;j++) ofs<<S[i][j]<<"\n"; //最後まではそのままファイルに出力
  S.resize(++N); //データ一つ分配列を拡張
  for(int j=0;j<M;j++){ //TAG等の情報を順に入力
    std::string tmp;
    std::cout<<S[0][j]<<" : ";
    std::cin>>tmp;
    ofs<<tmp<<"\n";
    S[N-1].emplace_back(tmp);
  }
  ofs.close();
}
//TAGから検索===========================================変更予定(添字だけ記憶させるで良い？)
void TAG_in(int f){
  std::vector<std::pair<std::string,std::string>> tmp;
  std::string tag;
  if(f==0) std::cout<<"TAG : ";
  std::cin>>tag;
  for(int i=0;i<N;i++) if(tag==S[i][f]) tmp.emplace_back(std::make_pair(S[i][1],S[i][3]));
  std::cout<<DL;
  if(tmp.size()==0) std::cout<<"Not Found\n";
  else if(tmp.size()==1){
    std::cout<<"ID : "<<tmp[0].first<<"\n";
    std::cout<<"PW : "<<tmp[0].second<<"\n";
  }else{
    for(int i=0;i<(int)tmp.size();i++) std::cout<<"("<<i<<")ID : "<<tmp[i].first<<"\n";
    std::cout<<DL;
    int inp;
    std::cout<<"num : ";
    std::cin>>inp;
    if(0<=inp&&inp<(int)tmp.size()){
      std::cout<<"ID : "<<tmp[inp].first<<"\n";
      std::cout<<"PW : "<<tmp[inp].second<<"\n";
    }else std::cout<<"Not Found\n";
  }
  std::cout<<DL;
  return;
}
//TAGからメールアドレスを検索==========================上と同じく
void CHK_MAL(){
  std::vector<std::pair<std::string,std::string>> tmp;
  std::string tag;
  std::cout<<"TAG : ";
  std::cin>>tag;
  for(int i=0;i<N;i++) if(tag==S[i][0]) tmp.emplace_back(std::make_pair(S[i][1],S[i][2]));
  std::cout<<DL;
  if(tmp.size()==0) std::cout<<"Not Found\n";
  else{
    for(int i=0;i<(int)tmp.size();i++) std::cout<<"("<<i<<")ID : "<<tmp[i].first<<"\n MAIL : "<<tmp[i].second<<"\n";
  }
  std::cout<<DL;
}
//TAGを全て表示========================================
void TAG_ALL(){
  std::cout<<DL;
  for(int i=1;i<N;i++) std::cout<<"  "<<S[i][0]<<"\n"; //TAGだけを順に出力
  std::cout<<DL;
}
//データを編集したり消去したり=========================
void ERASEorEDIT(int select){//select==0 : edit, select==1 : erase
  int a,t;//変更するデータの添字、本当に実行するかどうかbool代わり
  std::cout<<DL;
  for(int i=1;i<N;i++) printf("(%3d) : %s\n",i,S[i][0].c_str()); //添字とTAGを列挙
  std::cout<<DL;
  std::cout<<"Num : ";
  std::cin>>a;
  if(a>=N||a<1) return;//aの値によっては表示がおかしくなるので厳しく
  std::cout<<DL;
  for(int i=0;i<M;i++) printf("  %5s: %s\n",S[0][i].c_str(),S[a][i].c_str());
  std::cout<<DL;
  if(select) std::cout<<"Do you want to delete this data? No:0 Yes:1   : "; //本当に実行するか確認
  else std::cout<<"Do you want to edit this data? No:0 Yes:1  : ";
  std::cin>>t;
  if(t){ //確認の変数が真なら
    std::ofstream ofs("all.txt");
    ofs<<std::to_string(N-select)<<"\n"; //editならselect=0で個数減らない、eraseならselect=1で減る
    for(int i=0;i<a;i++) for(int j=0;j<M;j++) ofs<<S[i][j]<<"\n"; //変更箇所まではそのままファイルに出力
    if(select == 0){//edit
      int b; //項目ごとに変更をするかbool
      for(int j=0;j<M;j++){
        printf("Do you edit '%s' ? No:0 Yes:1  : ",S[0][j].c_str()); //項目ごとに変更する確認する
        std::cin>>b;
        if(b){
          printf("%s > ",S[a][j].c_str());
          std::cin>>S[a][j]; //新しいデータを配列に入力
        }
        ofs<<S[a][j]<<"\n"; //それをファイルに出力
      }
    }
    for(int i=a+1;i<N;i++) for(int j=0;j<M;j++) ofs<<S[i][j]<<"\n"; //残りもそのまま出力
    ofs.close();
    make_V(); //変更したファイルからまた配列に読み取る
  }
  return;
}
//メニュー画面=========================================
bool IF(){
  for(int i=0;i<8;i++){ //メニューを表示
    if(i==6) std::cout<<DL;
    printf("%2d : %s\n",i,MENU[i].c_str());
  }
  int select; //メニュー選択
  std::cin>>select;
  switch(select){
    case 0: return false; //0 : 終了
    case 1: TAG_in(0); return true; //1 : TAGで検索
    case 2: ADD_INF(); return true; //2 : データを追加
    case 3: CHK_MAL(); return true; //3 : TAGからMAILを検索
    case 4: TAG_ALL(); return true; //4 : TAGを列挙
    case 5: PWAUTH_change(); return true;  //5 : このアプリのパスワード変更
    case 6: ERASEorEDIT(0); return true; //6 : データ編集
    case 7: ERASEorEDIT(1); return true; //7 : データ削除
  }
  return false;
}
//MAIN=================================================
int main(){
  if(!LogIn()) return 0; //最初にこのアプリを使うためのパスワードを入力
  make_V();
  while(IF());
}
/*to do
意図しない入力への対処
無駄削減

*/
