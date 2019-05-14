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

vector<pair<string,pair<int,tuple<vector<Point>,vector<Point>,vector<TexturePoint>>>>> figure_points;

Figure loadFigure(Figure fig, string current_file){

    Figure nf = fig;

    vector<pair<string,pair<int,tuple<vector<Point>,vector<Point>,vector<TexturePoint>>>>>::iterator it;
    for(it = figure_points.begin(); it != figure_points.end() ; it++)
        if(it->first == current_file){
            nf.points = get<0>(it->second.second);
            nf.normals = get<1>(it->second.second);
            nf.num_triangles = it->second.first;
            nf.name = current_file;
            return nf;
        }


	ifstream file;
	file.open("../Generated_Models/" + current_file);

	file >> nf.num_triangles;
    nf.name = current_file;
	while (!file.eof()) {
		Point new_vertex;
		file >> new_vertex.x >> new_vertex.y >> new_vertex.z;
		nf.points.push_back(new_vertex);

        Point new_vertex_normal;
        file >> new_vertex_normal.x >> new_vertex_normal.y >> new_vertex_normal.z;
        nf.normals.push_back(new_vertex_normal);

        TexturePoint new_vertex_texture;
        file >> new_vertex_texture.x >> new_vertex_texture.y;
        nf.textures.push_back(new_vertex_texture);
	}

    figure_points.push_back(make_pair(current_file,make_pair(nf.num_triangles,make_tuple(nf.points,nf.normals,nf.textures))));

    return nf;
}

vector<Light> parseLights(XMLElement* lgts){
    XMLElement *lgt = lgts->FirstChildElement();
    vector<Light> lights;

    for (int i = 0; lgt; lgt = lgt->NextSiblingElement()){

        Light l;

        const char *type = lgt->Attribute("type");
        l.pos[0] = 0.0f; l.pos[1] = 0.0f; l.pos[2] = 0.0f; l.pos[3] = 1.0f;
        l.amb[0] = 0.0f; l.amb[1] = 0.0f; l.amb[2] = 0.0f; l.amb[3] = 1.0f;
        l.diff[0] = 1.0f; l.diff[1] = 1.0f; l.diff[2] = 1.0f; l.diff[3] = 1.0f;

        l.pos[0] = lgt->FloatAttribute("posX");
        l.pos[1] = lgt->FloatAttribute("posY");
        l.pos[2] = lgt->FloatAttribute("posZ");

        if(strcmp(type, "POINT") == 0){
            l.pos[3] = 1.0f;
        } else if(strcmp(type, "DIRECTIONAL") == 0){
            l.pos[3] = 0.0f;
        } else if(strcmp(type, "SPOTLIGHT") == 0){
            l.pos[3] = 1.0f;
        }

        l.amb[0] = lgt->FloatAttribute("ambR");
        l.amb[1] = lgt->FloatAttribute("ambG");
        l.amb[2] = lgt->FloatAttribute("ambB");

        l.diff[0] = lgt->FloatAttribute("diffR");
        l.diff[1] = lgt->FloatAttribute("diffG");
        l.diff[2] = lgt->FloatAttribute("diffB");

        l.l = GL_LIGHT0 + i;

        i++;
        lights.push_back(l);
    }
    return lights;
}

Tree parseGroup(XMLElement* father, Tree tree){
    Tree t;
    t.lights = tree.lights;

	for (XMLElement* child = father->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		const char* option = child->Value();

        switch(str2int(option)){
            case str2int("translate"):
                    t.head_figure.translation.empty = false;
                    t.head_figure.translation.time = child->FloatAttribute("time");
			        for (XMLElement *pModel = child->FirstChildElement() ; pModel != NULL; pModel = pModel->NextSiblingElement()) {
                        Point p;
                        p.x = pModel->FloatAttribute("X");
                        p.y = pModel->FloatAttribute("Y");
                        p.z = pModel->FloatAttribute("Z");
				        t.head_figure.translation.points.push_back(p);
			        }
                    break;
            case str2int("rotate"):
                    t.head_figure.rotation.empty = false;
            		t.head_figure.rotation.x = child->FloatAttribute("axisX");
            		t.head_figure.rotation.y = child->FloatAttribute("axisY");
            		t.head_figure.rotation.z = child->FloatAttribute("axisZ");
                    if (child->FloatAttribute("angle")){
                        t.head_figure.rotation.angle = child->FloatAttribute("angle");
                    }
			        else if (child->FloatAttribute("time")){
                        t.head_figure.rotation.time = child->FloatAttribute("time");
                    }
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
                        t.head_figure.color.r = m_node->FloatAttribute("R");
                        t.head_figure.color.g = m_node->FloatAttribute("G");
                        t.head_figure.color.b = m_node->FloatAttribute("B");
            		}
                    break;
            case str2int("group"):
                    Tree newTree = parseGroup(child,t);
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

    tree.lights = parseLights(pRootgroup);

    pRootgroup = pRootgroup->NextSiblingElement();

	tree = parseGroup(pRootgroup,tree);

    return tree;

}
