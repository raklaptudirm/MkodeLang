#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <windows.h>

using namespace std;
int code_length, var_num=0,var_no;
const string version="v0.3.2.1";
string vars_="",var_values="", err_det="OK";
string keywords[]={"Console","out","clear","nextLine","Kode","halt","in","NaN","infinity"};
string var_keys[]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","1","2","3","4","5","6","7","8","9","0","$","_"};
string var_start[]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","_"};

//-----------------------------------------
void header(){
    cout << "Mkode [Version:"<<version<<"] copyright (c) 2020 Rak Laptudirm" << endl << "Mkode console compiler application" << "\n\n";
}
//-----------------------------------------
string clearall(string clr){
    string clr_store="", clr_char;
    int clr_count;
    for (clr_count=0;clr_count<clr.size();clr_count++){
        clr_char=clr[clr_count];
        if (clr_char!=" "){
            clr_store=clr_store+clr_char;
        }
    }
    return clr_store;
}
//-----------------------------------------
string remove(string str){
    string str_char, str_store="";
    int str_count;
    for (str_count=0;str[str_count]==' ';str_count++){
    }
    for (;str_count<str.size();str_count++){
        str_char=str[str_count];
        str_store=str_store+str_char;
    }
    str_store="";
    for (str_count=str.length()-1;str_count>=0;str_count--){
        str_char=str[str_count];
        if (str_char!=" "){
            break;
        }
    }
    for (;str_count>=0;str_count--){
        str_char=str[str_count];
        str_store=str_char+str_store;
    }
    return str_store;
}
//-----------------------------------------
int check(string check){
    string ch_store;
    check=remove(check);
    if ((check[0]=='\''&&check[check.size()-1]=='\'')||(check[0]=='\"'&&check[check.size()-1]=='\"')){
        return 1;
    } else if ((check[0]=='0'||check[0]=='1'||check[0]=='2'||check[0]=='3'||check[0]=='4'||check[0]=='5'||check[0]=='6'||check[0]=='7'||check[0]=='8'||check[0]=='9'||check[0]=='-'||check[0]=='+')||(check=="NaN"||check=="infinity")){
        return 2;
    } else {
        return 3;
    }
}
//-----------------------------------------
string var_exists(string varr){
    var_no=0;
    string par_store, par_char;
    int par_count;
    par_store="";
    for (par_count=0;par_count<vars_.size();par_count++){
        par_char=vars_[par_count];
        if (par_char==","){
            var_no++;
            if (par_store==varr){
                return "OK";
            }
            par_store="";
        } else {
            par_store=par_store+par_char;
        }
    }
    return "Variable >> "+varr+" doesn't exist";
}
//-----------------------------------------
string get_val(string variable){
    variable=clearall(variable);
    err_det="OK";
    string get_char, get_store;
    int get_count, get_count2=0;
    get_store= var_exists(variable);
    if (get_store!="OK"){
        err_det=get_store;
        return get_store;
    }
    get_store="";
    for (get_count=0;get_count<var_values.size();get_count++){
        get_char=var_values[get_count];
        if (get_char==","){
            get_count2++;
            if (get_count2==var_no){
                return get_store;
            }
            get_store="";
        } else {
            get_store=get_store+get_char;
        }
    }
}
//-----------------------------------------

//-----------------------------------------
string set_var(string named, string value){
    int set_count, set_count2=0;
    string set_char, set_store, set_store2="";
    set_store=var_exists(named);
    if (set_store!="OK"){
        return set_store;
    }
    set_store="";
    for (set_count=0;set_count<var_values.size();set_count++){
        set_char=var_values[set_count];
        if (set_char==","){
            set_count2++;
            if (set_count2==var_no){
                set_store=value;
            }
            set_store2=set_store2+set_store+",";
            set_store="";
        } else {
            set_store=set_store+set_char;
        }
    }
    var_values=set_store2;
    return "OK";
}
//-----------------------------------------
string declare(int data,string name,string value){
    int dec_count, ok=0, dec_count2;
    string dec_chars,dec_store;
    for (dec_count=0;dec_count<9;dec_count++){
        if(name==keywords[dec_count]){
            ok=1;
        }
    }
    if (ok==1){
        return "Variable cant be a keyword";
    }
    for (dec_count=0;dec_count<53;dec_count++){
        dec_chars=name[0];
        if(dec_chars==var_start[dec_count]){
            ok=1;
        }
    }
    if (ok==0){
        return dec_chars+" is not allowed in >> "+name;
    } 
    for (dec_count=1;dec_count<name.size();dec_count++){
        ok=0;
        dec_chars=name[dec_count];
        for (dec_count2=0;dec_count2<64;dec_count2++){
            if(dec_chars==var_keys[dec_count2]){
                ok=1;
            }
        }
        if (ok==0){
            return "Illeagal character in >> "+name;
        }
    }
    ok=0;
    dec_store=var_exists(name);
    if (dec_store=="OK"){
        return "Redeclartion of Variable >> "+name;
    }
    vars_=vars_+name+",";
    var_values=var_values+value+",";
    var_num++;
    return "OK";
}
//-----------------------------------------
string parse(string st_parse) { //String Parser
    string output="", st_char,st_sto="";
    int st_count, st_string=0;
    st_parse=remove(st_parse);
    if (st_parse[0]=='\''&&st_parse[st_parse.size()-1]=='\''){
        for (st_count=1;st_count<st_parse.size()-1;st_count++){
            st_char=st_parse[st_count];
            st_sto=st_sto+st_char;
        }
    } else if (st_parse[0]=='\"'&&st_parse[st_parse.size()-1]=='\"'){
        for (st_count=1;st_count<st_parse.size()-1;st_count++){
            st_char=st_parse[st_count];
            if (st_char=="\\"){
                if (st_parse[st_count+1]=='\''||st_parse[st_count+1]=='\"'||st_parse[st_count+1]=='\\'){
                    st_char=st_parse[st_count+1];
                    st_count++;
                }
            }
            st_sto=st_sto+st_char;
        }
    } else {
        return st_parse;
    }
    return st_sto;
}
//------------------------------------------
string do_op(string ag1, string ag2, string op){
    err_det="OK";
    if (ag1=="NaN"||ag2=="NaN"){
        return "NaN";
    } else if (ag1=="infinity"||ag2=="infinity"){
        if (ag2=="infinity"&&(op=="/"||op=="%")){
            return "NaN";
        } else {
            return "infinity";
        }
    }
    double ar1, ar2, ans;
    int arg1, arg2;
    string ret;
    stringstream answer;
    stringstream a1(ag1);
    if (op!="%"){
        a1 >> ar1;
    } else {
        a1 >> arg1;
    }
    stringstream a2(ag2);
    if (op!="%"){
        a2 >> ar2;
    } else {
        a2 >> arg2;
    }
    
    if (op=="+"){
        ans=ar1+ar2;
    } else if (op=="-"){
        ans=ar1-ar2;
    } else if (op=="*"){
        ans=ar1*ar2;
    } else if (op=="/"){
        if (ar2==0){
            return "NaN";
        }
        ans=ar1/ar2;
    } else if (op=="%"){
        if (arg2==0){
            return"NaN";
        }
        ans=arg1%arg2;
    } else {
        err_det="Error >> Operator"+op;
        return "Error >> Operator"+op;
    }
    answer << ans;
    answer >> ret;
    return ret;
}
//-----------------------------------------
string evaluate(string ex){ //Evaluator
    err_det="OK";
    int st_count, st_list=0, last=1, st_count2, st_count3, pre, minus=0, type, siq=0, doq=0;
    string st_chars="", st_store="", calc[ex.size()];
    string temp, tem1, tem2;
    string precedence[6]={"@","/","%","*","+","-"};
    for (st_count=0;st_count<ex.size();st_count++){//Seperating calc
        st_chars=ex[st_count];
        if ((st_chars!="+"&&st_chars!="-" &&st_chars!="*"&&st_chars!="/"&&st_chars!="%"&&st_chars!="@")||st_count==0||(siq==1||doq==1)){
            st_store=st_store+st_chars;
            last=0;
            if ((st_count>0&&ex[st_count-1]!='\\')||(st_count==0)){
                if (st_chars=="\""&&siq==0){
                    if (doq==0){
                        doq=1;
                    } else {
                        doq=0;
                    }
                } else if (st_chars=="\'"&&doq==0){
                    if (siq==0){
                        siq=1;
                    } else {
                        siq=0;
                    }
                }
            }
        } else {
            if (last==1){
                system("cls");
                cerr << "Two calc next to one another";
                err_det="Two calc next to one another";
                return "2";
            }
            if (st_store==""){
                system("cls");
                cerr << "Two calc next to one another";
                err_det="Two calc next to one another";
                return "2";
            }
            calc[st_list]=st_store;
            st_list++;
            calc[st_list]=st_chars;
            st_list++;
            last=1;
            st_store="";
        }
    }
    calc[st_list]=st_store;
    st_list++;
    if (st_list==1){
        type=check(calc[0]);
        if (type==1){
            tem1=parse(calc[0]);
        } else if (type==2){
            tem1=calc[0];
        } else {
            tem1=get_val(calc[0]);
            if (err_det!="OK"){
                return tem1;
            }
        }
        st_store=tem1;
    } else {
        for (st_count=0;st_count<6;st_count++){
            if (calc[0]=="+"||calc[0]=="-"){
                pre=2;
            } else {
                pre=1;
            }
            for (;pre<st_list;pre=pre+2){
                if (calc[pre]==precedence[st_count]){ 
                    minus=0;
                    if (pre!=1){
                        if((calc[pre]=="+"||calc[pre]=="-")&&calc[pre-2]=="-"){
                            calc[pre-1]="-"+calc[pre-1];
                            minus=1;
                        }
                    }
                    type=check(calc[pre-1]);
                    if (type==1){
                        tem1=parse(calc[pre-1]);
                    } else if (type==2){
                        tem1=calc[pre-1];
                    } else {
                        tem1=get_val(calc[pre-1]);
                        if (err_det!="OK"){
                            return tem1;
                        }
                    }
                    type=check(calc[pre+1]);
                    if (type==1){
                        tem2=parse(calc[pre+1]);
                    } else if (type==2){
                        tem2=calc[pre+1];
                    } else {
                        tem2=get_val(calc[pre+1]);
                        if (err_det!="OK"){
                            return tem2;
                        }
                    }
                    if (calc[pre]!="@"){
                        st_store=do_op(tem1,tem2,calc[pre]);
                    } else {
                        st_store="\'"+tem1+tem2+"\'";
                    }
                    if (err_det!="OK"){
                        return st_store;
                    }
                    calc[pre+1]=st_store;
                    calc[pre-1]="";
                    calc[pre]="";
                    st_count3=pre-1;
                    if (minus==1){
                        calc[pre-2]="+";
                    }
                    //Expulsing voids----------------------------
                    for (st_count2=st_count3;(st_count2+2)<st_list;st_count2++){
                        temp=calc[st_count2+2];
                        calc[st_count2]=temp;
                        pre=1;
                    }
                    st_list=st_list-2;
                    pre=pre-2;
                    //--------------------------------------------
                }
            }
        }
    }
    return parse(st_store);
    
}

//------------------------------------------
string UES(string u_ex){
    int p_depth=0, p_count=0, p_con=0, p_list=0, p_de[u_ex.size()+2], highest_b=0, p_count2, p_count3, stacks=0, prev_b=0, sub=0,p_count4,str, sq=0, dq=0;
    string p_store="", p_ex[u_ex.size()+2],p_chars="",out="abc";
    for (p_count=0;p_count<u_ex.size();p_count++){
        p_chars=u_ex[p_count];
        if (p_chars=="("&&(sq==0&&dq==0)){
            p_con=1;
            break;
        } else if ((p_count>0&&u_ex[p_count-1]!='\\')||(p_count==0)) {
            if (p_chars=="\""&&sq==0){
                if (dq==0){
                    dq=1;
                } else {
                    dq=0;
                }
            } else if (p_chars=="\'"&&dq==0){
                if (sq==0){
                    sq=1;
                } else {
                    sq=0;
                }
            } 
        } 
    }
    dq=0;
    sq=0;
    if (p_con==1){
        u_ex="("+u_ex+")";
        for (p_count=0;p_count<u_ex.size();p_count++){
            p_chars=u_ex[p_count];
            if ((p_chars!="("&&p_chars!=")")||(dq==1||sq==1)){
                if ((p_count>0&&u_ex[p_count-1]!='\\')||(p_count==0)) {
                    if (p_chars=="\""&&sq==0){
                        if (dq==0){
                            dq=1;
                        } else {
                            dq=0;
                        }
                    } else if (p_chars=="\'"&&dq==0){
                        if (sq==0){
                            sq=1;
                        } else {
                            sq=0;
                        }
                    } 
                }
                p_store=p_store+p_chars;
            } else if (p_chars=="("){
                p_de[p_list]=p_depth;
                p_ex[p_list]=p_store;
                p_store="";
                p_list++;
                p_depth++;
                if (p_depth>highest_b){
                    highest_b=p_depth;
                }
            } else if (p_chars==")"){
                p_de[p_list]=p_depth;
                p_ex[p_list]=p_store;
                p_store="";
                p_list++;
                p_depth--;
            }
        }
        stringstream er;
        for (p_count=0;p_count<p_list;p_count++){//Calculate Highest Brackets
                if (p_de[p_count]==highest_b){
                    p_de[p_count]=highest_b-1;
                    p_ex[p_count]=evaluate(p_ex[p_count]);
                    for (p_count4=0;p_count4<p_list;p_count4++){
                        er << "" << p_de[0] << p_ex[0] ;
                    }
                }
            }
        for(;highest_b!=0;highest_b--){
            stacks=0;
            prev_b=0;
            for (p_count=0;p_count<p_list;p_count++){
                if ((p_de[p_count]==highest_b-1)&&(prev_b!=1)){
                    stacks++;
                    prev_b=1;
                } else if (p_de[p_count]!=highest_b-1){
                    prev_b=0;
                }
            }
            p_count3=0;
            for (p_count=0;p_count<stacks;p_count++){
                for (p_count3=0;p_de[p_count3]!=highest_b-1;p_count3++){
                }
                p_store="";
                sub=0;
                for (p_count2=p_count3;p_de[p_count2]==highest_b-1;p_count2++){
                    p_store=p_store+p_ex[p_count2];
                    sub++;
                }
                p_ex[p_count2-1]=evaluate(p_store);
                if (err_det!="OK"){
                    return p_ex[p_count2-1];
                }
                p_de[p_count2-1]=highest_b-2;
                sub--;
                for (p_count2=p_count3;p_count2<p_list;p_count2++){
                    p_store=p_ex[p_count2+sub];
                    p_ex[p_count2]=p_store;
                    str=p_de[p_count2+sub];
                    p_de[p_count2]=str;
                }
                p_list=p_list-sub;
            }
        }
        out=p_ex[0];
        if (err_det!="OK"){
            return p_ex[0];
        }
    } else {
        out=evaluate(u_ex);
        if (err_det!="OK"){
            return out;
        }
    }
    return out; 
}
//------------------------------------------
int Compile(string path) { 
    string var_er;
    int sl=0, ml=0, com_count, doubleq=0,singleq=0;
    string code="", ch, temp_com, com_char;
    ifstream read(path.c_str());
    while (getline(read,ch)) {
        sl=0;
        temp_com="";
        for (com_count=0;com_count<ch.size();com_count++){
            com_char=ch[com_count];
            if (ch[com_count]=='#'){
                if (ch[com_count+1]=='\''){
                    ml=1;
                } else if (ml==1&&ch[com_count-1]=='\''){
                } else {
                    sl=1;
                }
            }
            if (sl!=1&&ml!=1){
                temp_com=temp_com.append(com_char);
            }
            if (com_char=="#"&&ch[com_count-1]=='\''){
                ml=0;
            }
        }
        code=code.append(temp_com);
    }
    if (code==""){
        system("cls");
        cerr << "Cant find source file/Empty source file (\""<<path<<"\" = void)";
        return 9;
    }
    read.close();
    //-----------------------
    code_length=code.size();
    int err;//Lexer
    err=0;
    int count=0, listl=0;
    string chars[code.size()], store="";
    string character;
    for(count=0;count<code.size();count++) { //Breaking the code into tokens
        character=code.at(count);
             if (((character!=";")&&(character!=":")&&(character!="[")&&(character!="]")&&(character!="{")&&(character!="}")&&(character!="="))||(singleq==1||doubleq==1)) {
                 if (count>0&&code.at(count-1)!='\\'){
                     if (character=="\""&&singleq==0){
                        if (doubleq==0){
                            doubleq=1;
                        } else {
                            doubleq=0;
                        }
                     } else if (character=="\'"&&doubleq==0){
                        if (singleq==0){
                            singleq=1;
                        } else {
                            singleq=0;
                        }
                     }
                 }
                 store=store+character;
             } else if (character==" ") {
                 if (store!=""){
                     chars[listl]=store;
                     listl++;
                 }
                 store="";
             } else {
                 if (store!=""){
                     chars[listl]=store;
                     listl++;
                 }
                 chars[listl]=character;
                 listl++;
                 store="";
             }
    }
    chars[listl]=store;
    int count2=0, extras=0;
    //-----------------------------------
    
    for (count=0;count<=listl;count++){ //Counting voids
        if (chars[count]==""){
            extras++;
        }
    }
    
    for (count=0;count<=listl;count++){ //Expulsing voids
        if (chars[count]==""){
            for (count2=count;count2<=listl;count2++){
                 store=chars[count2+1];
                chars[count2]=store;
            }
        } 
    }
   
    listl=listl-extras+1;
   
    //-----------------------------------
    int line=1, line_start=0,structure=0; //Structured Compiling
    string command;
    while (line_start<listl){
        chars[line_start]=clearall(chars[line_start]);
        chars[line_start+1]=clearall(chars[line_start+1]);
        if (chars[line_start+1]==":"){
            structure=1;//Library Method
            chars[line_start+2]=clearall(chars[line_start+2]);
            chars[line_start+3]=clearall(chars[line_start+3]);
            chars[line_start+5]=clearall(chars[line_start+5]);
        } else if (chars[line_start+1]=="="){
            structure = 2;//Variable initialization
        } else if (chars[line_start+1]=="["){
            structure= 3;//Loop, if, etc
            chars[line_start+3]=clearall(chars[line_start+3]);
        } else {
            system("cls");
            cerr << "Unidentified statement structure at line "<< line;
            cout << chars[1+line_start];
            return 3;
        }
        //-----------------------------------
        switch (structure){
            case (1):
                if (chars[0+line_start]=="Console"){
                    command = "Console";
                } else if (chars[0+line_start]=="Kode"){
                    command="Kode";
                } else if(chars[0+line_start]=="New"){
                    command="New";
                } else {
                    system("cls");
                    cerr << "Illegal start to a statement >> line " << line;
                    return 1;
                    break;
                }
                if (command=="Console"){
                    if (chars[2+line_start]=="clear"){
                        if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==";"){
                            system("cls");
                            line_start=line_start+6;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }

                    } else if (chars[2+line_start]=="nextLine"){
                        if (chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                            chars[4+line_start]=UES(chars[4+line_start]);
                            stringstream s(chars[4+line_start]);
                            s >> count2;
                            for (count=0;count<count2;count++){
                                cout << endl;
                            }
                            line_start=line_start+7;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }

                    } else if (chars[2+line_start]=="out") {
                        if (chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                            store=UES(chars[4+line_start]);
                            cout << store;
                            line_start=line_start+7;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2; 
                        }
                    } else {
                        system("cls");
                        cerr << "Unexpected token >> " << chars[2+line_start] <<" at line >> " << line;
                        return 2;
                    }
                } else if (command=="Kode"){
                    if (chars[2+line_start]=="halt"){
                        if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==";"){
                            return 0;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }
                    } else if (chars[2+line_start]=="in"){
                        if (chars[3+line_start]=="["&&chars[4+line_start]=="]"&&chars[5+line_start]==":"&&chars[7+line_start]==";"){
                            cin >> store;
                            chars[6+line_start]=clearall(chars[6+line_start]);
                            character=set_var(chars[6+line_start],store);
                            if (character!="OK"){
                                system("cls");
                                cout << character;
                                return 7;
                            }
                            line_start=line_start+8;
                        } else {
                            system("cls");
                            cout << "Missing token at line >> " << line;
                            return 2;
                        }
                    } else if (chars[2+line_start]=="delay"){
                        if (chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                            store=UES(chars[4+line_start]);
                            stringstream d(store);
                            d >> count2;
                            Sleep(count2);
                            line_start=line_start+7;
                        } else {
                            system("cls");
                        cout << "Missing token at line >> " << line;
                        return 2;
                        }
                    } else {
                        system("cls");
                        cout << "Unexpected token at line >> " << line;
                        return 2;
                    }
                } else if (command=="New"){
                    if (chars[1+line_start]==":"&&chars[3+line_start]=="["&&chars[5+line_start]=="]"&&chars[6+line_start]==";"){
                        if (chars[2+line_start]=="var"){
                            store="";
                            temp_com=chars[4+line_start];
                            for (count=0;count<temp_com.size();count++){
                                character=temp_com[count];
                                if (character==","){
                                    var_er=declare(0,store,"0");
                                    if (var_er!="OK"){
                                        system("cls");
                                        cout << var_er;
                                        return 6;
                                    }
                                    store="";
                                } else {
                                    store=store+character;
                                }
                            }
                            var_er=declare(0,store,"0");
                            if (var_er!="OK"){
                                system("cls");
                                cout << var_er;
                                return 6;
                            }
                            line_start=line_start+7;
                        } else {
                            system("cls");
                            cerr << "Unexpected token >> " << chars[2+line_start] <<" at line >> " << line;
                            return 2;
                        }
                    } else {
                        system("cls");
                        cerr << "Unexpected token >> " << chars[2+line_start] <<" at line >> " << line;
                        return 2;
                    }
                }
                break;
            case (2):
                chars[line_start]= clearall(chars[line_start]);
                var_er=var_exists(chars[line_start]);
                    if (chars[3+line_start]==";"){
                        store=UES(chars[2+line_start]);
                        var_er=set_var(chars[line_start],store);
                        if (var_er!="OK"){
                            system("cls");
                            cerr << var_er;
                            return 7;
                        }
                        line_start=line_start+4;
                    } else {
                        system("cls");
                        cout << "Missing token \";\" at line >> " << line;
                        return 2;
                    }
                break;
            case (3):
                system("cls");
                cerr << "Loop statements are not included in " << version;
                return 5;
                break;
        }
        line++;
        if (err_det!="OK"){
            system("cls");
            cout << err_det;
            err_det="OK";
            return 10;
        }
    }
    //-----------------------------------
    return 0;
}
int main(){
    header();
    cout << "Compile:File:atPath>";
    string file_path;
    int com_ret;
    cin >> file_path;
    com_ret=Compile(file_path);
    cout << "\n\n";
    return com_ret;
}
