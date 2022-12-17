/*
Creator: Nicolas Brambilla Rodrigues
Instagram: @nickrois_
Github: github.com/nickrois
Description: Development of an organization tool in c++ with no visual framework on Windows.
-Thanks Bruno for the help with the files.
*/

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

typedef struct no{
  string title;
  string desc;
  string resp;
  int member;
}bloco;

map<int, int> color { {1, 0x50 }, {2, 0xD0 },
                      {3, 0x40 }, {4, 0xC0 },
                      {5, 0x30 }, {6, 0xB0 },
                      {7, 0x10 }, {8, 0x90 },
                      {9, 0x60 }, {10, 0xF0 } };

map<int, string> team;

void print(const vector<bloco>& a);

int pass(vector<bloco>& a,vector<bloco>& b,vector<bloco>& c,int &back, bloco& backCard);

void goBack(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,int& back,int& back2, bloco& backCard);

void eraseCards(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c, map<int, string>& team);

void printTeam();

void add(vector<bloco>& a, vector<bloco>& c, vector<bloco>& d, bloco& backCard);

int nextPos(vector<bloco>& a, string s);

void rem(vector<bloco>& a,vector<bloco>& b,vector<bloco>& c,bloco& backCard,int& back2);

void readDesc(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,int& back,int& back2, bloco& backCard);

void saveFile(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,map<int, string>& team);

void readFile(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,map<int, string>& team);

int main(){
  int op=0,back[2]={0,0};
  bloco backCard;
  string erase;

  vector<bloco> todo;
  vector<bloco> doing;
  vector<bloco> done;

  todo.clear();
  doing.clear();
  done.clear();

  readFile(todo,doing,done,team);

  system("color F0");
  while(op!=8){
    system("cls");
    saveFile(todo,doing,done,team);
    cout << "TO DO: ";
    print(todo);
    cout << endl << "DOING: ";
    print(doing);
    cout << endl << "DONE: ";
    print(done);
    cout << endl << "TEAM: ";
    printTeam();
    cout << endl << endl << endl;
    cout << "1- Add card" << endl;
    cout << "2- Move a card to next stage" << endl;
    cout << "3- Remove card " << endl;
    cout << "4- Read description " << endl;
    cout << "5- Go back " << endl;
    cout << "6- Erase all cards " << endl;
    cout << "8- Sair" << endl << endl;
    cout << "Choose: ";
    fflush(stdin);
    cin >> op;
    while(getchar()!='\n');

    switch(op){
      case 1:
        add(todo,doing,done,backCard);
        back[0] = 1;
        break;
      case 2:
        if(pass(todo,doing,done,back[1],backCard))
          back[0]=2;
        break;
      case 3:
        rem(todo,doing,done,backCard,back[1]);
        back[0]=3;
        break;
      case 4:
        readDesc(todo,doing,done,back[0],back[1],backCard);
        break;
      case 5:
        goBack(todo,doing,done,back[0],back[1],backCard);
        break;
      case 6:
        cout << "THIS ACTION CANNOT BE UNDONE. PROCEED? [Y/N]" << endl;
        getline(cin,erase);
        if(erase=="Y"){
          eraseCards(todo,doing,done,team);
          back[0] = 5;
        }else{
          cout << "CANCELLED [enter]" << endl;
          while(getchar()!='\n');
        }
        break;
      case 8:
        system("cls");
        return 0;
        break;
      default:
        cout << endl << "Invalid option [enter]" << endl;
        while(getchar()!='\n');
        break;
    }
  }

  return 0;
}//end main

void eraseCards(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,map<int, string>& team){
  a.clear();
  b.clear();
  c.clear();
  team.clear();
}//end eraseCards

void readFile(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,map<int, string>& team){ //M N O P Q
  fstream file;
  bloco control;
  int map;
  string mapi,map2;
  string s;
  string numero;

  file.open("cards.txt");

  if(file.fail()){
    cout << "File failed to open [enter]" << endl;
    getchar();
    return;
  }

  while(getline(file,s)){
    if(s=="N" || s=="M" || s=="O"){
      getline(file,control.title); //recebe informacoes
      getline(file,control.desc);
      getline(file,control.resp);
      getline(file,numero);
      control.member = stoi(numero);
    }

    if(s=="N")
      a.push_back(control); //salva informacoes no PROGRAMA
    else if(s=="M")
      b.push_back(control);
    else if(s=="O")
      c.push_back(control);
    else if(s=="P"){
      getline(file,numero);
      map = stoi(numero);
      getline(file,map2);
      team.insert(pair<int, string>(map, map2));
    }else if(s=="0")
      break;

  }

  file.close();

}//end readFile

void saveFile(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,map<int, string>& team){
  fstream file;
  file.open("cards.txt", fstream::out | fstream::trunc);

  for(int i=0;i<a.size();i++){ //salva info no arquivo
    file << "N" << endl; //salva sinalizador
    file << a[i].title << endl; //salva infos
    file << a[i].desc << endl;
    file << a[i].resp << endl;
    file << a[i].member << endl;
  }

  for(int i=0;i<b.size();i++){
    file << "M" << endl; //para pegar no getline da hora de ler
    file << b[i].title << endl;
    file << b[i].desc << endl;
    file << b[i].resp << endl;
    file << b[i].member << endl;
  }

  for(int i=0;i<c.size();i++){ //mesmo para vec 3
    file << "O" << endl;
    file << c[i].title << endl;
    file << c[i].desc << endl;
    file << c[i].resp << endl;
    file << c[i].member << endl;
  }

  for (const auto &team : team){ //mesmo para map
    file << "P" << endl;
    file << team.first << endl << team.second << endl;
  }

  file << "0" << endl;

  file.close();
}//end saveFile

void readDesc(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c, int& back, int& back2, bloco& backCard){
  string s;
  bool read=false;

  cout << "Type the title to read the description: " << endl;
  getline(cin,s);

  for(int i=0; i<a.size(); i++){
    if(a[i].title == s)
      read = true;
    if(read){
      system("cls");
      cout << a[i].desc << endl << endl << "Leave [enter]" << endl;
      back=4;
      back2=1;
      backCard = a[i];
      while(getchar()!='\n');
      return;
    }
  }
  for(int i=0; i<b.size(); i++){
    if(b[i].title == s)
      read = true;
    if(read){
      system("cls");
      cout << b[i].desc << endl << endl << "Leave [enter]" << endl;
      back=4;
      back2=2;
      backCard = b[i];
      while(getchar()!='\n');
      return;
    }
  }

  for(int i=0; i<c.size(); i++){
    if(c[i].title == s)
      read = true;
    if(read){

      system("cls");
      cout << c[i].desc << endl << endl << "Leave [enter]" << endl;
      back=4;
      back2=3;
      backCard = c[i];
      while(getchar()!='\n');
      return;
    }
  }

  if(!read){
    cout << endl << "Title does not exist [enter]" << endl;
    while(getchar()!='\n');
  }
}//end readDesc

int pass(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c, int& back, bloco& backCard){
  string control;
  int aux;

  cout << "Type the title to be passed on: " << endl;
  getline(cin,control);

  aux=nextPos(a,control);
  if(aux>=0){
    b.push_back(a[aux]);
    backCard = a[aux];
    a.erase(a.begin()+aux);
    back=1;
    return 1;
  }
  aux=nextPos(b,control);
  if(aux>=0){
    c.push_back(b[aux]);
    backCard = b[aux];
    b.erase(b.begin()+aux);
    back=2;
    return 1;
  }

  aux=nextPos(c,control);
  if(aux>=0){
    cout << "It's already on the last stage. Yay! [Enter]" << endl;
    back=3;
    while(getchar()!='\n');
    return 1;
  }

  cout << "Element not found [enter]" << endl;
  while(getchar()!='\n');
  return 0;
}//end pass

void goBack(vector<bloco>& a, vector<bloco>& b, vector<bloco>& c,int& back, int& back2, bloco& backCard){
  if(back==1){
    int n;
    bool remove=false;

    for (int i=0; i<a.size(); i++){
      if(a[i].title == backCard.title)
        remove = true;
      if(remove){
        n = a[i].member;
        backCard = a[i];
        back=3;
        back2=1;
        a.erase(a.begin()+i);
        cout << "Gone back succesfully [enter]" << endl;
        while(getchar()!='\n');
      }
    }

    if(remove){
      for (int i=0; i<a.size(); i++){
        if(a[i].member == n)
          remove = false;
      }
      for (int i=0; i<b.size(); i++){
        if(b[i].member == n)
          remove = false;
      }
      for (int i=0; i<c.size(); i++){
        if(c[i].member == n)
          remove = false;
      }
      if(remove)
        team.erase(n);

      return;
    }

  }else if(back==2){
    int n;
    bool voltar=false;
    if(back2==1){
      for(int i=0; i<b.size(); i++){
        if(b[i].title == backCard.title)
          voltar = true;
        if(voltar){
          b.erase(b.begin()+i);
          a.push_back(backCard);
          back=5;
          cout << "Gone back succesfully [enter]" << endl;
          while(getchar()!='\n');
          break;
        }
      }
    }else if(back2==2){
      for(int i=0; i<c.size(); i++){
        if(c[i].title == backCard.title)
          voltar = true;
        if(voltar){
          c.erase(c.begin()+i);
          b.push_back(backCard);
          back=2;
          back2=1;
          cout << "Gone back succesfully [enter]" << endl;
          while(getchar()!='\n');
          break;
        }
      }
    }else if(back2==3){
      cout << "Last move wasn't valid [enter]" << endl;
      back=5;
      while(getchar()!='\n');
    }
  }else if(back==3){
    if(back2==1){
      a.push_back(backCard);
      if(!team.count(backCard.member))
        team.insert(pair<int, string>(backCard.member, backCard.resp));
    }else if(back2=2){
      b.push_back(backCard);
      if(!team.count(backCard.member))
        team.insert(pair<int, string>(backCard.member, backCard.resp));
    }else if(back2=3){
      c.push_back(backCard);
      if(!team.count(backCard.member))
        team.insert(pair<int, string>(backCard.member, backCard.resp));
    }
    back=5;
  }else if(back==4){
    bool read=false;
    if(back2==1){
      for(int i=0; i<a.size(); i++){
        if(a[i].title == backCard.title)
          read = true;
        if(read){
          system("cls");
          cout << a[i].desc << endl << endl << "Leave [enter]" << endl;
          while(getchar()!='\n');
        }
      }
    }else if(back2==2){
      for(int i=0; i<b.size(); i++){
        if(b[i].title == backCard.title)
          read = true;
        if(read){
          system("cls");
          cout << b[i].desc << endl << endl << "Leave [enter]" << endl;
          while(getchar()!='\n');
        }
      }
    }else if(back2==3){
      for(int i=0; i<c.size(); i++){
        if(c[i].title == backCard.title)
          read = true;
        if(read){
          system("cls");
          cout << c[i].desc << endl << endl << "Leave [enter]" << endl;
          while(getchar()!='\n');
        }
      }
    }else{
      cout << "Last move wasn't valid [enter]" << endl;
      back=5;
      while(getchar()!='\n');
    }
  }else{
    cout << "Last move wasn't valid [enter]" << endl;
    back=5;
    while(getchar()!='\n');
  }
}//end goBack


void print(const vector<bloco>& a){

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // comandos do cmd para definir hConsole
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

  WORD saved_attributes;
  /* Salvar estado atual */
  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes; // salva config base do cmd

  for (int i=0; i<a.size(); i++){
    SetConsoleTextAttribute(hConsole, color[a[i].member]);
    cout << "[" << a[i].member << "- " << a[i].title << "]";
    SetConsoleTextAttribute(hConsole, saved_attributes);
    cout << " ";
    if(!((i+1)%8))
      cout << endl;
  }
  cout << endl;

}//end print

void printTeam(){
  if(team.size()>0){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // comandos do cmd para definir hConsole
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    WORD saved_attributes;
    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes; // salva config base do cmd

    for (const auto &team : team){
      SetConsoleTextAttribute(hConsole, color[team.first]);
      cout << "[ " << team.first << "-" << team.second << " ]";
      SetConsoleTextAttribute(hConsole, saved_attributes);
      cout << " ";
    }
    cout << endl;
  }else{
    cout << "NO RESPONSIBLES" << endl;
  }
}//end printTeam

void add(vector<bloco>& a, vector<bloco>& c, vector<bloco>& d, bloco& backCard){
  bloco b;
  bool insereteam=true,inserecard=true;

  cout << "Enter title: ";
  getline(cin,b.title);

  for (int i=0; i<a.size(); i++){
    if(a[i].title == b.title)
      inserecard = false;
  }
  for (int i=0; i<c.size(); i++){
    if(c[i].title == b.title)
      inserecard = false;
  }
  for (int i=0; i<d.size(); i++){
    if(d[i].title == b.title)
      inserecard = false;
  }

  if(!inserecard){
    cout << "Title already in use [enter]";
    while(getchar()!='\n');
    return;
  }

  cout << "Enter description: ";
  getline(cin,b.desc);

  cout << "Enter member responsible(number from 1 to 10): ";
  cin >> b.member;
  while(getchar()!='\n');
  if(b.member>10 || b.member < 0)
    return;

  if(team.count(b.member))
    insereteam = false;

  cout << "Enter member responsible(name): ";
    getline(cin,b.resp);

  if(insereteam){
    team.insert(pair<int, string>(b.member, b.resp));
  }

  backCard = b;
  a.push_back(b);

}//end add

void rem(vector<bloco>& a,vector<bloco>& b,vector<bloco>& c,bloco& backCard,int& back2){
  string s;
  int n;
  bool remove=false;

  cout << "Title to be removed: ";
  getline(cin,s);

  for (int i=0; i<a.size(); i++){
    if(a[i].title == s)
      remove = true;
    if(remove){
      n = a[i].member;
      back2 = 1;
      backCard = a[i];
      a.erase(a.begin()+i);
      cout << "Card removed succesfully [enter]" << endl;
      while(getchar()!='\n');
    }
  }

  for (int i=0; i<b.size(); i++){
    if(b[i].title == s)
      remove = true;
    if(remove){
      n = b[i].member;
      back2 = 2;
      backCard = b[i];
      b.erase(b.begin()+i);
      cout << "Card removed succesfully [enter]" << endl;
      while(getchar()!='\n');
    }
  }

  for (int i=0; i<c.size(); i++){
    if(c[i].title == s)
      remove = true;
    if(remove){
      n = c[i].member;
      back2 = 3;
      backCard = c[i];
      c.erase(c.begin()+i);
      cout << "Card removed succesfully [enter]" << endl;
      while(getchar()!='\n');
    }
  }

  if(remove){
    for (int i=0; i<a.size(); i++){
      if(a[i].member == n)
        remove = false;
    }
    for (int i=0; i<b.size(); i++){
      if(b[i].member == n)
        remove = false;
    }
    for (int i=0; i<c.size(); i++){
      if(c[i].member == n)
        remove = false;
    }
    if(remove)
      team.erase(n);

    return;
  }

  cout << "Card doesn't exist [enter]" << endl;
  while(getchar()!='\n');

}//end rem

int nextPos(vector<bloco>& a, string s){

  for (int i=0; i<a.size(); i++)
    if(a[i].title == s)
      return i;

  return -1;
}//end nextPos
