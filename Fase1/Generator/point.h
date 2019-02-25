/**
* @brief classe que define intancias de Ponto
*/
class Point{
    private:
        float x,y,z;
    public:
        Point(){
            x = 0;
            y = 0;
            z = 0;
        }
        Point(float xn, float yn, float zn){
            x = xn;
            y = yn;
            z = zn;
        }
        float getX(){return x;}
        float getY(){return y;}
        float getZ(){return z;}
};
