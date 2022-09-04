#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<algorithm>
#include<dirent.h>            
#include<sys/stat.h>            
#include<termios.h>
#include<vector>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>             
#include<pwd.h>               
#include<grp.h>                 
#include<sys/ioctl.h>          
using namespace std;

#define MAX 15
#define escape_char 27             
#define clr cout<<"\33c"
#define set_pos(x,y) printf("%c[%d;%dH",escape_char,x,y)
#define clear_from cout<<"\e[0J"
#define clear_line cout<<"\33[K\r"
void listfiles(const char*, int);
void command_mode(const char*, vector<char*>, int);
stack<string> st_front, st_back;
vector<string> command_vector;            
string usid;
string home_dir;
string curr_directory;
string cur_direc;
char paths[4100];
char ch1[4100];
char ch[4100];
int last_index=MAX;
int first_index=0;
int check_search;
int commandMode;
int pos=1;
int settt=16;
int row;
int aa;

string char_to_string(const char *st1)
{
    string ans="";
    for(int i=0; i<10000;i++){
        if(st1[i]!=0)
            ans.push_back(st1[i]);
        else 
            break;
    }
    return ans;
}
vector<string> split(string st, string slash)
{
    string str;          
    size_t loc=0;
    vector<string> res;
    while ((loc = st.find(slash)) != string::npos) {
        str = st.substr(0, loc);
        res.push_back(str);
        st.erase(0, loc + slash.length());
    }
    res.push_back(st);
    return res;
}

//------------------------------- Command Mode Functionalities ----------------------------\]

string absolute_path(string path)
{
    string pwd = cur_direc;
    string abs_path = "";
    if(path[0] == '~')
        abs_path = string(home_dir) + path.substr(1, path.length()-1);
    
    else if(path[0] == '.' && path[1] == '/')
        abs_path = pwd + "/" + path.substr(2, path.length()-2);
    
    else if(path[0] == '/')
        abs_path = path;

    else
        abs_path = pwd + "/" + path;

    return abs_path;
}
int check_dir(string path)
{
    struct stat str;
    if(stat(path.c_str(), &str) != 0) 
        return 0;
    if (S_ISDIR(str.st_mode))
        return 1;
    else
        return 0;
}
mode_t check_mode(string path)
{
    struct stat str;
    stat(path.c_str(), &str);
    mode_t mode=0;

    mode = mode | ((str.st_mode & S_IRGRP)?0040:0);
    mode = mode | ((str.st_mode & S_IWGRP)?0020:0);
    mode = mode | ((str.st_mode & S_IXGRP)?0010:0);       
    mode = mode | ((str.st_mode & S_IROTH)?0004:0);
    mode = mode | ((str.st_mode & S_IWOTH)?0002:0);
    mode = mode | ((str.st_mode & S_IXOTH)?0001:0);
    mode = mode | ((str.st_mode & S_IRUSR)?0400:0);
    mode = mode | ((str.st_mode & S_IWUSR)?0200:0);
    mode = mode | ((str.st_mode & S_IXUSR)?0100:0);

    return mode;
}

void fcopy(string source, string dest)
{
    mode_t mode = check_mode(source);
    int src_open = open(source.c_str(), O_RDONLY);
    int des_open = open(dest.c_str(), O_CREAT|O_WRONLY, mode);
    char c;
    if(src_open == -1){
        set_pos(MAX+5,settt);
            cout<<"Error in Opening Source File";
        set_pos(MAX+4,settt);
        return;
    }
    if(des_open == -1){
        set_pos(MAX+5,settt);
            cout<<"File Already Exist";
        set_pos(MAX+4,settt);
        return;
    }
    while(read(src_open, &c, 1))
        write(des_open, &c, 1);

    close(src_open);
    close(des_open);
    return;
}
void copy_directory(string source, string dest)
{
    DIR *path = opendir(source.c_str());
    struct dirent *entity;
    entity = readdir(path);
    if(path == NULL)
    {
        set_pos(MAX+5,settt);
            cout<<"Error in opening Directory";
        set_pos(MAX+4,settt);
        exit(1);
    }
    while(entity != NULL)
    {
        if(entity->d_name == "."  || entity->d_name == "..")
            continue;
        else{
            string dname = entity->d_name;
            string sr = source + "/" + dname;
            string dr = dest + "/" + dname;
            if(!check_dir(sr))
                fcopy(sr,dr);
            else{
                mode_t mode = check_mode(sr);
                int make_dir = mkdir(dr.c_str(), mode);
                if(make_dir == -1)
                {
                    set_pos(MAX+5,settt);
                        cout<<"Couldn't Create Directory";
                    set_pos(MAX+4,settt);
                    return;
                }
                else
                    copy_directory(sr,dr);
            }
        }
    }
    return;
}
void copy_file(vector<string> str)
{
    if(str.size() <= 2){
        set_pos(MAX+5,settt);
            cout<<"Copy Command is not valid";
        set_pos(MAX+4,settt);
        return;
    }
    else
    {
        string dest = absolute_path(str[str.size()-1]);
        int i;
        if(!(check_dir(dest)))
        {
            set_pos(MAX+5,settt);
                cout<<"Destination type is not a directory";
            set_pos(MAX+4,settt);
            return;
        }
        else{
            for(i=1; i<str.size()-1; i++)
            {
                string source = absolute_path(str[i]);
                vector<string> source_files = split(str[i], "/");
                string destination = dest + "/" + source_files[source_files.size()-1];   
                if(check_dir(source))
                {
                    mode_t mode = check_mode(source);
                    int make_dir = mkdir(destination.c_str(), mode);
                    if(make_dir == -1)
                    {
                        set_pos(MAX+5,settt);
                            cout<<"Can't Create Directory";
                        set_pos(MAX+4,settt);
                        return;
                    }
                    copy_directory(source, destination);
                }
                fcopy(source, destination);
            }
        }
    }
    return;
}

void search_file(string cd, vector<string> str)
{
    if(str.size() != 2){
        set_pos(MAX+5,settt);
            cout<<"search command is not valid";
        set_pos(MAX+4,settt);
    }
    else
    {
        DIR *path = opendir(cd.c_str());
        struct dirent *entity;
        struct stat fileinfo;
        entity = readdir(path);
        string srch_file = cd + "/" + (str[1]);
        string check_file = cd;

        if(path == NULL){
            set_pos(MAX+5,settt);
                cout<<"Path can't be null";
            set_pos(MAX+4,settt);
            return;
        }
        else{
            while(entity != NULL){
                stat(entity->d_name, &fileinfo);
                if(str[1] == "."  || str[1] == "..")
                    continue;
                else
                {
                    string dname = entity->d_name;
                    check_file += "/";
                    check_file += dname;
                    if(srch_file == check_file)
                    {
                        check_search = 1;
                        return;
                    }
                    if(check_dir(check_file))
                        search_file(check_file ,str);
                    
                    entity = readdir(path);
                }
            }
        }
        closedir(path);
    }
    check_search = 0;
    return;
}
void create_file(vector<string> str)
{
    if(str.size() != 3){
        set_pos(MAX+5,settt);
            cout<< "Create File command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        string file_name_src = str[1];
        string dest = absolute_path(str[2]);
        dest += "/";
        dest += file_name_src;
        int crt_fil = creat(dest.c_str(), 0600);
        if(crt_fil==-1){
            set_pos(MAX+5,settt);
                cout<<"Couldn't create file";
            set_pos(MAX+4,settt);
        }
    }
}
void create_directory(vector<string> str)
{
    if(str.size() != 3){
        set_pos(MAX+5,settt);
            cout<< "Copy Directory command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        string folder_name_src = str[1];
        string dest = absolute_path(str[2]);
        dest += "/";
        dest += folder_name_src;
        int crt_dir = mkdir(dest.c_str(), 0755);
        if(crt_dir==-1){
            set_pos(MAX+5,settt);
                cout<<"Couldn't create folder";
            set_pos(MAX+4,settt);
        }
    }
}
void rename_file(vector<string> str)
{
    if(str.size() != 3){
        set_pos(MAX+5,settt);
            cout<<"rename command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        char a[4100];
        char b[4100];
        string old_path = str[1];
        string new_path = str[2];
        realpath(old_path.c_str(), a);
        realpath(new_path.c_str(), b);
        int check_rename = rename(a,b);
        if(check_rename == -1){
            set_pos(MAX+5,settt);
                cout<<"Couldn't rename the file/ directory";
            set_pos(MAX+4,settt);
        }      
    }
    return;
}
void move_file(vector<string> str)
{
    if(str.size() < 3){
        set_pos(MAX+5,settt);
            cout<<"move command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        char a[4100];
        vector<string> move_files;
        string dest_dir = str[str.size()-1];
        string dst = absolute_path(dest_dir);
        string correct = dst;
        for(int i=1; i<str.size()-1; i++)
            move_files.push_back(str[i]);
        
        for(int i=0; i<move_files.size(); i++)
        {
            realpath(move_files[i].c_str(), a);
            dst += "/";
            dst += move_files[i];
            int check_rename = rename(a, dst.c_str());
            dst = correct;
            if(check_rename == -1){
                set_pos(MAX+5,settt);
                    cout<<"Couldn't move the file/ directory";
                set_pos(MAX+4,settt);
                break;
            }
        }
    }
}
void go_to(vector<string> str, int size)
{
    if(str.size() != 2){
        set_pos(MAX+5,settt);
            cout<<"goto command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        string abs_path = absolute_path(str[1]);
        if(!check_dir(abs_path)){
            set_pos(MAX+5,settt);
                cout<<"Wrong Input";
            set_pos(MAX+4,settt);
            return;
        }
        clr;
        listfiles(abs_path.c_str(), size);
    }
    return;
}
void delete_file(vector<string> str)
{
    if(str.size() != 2){
        set_pos(MAX+5,settt);
            cout<<"delete command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        if(str[1] == "." || str[1] == "..")
        {}
        else{
            string del_file = absolute_path(str[1]);
            int rf = remove(del_file.c_str());
            if(rf == -1){
                set_pos(MAX+5,settt);
                    cout<<"Couldn't Delete file";
                set_pos(MAX+4,settt);
            }
        }
    }
    return;
}
void ddir(string str)
{
    DIR *path = opendir(str.c_str());
    struct dirent *entity;
    entity = readdir(path);
    if(path == NULL){
        cout<<"ERROR";
        return;
    }
    else{
        while(entity != NULL)
        {
            string dname = entity->d_name;
            string del_fol = str + "/" + dname;
            if(dname == "." || dname == "..")
                continue;
            else{
                if(!check_dir(del_fol))
                {
                    int rf = remove(del_fol.c_str());
                    if(rf == -1){
                        set_pos(MAX+5,settt);
                            cout<<"Couldn't Delete file "<<str;
                        set_pos(MAX+4,settt);
                        return;
                    }
                }
                else{
                    ddir(del_fol);
                    int rd = rmdir(del_fol.c_str());
                    if(rd == -1){
                        set_pos(MAX+5,settt);
                            cout<<"Can't delete this folder";
                        set_pos(MAX+4,settt);
                    }
                }
            }
        }
    }
    return;
}
void delete_directory(vector<string> str)
{
    if(str.size()!= 2){
        set_pos(MAX+5,settt);
            cout<<"delete command is not valid";
        set_pos(MAX+4,settt);
    }
    else{
        if(str[1] == "." || str[1] == ".."){
            set_pos(MAX+5,settt);
                cout<<"Please don't try to access current directory or previous directory";
            set_pos(MAX+4,settt);
        }
        else{
            string del_dir = absolute_path(str[1]);
            if(check_dir(del_dir))
            {
                ddir(del_dir);
                int rd = rmdir(del_dir.c_str());
                if(rd == -1){
                    set_pos(MAX+5,settt);
                        cout<<"Couldn't delete directory";
                    set_pos(MAX+4,settt);
                }
            }
        }
    }
    return;
}

//--------------------------------- Enable Non-Canonical Mode ------------------------------\]

struct termios original;
void die(const char *s) 
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(s);
            // perror() looks at the global errno variable and prints a descriptive error message for it. It also prints the string given to it before it prints the error message, which is meant to provide context about what part of your code caused the error.
    exit(1);
            // After printing out the error message, we exit the program with an exit status of 1, which indicates failure (as would any non-zero value).
}
void disable_non_canonical_mode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}
void enable_non_canonical_mode()
{
    tcgetattr(STDIN_FILENO, &original);
            // Terminal attributes can be read into a termios struct by tcgetattr()
    atexit(disable_non_canonical_mode);
    struct termios raw = original;
    raw.c_lflag &= ~( ECHO | ICANON );
            // ICANON flag allows us to turn off canonical mode.
            // This means we will finally be reading input byte-by-byte, instead of line-by-line.
            // ICANON flag is the local flag in the c_lflag field
    if ( tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) )
        die("tcsetattr");
}

//--------------------------------------- Normal Mode ----------------------------------------\]

void displayParent_dir(const char* st1, string list, int size)
{
    string current_dir="";
    string path_name = char_to_string(st1);
    path_name += "/";
    path_name += list;
    vector<string> path ;
    path = split(path_name,"/");

    if(path.size() == 0)
        current_dir = "";
    else if(path.size() == 2)
        current_dir = char_to_string(ch);
    else
        current_dir = path[0];
    
    for(int i=1;i<path.size()-2;i++)
        current_dir += "/" + path[i];
    
    listfiles(current_dir.c_str(),size);  
}
void normal_mode(const char* st1, vector<char*> v, int size)
{
    int n = v.size();
    int i, k=-1;
    int a = min(MAX,n);
    aa = a;
    struct stat inode;
    set_pos(MAX+3,0);
    cout<<"Currently in Normal Mode  ";
    set_pos(MAX+4,0);
    clear_line;
    set_pos(MAX+5,0);
    clear_line;
    set_pos(pos,0);
                  
    home_dir = "/home/" + usid;

    while(true)
    {
        int c = 0;
        c = cin.get();
        if(c == 65)             // Upper Key
        {           
            if(pos > 1)
            {
                pos--;
                set_pos(pos,0);
                listfiles(st1, n);
            }
            else if(pos == 1 && first_index > 0)
            {
                first_index--;
                last_index--;
                listfiles(st1, n);
                if(pos == 0)
                    pos = 1;
                set_pos(pos,0);
            }
        }
        else if(c == 66)        // Lower Key
        {
            if(pos<MAX && pos < v.size() )
            {
                pos++;
                set_pos(pos,0);
            }
            else if(last_index < v.size())
            {
                first_index++;
                last_index++;
                listfiles(st1, n);
            }
            else{
                int len = v.size();
                int a = min(MAX,len);
                set_pos(a,0);
            }
        }
        else if(c == 67)        // Right Key
        {
            if(!st_front.empty())
            {
                string str=st_front.top();
                st_front.pop();
                st_back.push(cur_direc);
                listfiles(str.c_str(),size);
            }
        }
        else if(c == 68)        // Left Key
        {        
            if(!st_back.empty())
            {
                string s=st_back.top();
                st_back.pop();
                st_front.push(cur_direc);
                listfiles(s.c_str(), size);
            }
        }
        else if(c == 10)        // Enter Key
        {
            pos+=(k>0)?k:0;
            if(pos > 1)
            {
                stat((v[first_index + pos-1]),&inode);
                if(S_ISDIR(inode.st_mode))
                {
                    string filePath="";

                    if(cur_direc == "/")
                        filePath = cur_direc;
                    else
                        filePath = cur_direc + '/' + char_to_string(v[first_index + pos-1]);
                    
                    stat(filePath.c_str(),&inode);

                    string pwd = cur_direc;
                    st_back.push(pwd);
                    while(!st_front.empty())
                        st_front.pop();

                    if(pos==2){
                        pos = 1;
                        displayParent_dir(st1, v[pos], size);   
                    } 
                    else{
                        pos = 1;
                        listfiles(filePath.c_str(), size);
                    }
                }
                else 
                {
                    string filePath;

                    if(cur_direc == "/")
                        filePath = cur_direc;
                    else
                        filePath = cur_direc + '/' + char_to_string(v[first_index + pos-1]);
                    
                    stat(filePath.c_str(),&inode);

                    string pwd = cur_direc;
                    st_back.push(pwd);

                    if(S_ISDIR(inode.st_mode))
                    {
                        if(pos==2){
                            pos = 1;
                            displayParent_dir(st1, v[pos], size);    
                        }
                        else{
                            pos = 1;
                            listfiles(filePath.c_str(), size);  
                        }
                    }
                    else {
                        if (fork() == 0) {
                            execl("/usr/bin/xdg-open", "xdg-open", filePath.c_str(), (char *)0);
                            exit(1);
	                    }
                    }
                }
            }
        }
        else if(c == 127)       // Backspace Key
        {
            while(!st_front.empty())
                st_front.pop();
            if(cur_direc == "/")
                continue;
            st_back.push(cur_direc);
            displayParent_dir(st1, v[1], size);
        }
        else if(c == 113)       // q button
        {        
            clr;
            exit(1);
        }
        else if(c == 104)       // h button
        {
            while(!st_front.empty())
                st_front.pop();
            st_back.push(cur_direc);
            listfiles(home_dir.c_str(),size); 
        }
        else if(c == 58)        // Colon {:}
        {
            command_mode(st1, v, size);
        }
    }
}

//--------------------------------------- Command Mode ---------------------------------------\]

void function_call(string call, int n)
{
    if(call == "goto")
        go_to(command_vector, n);
    
    else if(call == "rename")
        rename_file(command_vector);
    
    else if(call == "move")
        move_file(command_vector);

    else if(call == "create_file")
        create_file(command_vector);
    
    else if(call == "create_dir")
        create_directory(command_vector);

    else if(call == "search"){
        check_search = 0;
        search_file(cur_direc, command_vector);
        if(check_search == 1)
        {
            set_pos(MAX+5, settt);
                cout<<"True";
            set_pos(MAX+4, settt);
        }
        else
        {
            set_pos(MAX+5, settt);
                cout<<"False";
            set_pos(MAX+4, settt);
        }
    }
    
    else if(call == "copy")
        copy_file(command_vector);

    else if(call == "delete_file")
        delete_file(command_vector);

    else if(call == "delete_dir")
        delete_directory(command_vector);

}
string getcommand(string str, int n)
{
    char c='m';
    string command="";
    int z=16;
    set_pos(MAX+4,z);
    while(true)
    {
        c=cin.get();
        if(c == 27)             // Escape Character
            return "esc";
        else if(c == 10)        // Enter
        {
            if(command == "quit")
            {
                clr;
                exit(1);
            }
            else{
                set_pos(MAX+4,16);
                cout<<"\x1b[0K";
                return command;
            }
        }
        else if(c == 127)       // Backspace
        {
            if(z<17)
                continue;
            else
            {
                z--;
                set_pos(MAX+4,z);
                cout<<"\x1b[0K";
                command.pop_back();
            }
            
        }
        else
        {
            set_pos(MAX+5,z);
            clear_line;
            set_pos(MAX+4,z);
            command.push_back(c);
            cout<<c;
            z++;
            set_pos(MAX+4, z);
        }
    }
    return "asddfg";
}
void command_mode(const char* st1, vector<char*> v, int size)
{
    commandMode = 1;
    int n=(size<v.size())?size+1:v.size()+1;
    int y=0, z=16, i;
    set_pos(MAX+3,0);
        cout<<"Currently in Command Mode";
    set_pos(MAX+4,0);
        cout<<"Enter Command:     ";
    set_pos(MAX+5,0);
        clear_line;
    set_pos(MAX+4,z);
    char a,b;
    string command="";
    vector<string> p;
    while(true)
    {
        command_vector.clear();
        command = getcommand(command, n);

        if(command == "esc")
        {
            commandMode = 0;
            normal_mode(st1, v, size);
        }
        string x="";
        for(i=0;i<command.size();i++)
        {
            if(command[i] != 32)
                x += command[i];
            
            else{
                command_vector.push_back(x);
                x="";
            }
        }
        command_vector.push_back(x);

        string call = command_vector[0];
        
        function_call(call, n);       
    }
    return;
}

//-------------------------------- Used for printing each row --------------------------------\]

bool strcmpr(char* c1, char* c2)
{
    return (strcmp(c1,c2)<0);
}
void printdata(const char *st1, const char *st2)    
{
    string path = char_to_string(st2);
    path += "/";
    path += char_to_string(st1);
    const char* paths = new char[4100];
    paths = path.c_str();
    struct stat str1;
    stat(paths, &str1);

    double size=str1.st_size;
    char unit='B';
    if(size>100)
    {
        size/=1024;
        unit='K';
    }
    if(size>100)
    {
        size/=1024;
        unit='M';
    }
    if(size>100)
    {
        size/=1024;
        unit='G';
    }
    
    string pw="";
    pw+=((S_ISDIR(str1.st_mode))  ? "d" : "-");
    pw+=((str1.st_mode & S_IRUSR) ? "r" : "-");           // S_IRUSR = ..00100000000 nad its logical And with 
    pw+=((str1.st_mode & S_IWUSR) ? "w" : "-");           // st_mode = 100000111111101 gives us the answer 
    pw+=((str1.st_mode & S_IXUSR) ? "x" : "-");           // for the required place.
    pw+=((str1.st_mode & S_IRGRP) ? "r" : "-");
    pw+=((str1.st_mode & S_IWGRP) ? "w" : "-");
    pw+=((str1.st_mode & S_IXGRP) ? "x" : "-");
    pw+=((str1.st_mode & S_IROTH) ? "r" : "-");
    pw+=((str1.st_mode & S_IWOTH) ? "w" : "-");
    pw+=((str1.st_mode & S_IXOTH) ? "x" : "-");

    usid = getpwuid(str1.st_uid)->pw_name;
    string time = ctime(&str1.st_mtime);
    string trimtime = time.substr(4, time.size()-10);             // This is done to remove Day in start
                                                                  //  and year and "\n" in the end
    cout<<"  ";
    
    cout<<pw<<"\t";    
    cout<<setprecision(2)<<size<<unit<<"\t";
    cout<<getpwuid(str1.st_uid)->pw_name<<"\t";
    cout<<getgrgid(str1.st_gid)->gr_name<<"\t";
    cout<< trimtime <<"\t  ";                                
    cout<<st1;
    cout<<"\n";
    
    return;
}

//------------------------ Used for listing down the files and directories -------------------\]

void listfiles(const char *dir, int size)
{
    if(char_to_string(dir) == "") 
    {
        string slash = "/";
        dir = slash.c_str();
        cur_direc = "/";
    }
    DIR* path = opendir(dir);
    vector<char*> pt;               
    struct dirent *entity;            
    entity = readdir(path);
    int i;

    if(path == NULL ){
        cout<<"Error in fecthing files"<<"\n";
        exit(1);
    }

    chdir(dir);
    getcwd(ch1, sizeof(ch1));
    cur_direc=char_to_string(ch1);

    while(entity != NULL)             
    {
        pt.push_back(entity->d_name);
        entity = readdir(path);
    }

    sort(pt.begin(), pt.end(), strcmpr);
    closedir(path);

    int n = pt.size();

    // Clear the screen before printing the content
    clr;

    for(i=first_index;i<last_index && i<pt.size();i++)
        printdata(pt[i], dir);
    
    if(commandMode == 1)
        command_mode(dir, pt, n);
    else
        normal_mode(dir, pt, n);

    return;
}

//--------------------------------------- Main Function --------------------------------------\]

int main(int argc, char* argv[])
{
    struct winsize ro;

    getcwd(ch, sizeof(ch));
    cur_direc=ch;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ro);
    row = ro.ws_row;
            // ioctl (input/output control) is a system call for device-specific input/output operations and other operations which cannot be expressed by regular system calls.
            // TIOCGWINSZ, "T"ermios "IOC"tl to "G"et the "WIN"dow "S"i"Z"e.
    enable_non_canonical_mode();
    listfiles(ch, row-4);
    return 0;
}

