#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
int ID;

// Tipo de dado customizado 'todo' com dois campos: id e task
struct todo {
    int id;
    string task;
};

// Este método é usado para adicionar uma nova tarefa à lista de tarefas
void addtodo() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       REGISTRADOR DE TAREFAS                          " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    todo todo;
    cout << "\n\tNova tarefa: ";
    cin.get();
    getline(cin, todo.task); // Obtém a entrada do usuário
    ID++; // Incrementa o id para a tarefa atual

    // Escreve esta tarefa no arquivo 'todo.txt'
    ofstream write;
    write.open("todo.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << todo.task;
    write.close();

    // Escreve o ID em um novo arquivo para uso posterior na adição de novas tarefas
    write.open("id.txt");
    write << ID;
    write.close();

    char ch;
    cout << "Deseja adicionar mais uma tarefa? y/n" << endl;
    cin >> ch;

    // Se o usuário deseja adicionar uma nova tarefa, chama a mesma função novamente, senão, retorna
    if (ch == 'y') {
        addtodo();
    }
    else {
        cout << "\n\tTarefa foi adicionada com sucesso";
        return;
    }
}

// Este método é usado para imprimir a tarefa na tela
void print(todo s) {
    cout << "\n\tID: " << s.id;
    cout << "\n\tTarefa: " << s.task;
}

// Este método é usado para ler dados do arquivo 'todo.txt' e imprimi-los na tela
void readData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       REGISTRADOR DE TAREFAS                          " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    todo todo;
    ifstream read;
    read.open("todo.txt");
    cout << "\n\t------------------Suas tarefas atuais na lista--------------------";
    // Enquanto não alcançarmos o final do arquivo, continue imprimindo os dados na tela
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }
    read.close();
}

// Este método é usado para buscar uma tarefa específica no arquivo 'todo.txt'
int searchData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       REGISTRADOR DE TAREFAS                          " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id;
    cout << "\n\tDigite o ID da tarefa: ";
    cin >> id;
    todo todo;
    ifstream read;
    read.open("todo.txt");
    // Enquanto não alcançarmos o final do arquivo, continue buscando pelo ID que corresponde ao ID inserido pelo usuário
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id) {
            print(todo);
            return id;
        }
    }
}

// Este método é usado para deletar a tarefa do arquivo 'todo.txt'
void deleteData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       REGISTRADOR DE TAREFAS                          " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id = searchData();
    cout << "\n\tDeseja deletar esta tarefa? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        // Enquanto não alcançarmos o final do arquivo, continue buscando pelo ID para deletar a tarefa
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tTarefa deletada com sucesso";
    }
    else {
        cout << "\n\tRegistro não deletado";
    }
}

// Este método é usado para atualizar a tarefa
// Aqui criamos um novo arquivo 'temp.txt' e adicionamos todos os dados atualizados a este arquivo
// Depois de atualizar, deletamos o arquivo 'todo.txt' original e renomeamos este arquivo para 'todo.txt'
void updateData() {
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       REGISTRADOR DE TAREFAS                          " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id = searchData();
    cout << "\n\tDeseja atualizar esta tarefa? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        todo newData;
        cout << "\n\tDigite a nova tarefa: ";
        cin.get();
        getline(cin, newData.task);
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        // Enquanto não alcançarmos o final do arquivo, continue buscando pelo ID e, ao encontrar, atualize com os novos dados
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
            else {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << newData.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tTarefa atualizada com sucesso";
    }
    else {
        cout << "\n\tRegistro não deletado";
    }
}

int main()
{
    system("cls");
    system("Color E0"); // "Color XY", X - backgroung color, Y - text color
    system("title todoapp @copyassignment");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t*                       REGISTRADOR DE TAREFAS                        *" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl << endl;
    ifstream read;
    read.open("id.txt");
    if (!read.fail()) {
        read >> ID;
    }
    else {
        ID = 0;
    }
    read.close();

    while (true) {
        cout << endl << endl;
        cout << "\n\t1. Adicionar tarefa";
        cout << "\n\t2. Ver tarefas";
        cout << "\n\t3. Procurar tarefa";
        cout << "\n\t4. Deletar tarefa";
        cout << "\n\t5. Atualizar tarefa";

        int choice;
        cout << "\n\tDigite a opção: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addtodo();
            break;
        case 2:
            readData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            updateData();
            break;
        }
    }
}
