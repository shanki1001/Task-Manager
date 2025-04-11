#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<iomanip>

using namespace std;

struct task{
    int id;
    string title;
    string description;
    string dueDate;
    string status;
};

vector<task> Tasks;

bool authenticate(){

    ifstream file("credentials.txt");

    if(!file.is_open()){
        cout << "Authentication file not found!!!\n";
        return false;
    }

    string storedUsername , storedPassword;
    getline(file, storedUsername ,',');
    getline(file, storedPassword);

    file.close();

    string inputUsername, inputPassword;
    cout << "Enter Username: ";
    getline(cin, inputUsername);
    cout << "Enter Password: ";
    getline(cin, inputPassword);

    return(inputUsername== storedUsername && inputPassword == storedPassword);

}

void addTask(){

    task newTask;
    newTask.id = Tasks.size()+1;
    cout << "Enter the task title:";
    getline(cin,newTask.title);
    newTask.status = "Not Completed";
    cout<<"Enter due date in (DD-MM-YYYY) format:";
    getline(cin,newTask.dueDate);
    cout<<"Enter description(optinal):";
    getline(cin,newTask.description);

    Tasks.push_back(newTask);

}
void filterTasks(){
    if(Tasks.size()==0){
        cout<<"No tasks in the List!!!\n";
        return;
    }
    string filterBy;
    cout<<"Enter By which you want to filter the List (for_e.g:- status):";
    getline(cin,filterBy);
    cout<<"\nFiltering the list by "<<filterBy<<":\n";
    for(int i=0 ; i<Tasks.size();i++){
        if(Tasks[i].status == "Not Completed"){
            cout << "Id         :"<<Tasks[i].id<<"\n";
            cout << "Title      :"<<Tasks[i].title<<"\n";
            cout << "Status     :"<<Tasks[i].status<<"\n";
            cout << "Due date   :"<<Tasks[i].dueDate<<"\n";
            if(Tasks[i].description!="")
            cout << "Description:"<<Tasks[i].description<<"\n";
            cout<<"\n";
        }
    }
    for(int i=0 ; i<Tasks.size();i++){
        if(Tasks[i].status == "Completed"){
            cout << "Id         :"<<Tasks[i].id<<"\n";
            cout << "Title      :"<<Tasks[i].title<<"\n";
            cout << "Status     :"<<Tasks[i].status<<"\n";
            cout << "Due date   :"<<Tasks[i].dueDate<<"\n";
            if(Tasks[i].description!="")
            cout << "Description:"<<Tasks[i].description<<"\n";
            cout<<"\n";
        }
    }

}
void viewTasks(){

    if(Tasks.size()==0) {
        cout<<"Tasks List is Empty!!!\n";
        return;
    }

    cout<<"         ============All the tasks============\n";
    cout << left
         << setw(5)  << "ID"
         << setw(25) << "Title"
         << setw(15) << "Status"
         << setw(15) << "Due Date"
         << "Description\n";
    cout << string(75, '-') << "\n";
    for(int i=0 ; i<Tasks.size() ;i++){
        cout<< left
            <<setw(5)<<Tasks[i].id
            <<setw(25)<<Tasks[i].title
            <<setw(15)<<Tasks[i].status
            <<setw(15)<<Tasks[i].dueDate;
            if(Tasks[i].description!="")
            cout <<Tasks[i].description<<"\n";
            else cout<<"--Nill--\n";
        cout << string(75, '-') << "\n";
    }
    cout<<"\n\n";

}
void deleteTask(){
    if(Tasks.size()==0){
        cout<<"Tasks List is Empty!!!\n";
        return;
    }
    viewTasks();
    int index;
    do{
        cout<<"Enter Id of the task you want to delete:";
        cin>>index;
        cin.ignore();
        if(index<1 || index>Tasks.size())
        cout<<"Enter a valid Id!!\n";
    }while(index<1 || index>Tasks.size());
    Tasks.erase(Tasks.begin()+index-1);
    for(int i=0 ; i<Tasks.size(); i++){
        Tasks[i].id = i+1;
    }
    cout<<"Task deleted successfully!!!!\n";
}
void loadTasks(){
    Tasks.clear();

    ifstream file("Tasks.csv");
    if(!file.is_open()){
        cout<<"Error in file opening!!!\n";
        return;
    }

    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string StringId, title, dueDate , status, description;
        task t;
        getline(ss,StringId,',');
        getline(ss,title,',');
        getline(ss,dueDate,',');
        getline(ss,status,',');
        getline(ss,description);
        t.id = stoi(StringId);
        t.title = title;
        t.dueDate = dueDate;
        t.status = status;
        t.description = description;
        Tasks.push_back(t);
    }
    file.close();
    cout<<"**Tasks loaded successfully**\n";

}

   // int id;
   // string title;
   // string description;
   // string dueDate;
   // string status;
void markComplete(){
    if(Tasks.size()==0){
        cout<<"No tasks in the list to mark complete!!!\n";
        return;
    }
    viewTasks();
    int index;
    do{
        cout<<"\nEnter the id you want to Mark:";
        cin>>index;
        cin.ignore();
        if(index<0 || index>Tasks.size()){
            cout<<"Index out of bounds!!!! Re-enter\n";
        }
    }while(index<1 || index>Tasks.size());

    Tasks[index-1].status = "Completed";
    cout<<"\n---Task Marked Successfully---\n";
}

void saveTask(){
    if(Tasks.size()==0)
        return;
    ofstream file("Tasks.csv");
    if(!file.is_open()){
        cout<<"Error in file opening!!!\n";
        return;
    }
    for(int i=0 ;i<Tasks.size() ; i++){
        file<<Tasks[i].id<<",";
        file<<Tasks[i].title<<",";
        file<<Tasks[i].dueDate<<",";
        file<<Tasks[i].status<<",";
        file<<Tasks[i].description<<"\n";
    }

    file.close();
}




int main()
{
    int chance = 1;
    while(chance<=3){
        if(!authenticate()){
            cout << "Authentication failed!!! Try left:"<<3-(chance++)<<"\n";
        }else break;
    }
    if(chance>3) return 0;

    int choice;
    loadTasks();
    do{
            cout<<"         ------Menu------\n";
            cout<<"     1.Add a task\n";
            cout<<"     2.View all tasks\n";
            cout<<"     3.Delete a task\n";
            cout<<"     4.Filter tasks\n";
            cout<<"     5.Mark complete a task\n";
            cout<<"     6.Save tasks and exit\n";
            cout<<"Enter a choice:";
            cin>>choice;
            cin.ignore();
            switch(choice){
                case 1: addTask();break;
                case 2: viewTasks();break;
                case 3: deleteTask();break;
                case 4: filterTasks();break;
                case 5: markComplete();break;
                case 6: saveTask();break;
            }

    }while(choice!=6);

    return 0;
}
