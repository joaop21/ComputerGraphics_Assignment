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

Figure loadFigure(Figure fig,string current_file){

    Figure nf = fig;
	ifstream file;
	file.open("../Generated_Models/" + current_file);

	file >> nf.num_triangles;
	while (!file.eof()) {
		Point new_point;
		file >> new_point.x >> new_point.y >> new_point.z;
		nf.points.push_back(new_point);
	}
    return nf;
}

Tree parseGroup(XMLElement* father){
    Tree t;

	for (XMLElement* child = father->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		const char* option = child->Value();

        switch(str2int(option)){
            case str2int("translate"):
                    t.head_figure.translation.empty = false;
            		t.head_figure.translation.x = child->FloatAttribute("X");
            		t.head_figure.translation.y = child->FloatAttribute("Y");
            		t.head_figure.translation.z = child->FloatAttribute("Z");
                    break;
            case str2int("rotate"):
                    t.head_figure.rotation.empty = false;
            		t.head_figure.rotation.angle = child->FloatAttribute("angle");
            		t.head_figure.rotation.x = child->FloatAttribute("axisX");
            		t.head_figure.rotation.y = child->FloatAttribute("axisY");
            		t.head_figure.rotation.z = child->FloatAttribute("axisZ");
                    break;
            case str2int("scale"):
                    t.head_figure.scale.empty = false;
					t.head_figure.scale.x = child->FloatAttribute("X");
            		t.head_figure.scale.y = child->FloatAttribute("Y");
            		t.head_figure.scale.z = child->FloatAttribute("Z");
                    break;
            case str2int("models"):
            		for(XMLElement* m_node = child->FirstChildElement("model"); m_node != NULL; m_node = m_node->NextSiblingElement()){
            			string file_name = m_node->Attribute("file");
            			t.head_figure = loadFigure(t.head_figure,file_name);
            		}
                    break;
            case str2int("group"):
                    Tree newTree = parseGroup(child);
                    t.children.push_back(newTree);
                    break;
        }
	}

	return t;
}

Tree parser_XML(){
	XMLDocument doc;
	doc.LoadFile("../Scenes/scene.xml");

    Tree tree;

	// testa se ficheiro XML abriu sem erros
	if(doc.ErrorID() != 0) {
		cout << "Erro ao abrir o ficheiro xml.\n";
		return tree;
	}

	XMLElement *pRoot = doc.FirstChildElement("scene");
	if (pRoot == nullptr) return tree; // testa se obteve a raiz da arvore xml

    XMLElement *pRootgroup = pRoot->FirstChildElement();
    if (pRootgroup == nullptr) return tree;

	tree = parseGroup(pRootgroup);

    return tree;

}
