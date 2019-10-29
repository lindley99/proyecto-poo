#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const string fichero = "../laberintos/laber1.txt";
const int MAX = 100;

int main() {
    int ** matrix;  //doble puntero para memoria dinamica
    int n, m;
    ifstream fi;
    fi.open(fichero);
    if(fi.is_open()){
        fi>>n>>m;   //fila y columna dimensiones

        /***creacion de matrix**/
        matrix = new int*[n]; //n filas
        for(int i = 0; i < n; i++){
            matrix[i] = new int[m];   //m columnas
            for(int j = 0; j < m; j++) {
                matrix[i][j] = MAX;  //cada celda va tener un valor de MAX
            }
        }
        int obstaculos;
        fi>>obstaculos;  //2 linea del txt
        int fil,col;
        while(obstaculos--){
            fi>>fil>>col;     //leyendo las coordenadas
            matrix[fil][col]=-1;
        }
        fi.close();
    }
    else cerr<<"Error de lectura\n";

    matrix[0][0] = 0; //punto inicial

    priority_queue<pair<int,pair<int,int>>> cola;

    cola.push(make_pair(0,make_pair(0,0)));

    while(!cola.empty()){
        int dist = cola.top().first;
        pair<int,int> coord = cola.top().second;
        cola.pop(); //elimino de la cola
        int fil = coord.first;
        int col = coord.second;
        if(fil-1 >= 0) {  //verificar si no estoy en la primera fila
            if(matrix[fil-1][col] != -1){ //verificar si no es obstaculo
                if(dist+1 < matrix[fil-1][col]){
                    matrix[fil-1][col]=dist+1;
                    cola.push(make_pair(dist+1,make_pair(fil-1,col)));
                }
            }
        }
        if(fil+1 != n) { //verificar si no estoy en la ultima fila
            if(matrix[fil+1][col] != -1){ //verificar si no es obstaculo
                if(dist+1 < matrix[fil+1][col]){
                    matrix[fil+1][col] = dist+1;
                    cola.push(make_pair(dist+1,make_pair(fil+1,col)));
                }
            }
        }
        if(col-1 >= 0) { //verificar si no estoy en la primera columna
            if(matrix[fil][col-1] != 1){ //verificar si no es obstaculo
                if(dist+1< matrix[fil][col-1]){
                    matrix[fil][col-1] = dist+1;
                    cola.push(make_pair(dist+1,make_pair(fil,col-1)));
                }
            }
        }
        if(col+1 != m) { //verificar si no estoy en la ultima columna
            if(matrix[fil][col+1] != 1){ //verificar si no es obstaculo
                if(dist+1  < matrix[fil][col+1]){
                    matrix[fil][col+1] = dist+1;
                    cola.push(make_pair(dist+1,make_pair(fil,col+1)));
                }
            }
        }
    }

    for(int i = 0; i < n ; i++) {
        for(int j = 0; j < m; j++) {
            if ( matrix[i][j] == -1) {
                cout<<"[@] ";
            } else {
                cout<<"["<<matrix[i][j]<<"]"<<" ";
            }
        }
        cout<<'\n';
    }

    return 0;
}