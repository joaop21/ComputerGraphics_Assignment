#ifndef PARSER_H
#define PARSER_H
#endif

#include <vector>

using namespace std;
using namespace geometry;

/**
* @brief Função que lê o ficheiro XML que contêm os modelos a carregar,
*     posteriormente lê os modelos e armazena os pontos e as figuras necessárias
*     para mais à frente poderem ser desenhadas.
*
* @param figures , vector onde se armazenará o necessário a carregar
*/
void parser_XML(Tree tree);
