#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> leerArchivo(string);
void guardarArchivo(vector<string>);
int main(int argc, char *argv[]){
    string texto = "";
    vector<string> infoExtraida;
    infoExtraida =  leerArchivo(argv[1]);
    guardarArchivo(infoExtraida);
} // Fin Main

vector<string> leerArchivo(string nombre){
    vector<string> informacion;
    string linea = "";
    fstream lector(nombre);
    int numClases = 0;
    string clases = "";
    while (!lector.eof()){
        lector >> linea;
        for (int i = 0; i < linea.size(); i++){
            if (linea[i] == ':'){
                int diferencia;
                diferencia = (linea.size()) - (i + 1);
                clases += linea.substr(i + 1, diferencia) + ";";
            } else if(linea[i] == ']'){
                informacion.push_back(clases);
                clases = "";
            } // Fin If  
        } // Fin For
    } // Fin While
    char separador = ';'; 
    vector<string> separacionInfo; 
    for (int i = 0; i < informacion.size(); i++){
        for(int p = 0, q = 0; p != informacion[i].npos; p = q){
            separacionInfo.push_back(informacion[i].substr(p + (p != 0), (q = informacion[i].find(separador, p + 1)) - p - (p != 0)));
        } // Fin For   
    } // Fin For
    separacionInfo.pop_back();
    lector.close();
    return separacionInfo;
} // Fin Leer Archivo

void guardarArchivo(vector<string> informacion){
    string namecpp, nameh;
    fstream escritor;
    namecpp = informacion[0] + ".cpp";
    nameh = informacion[0] + ".h";
    escritor.open(namecpp, ios::app);
    char comilla = '"';
    string lineaInclude;
    string include = "#include ";
    lineaInclude = include + comilla + informacion[0] + ".h" + comilla;
    escritor << lineaInclude + "\n";
    escritor << "\n";
    escritor << informacion[0] + "::" + informacion[0] + "() {" + "\n";
    escritor << "}" << "\n";
    escritor <<  "\n";
    /*int num, dif;
    for (int i = 0; i < informacion.size(); i++){
        if (informacion[i] == ""){
            num = i - 1;
        }     
    }
    escritor << informacion[0] + "::" + informacion[0] + "("; 
    for (int i = 1; i < num; i++){
        if (i == dif - 1){
            string tipo, variable;
            int linea;
            for (int j = 0; j < informacion[i].size(); j++){
                if (informacion[] == '|'){
                    
                }
                
            }
            
            informacion[i]
            escritor << informacion[i] + "::" + informacion[0] + "(";             
        } else {

        }  
    }*/
     
    //escritor << informacion[0] + "::" + informacion[0] + "(";
    escritor.close();
    escritor.open(nameh, ios::app);
    string name;
    name = informacion[0];
    for (int i = 0; i < name.size(); i++) {
        name[i] = toupper(name[i]);
    } // Fin For
    escritor << "#ifndef " + name + "_H" + "\n";
    escritor << "#define " + name + "_H" + "\n";
    escritor << "#include <string>" << "\n";
    escritor << "using namespace std;" << "\n";
    escritor << "class " + informacion[0] + "{" + "\n";
    escritor << "   private:" << "\n";
    escritor << "   public:" << "\n";
    escritor << informacion[0] + "();" + "\n";
    escritor << "};" << "\n";
    escritor << "#endif" << "\n";
    escritor.close();
    int contatributos;
    for (int i = 0; i < informacion.size(); i++){
        if (informacion[i] == ""){
            namecpp = "";
            nameh = "";
            namecpp = informacion[i + 1] + ".cpp";
            nameh = informacion[i + 1] + ".h";
            escritor.open(namecpp, ios::app);
            char comilla = '"';
            string lineaInclude;
            string include = "#include ";
            lineaInclude = include + comilla + informacion[i + 1] + ".h" + comilla;
            escritor << lineaInclude + "\n";
            escritor << "\n";
            escritor << informacion[i + 1] + "::" + informacion[i + 1] + "() {" + "\n";
            escritor << "}" <<  "\n";
            escritor <<  "\n";
            escritor.close();
            escritor.open(nameh, ios::app);
            string name;
            name = informacion[i + 1];
            for (int i = 0; i < name.size(); i++) {
                name[i] = toupper(name[i]);
            } // Fin For
            escritor << "#ifndef " + name + "_H" + "\n";
            escritor << "#define " + name + "_H" + "\n";
            escritor << "#include <string>" << "\n";
            escritor << "using namespace std;" << "\n";
            escritor << "class " + informacion[i + 1] + "{" + "\n";
            escritor << "   private:" << "\n";
            escritor << "   public:" << "\n";
            escritor << informacion[i + 1] + "();" + "\n";
            escritor << "};" << "\n";
            escritor << "#endif" << "\n";
            escritor.close();
        } // Fin If
    } // Fin For
} // Fin Guardar Archivo