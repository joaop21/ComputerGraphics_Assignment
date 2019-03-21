#include <iostream>
#include <fstream>
#include <stdexcept>
#include "geometry.h"
#include "parser.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;
using namespace geometry;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

Tree parseGroup(XMLElement* father){
    Tree t;

	for (XMLElement* child = father->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		const char* option = child->Value();

        switch(str2int(option)){
            case str2int("translate"):
                    break;
            case str2int("rotate"):
                    break;
            case str2int("scale"):
                    break;
            case str2int("models"):
                    break;
            case str2int("group"):
                    Tree newTree = parseGroup(child);
                    break;
        }
	}

	return t;
}

void load_generated_files(vector<Figure> figures){
	XMLDocument doc;
	doc.LoadFile("../Scenes/scene.xml");

	// testa se ficheiro XML abriu sem erros
	if(doc.ErrorID() != 0) {
		cout << "Erro ao abrir o ficheiro xml.\n";
		return;
	}

	XMLElement *pRoot = doc.FirstChildElement("scene");
	if (pRoot == nullptr) return; // testa se obteve a raiz da arvore xml


	vector<string> files; // nomes de ficheiros que contêm as figuras

	// filtra os nomes dos ficheiros
	XMLElement *file_names = pRoot->FirstChildElement("model");
	while(file_names) {
		string new_file = file_names->Attribute("file"); // retira o nome do ficheiro
		files.push_back(new_file); // coloca o nome no vetor
		file_names = file_names->NextSiblingElement("model"); // passa para o proximo filho
	}

	// filtra os pontos e figuras
	for(int i = 0 ; i < files.size() ; i++){
		string current_file = files[i];
		ifstream file;
		file.open("../Generated_Models/" + current_file);

		Figure fig;
		file >> fig.num_triangles;
		while (!file.eof()) {
			Point new_point;
			file >> new_point.x >> new_point.y >> new_point.z;
			fig.points.push_back(new_point);
		}
		figures.push_back(fig);
	}

}
