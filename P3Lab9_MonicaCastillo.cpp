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
    int num;
    for (int i = 0; i < informacion.size(); i++){
        if (informacion[i] == ""){
            num = i - 1;
            break;
        } // Fin If   
    } // Fin For
    escritor << informacion[0] + "::" + informacion[0] + "("; 
    for (int i = 1; i <= num; i++){
        if (i == num){
            string tipo, variable;
            int linea;
            string atributo;
            atributo = informacion[i];
            for (int j = 0; j < atributo.size(); j++){
                if (atributo[j] == '|'){
                    linea = j;
                } // Fin If            
            } // Fin For
            tipo = atributo.substr(0, linea);
            variable = atributo.substr(linea + 1, atributo.size() - linea);
            escritor << tipo + " _" + variable + "){" + "\n";             
        } else {
            string tipo, variable;
            int linea;
            string atributo;
            atributo = informacion[i];
            for (int j = 0; j < atributo.size(); j++){
                if (atributo[j] == '|'){
                    linea = j;
                } // Fin If            
            } // Fin For
            tipo = atributo.substr(0, linea);
            variable = atributo.substr(linea + 1, atributo.size() - linea);
            escritor << tipo + " _" + variable + ", ";   
        } // Fin If
    } // Fin For
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor << "    " + variable + " = _" + variable + ";" + "\n";   
    } // Fin For
    escritor << "}" << "\n";
    escritor <<  "\n";
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor << "void " + informacion[0] + "::set_" + variable + "(" + tipo + " _" + variable + "){" + "\n"; 
        escritor << "    " + variable + " = _" + variable + ";" + "\n";
        escritor << "}" << "\n";
        escritor <<  "\n";
    } // Fin For
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor << tipo + " " + informacion[0] + "::get_" + variable + "(){" + "\n"; 
        escritor << "    return " + variable + ";" + "\n";
        escritor << "}" << "\n";
        escritor <<  "\n";
    } // Fin For
    string name1;
    name1 = informacion[0];
    for (int i = 0; i < name1.size(); i++) {
        name1[i] = toupper(name1[i]);
    } // Fin For
    escritor << "string " + informacion[0] + "::toString(){" +"\n"; 
    escritor << "}" << "\n";
    escritor <<  "\n";
    escritor << informacion[0] + "::~" + informacion[0] + "() {" + "\n";
    escritor << "}" << "\n";
    escritor <<  "\n";
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
    escritor << "    private:" << "\n";
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor << "        " + tipo + " " + variable + ";" + "\n"; 
    } // Fin For
    escritor << "    public:" << "\n";
    escritor << "        " + informacion[0] + "();" + "\n";
    escritor << "        " + informacion[0] << "(";
    for (int i = 1; i <= num; i++){
        if (i == num){
            string tipo, variable;
            int linea;
            string atributo;
            atributo = informacion[i];
            for (int j = 0; j < atributo.size(); j++){
                if (atributo[j] == '|'){
                    linea = j;
                } // Fin If            
            } // Fin For
            tipo = atributo.substr(0, linea);
            variable = atributo.substr(linea + 1, atributo.size() - linea);
            escritor << tipo + ");" + "\n";  
        } else {
            string tipo, variable;
            int linea;
            string atributo;
            atributo = informacion[i];
            for (int j = 0; j < atributo.size(); j++){
                if (atributo[j] == '|'){
                    linea = j;
                } // Fin If            
            } // Fin For
            tipo = atributo.substr(0, linea);
            variable = atributo.substr(linea + 1, atributo.size() - linea);
            escritor << tipo + ", ";   
        } // Fin If
    } // Fin For
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor << "        void set_" + variable + "(" + tipo + ");" + "\n"; 
    } // Fin For
    for (int i = 1; i <= num; i++){
        string tipo, variable;
        int linea;
        string atributo;
        atributo = informacion[i];
        for (int j = 0; j < atributo.size(); j++){
            if (atributo[j] == '|'){
                linea = j;
            } // Fin If            
        } // Fin For
        tipo = atributo.substr(0, linea);
        variable = atributo.substr(linea + 1, atributo.size() - linea);
        escritor <<  "        " + tipo + " get_" + variable + "();" + "\n"; 
    } // Fin For
    escritor << "        string toString();" << "\n";   
    escritor << "        ~" + informacion[0] + "();" + "\n";
    escritor << "};" << "\n";
    escritor << "#endif" << "\n";
    escritor.close();
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
            escritor << informacion[i + 1] + "::~" + informacion[i + 1] + "() {" + "\n";
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
            escritor << "    private:" << "\n";
            escritor << "    public:" << "\n";
            escritor << "        " + informacion[i + 1] + "();" + "\n";
            escritor << "        ~" + informacion[i + 1] + "();" + "\n";
            escritor << "        string toString();" << "\n";   
            escritor << "};" << "\n";
            escritor << "#endif" << "\n";
            escritor.close();
        } // Fin If
    } // Fin For
} // Fin Guardar Archivo