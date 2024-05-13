#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Vert {//Точка полигона
    double x;
    double y;
};

class Polygon {
    long long numOfVert;//Количество точек полигона
    vector<Vert> arrOfVert;//Массив точек полигона
    friend istream& operator>>(istream& input, Polygon& obj);//Объявление перегрузок функций ввода и вывода дружественными,
    friend ostream& operator<<(ostream& output, const Polygon& p);//чтобы они имели доступ к полям класса
public:
    Polygon() : numOfVert(0), arrOfVert() {}//Конструктор по умолчанию
    Polygon(vector <Vert>& v) {//Конструктор инициализации
        arrOfVert = v;
        numOfVert = v.size();
    }
    Polygon(const Polygon& p) {//Конструктор копирования
        arrOfVert = p.arrOfVert;
        numOfVert = p.numOfVert;
    }
    ~Polygon() { arrOfVert.clear(); }//Деструктор

    const long long printNumVert() const {//Вывести количество точек
        return numOfVert;
    }
    void addVert(long long index, Vert& p) {//Добавить точку
        if (index >= numOfVert) {//Если индекс указан больше чем размер, то добавляем точку в конец
            arrOfVert.push_back(p);
        }
        else {//Добавление точки по индексу
            arrOfVert.insert(arrOfVert.begin() + index, p);
        }
        ++numOfVert;
    }
    void deleteVert(Vert& p) {//Удаление точки, если она есть
        for (int i = 0; i < numOfVert; ++i) {
            if ((arrOfVert[i].x == p.x) && (arrOfVert[i].y == p.y)) {
                arrOfVert.erase(arrOfVert.begin() + i);
                --numOfVert;
                return;
            }
        }
    }
    const char* vertInPolygon(Vert& dot) const {//Наличие точки внутри полигона
        bool c = false;
        for (long long i = 0, j = numOfVert - 1; i < numOfVert; j = i++) {
            if ((((arrOfVert[i].y <= dot.y) && (dot.y < arrOfVert[j].y))
                || ((arrOfVert[j].y <= dot.y) && (dot.y < arrOfVert[i].y)))
                && ((arrOfVert[j].y - arrOfVert[i].y != 0)
                    && (dot.x > ((arrOfVert[j].x - arrOfVert[i].y) * (dot.y - arrOfVert[i].y) / (arrOfVert[j].y - arrOfVert[i].y) + arrOfVert[i].x)))) {
                c = !c;
            }
        }
        return ((c) ? "Yes" : "No");
    }
    const char* intersection(Polygon& other) const {//Пересечение полигонов
        bool c = false;
        for (long long i = 0; i < other.numOfVert; ++i) {
            if (vertInPolygon(other.arrOfVert[i])) {
                c = true;
            }
        }
        return ((c) ? "Yes" : "No");
    }
    const double area() const {//Вычисление площади полигона
        double temp1 = 0;
        double temp2 = 0;
        long long i = 0;
        for (; i < numOfVert - 1; ++i) {
            temp1 += arrOfVert[i].x * arrOfVert[i + 1].y;//(x1*y2)+(x2*y3)+...
            temp2 += arrOfVert[i].y * arrOfVert[i + 1].x;//(y1*x2)+(y2*x3)+...
        }
        temp1 += arrOfVert[i].x * arrOfVert[0].y;//x1*yn
        temp2 += arrOfVert[i].y * arrOfVert[0].x;//y1*xn
        return abs((temp1 - temp2) / 2);
    }
    void operator=(Polygon& polygon) {//Операция присваивания
        arrOfVert = polygon.arrOfVert;
        numOfVert = polygon.numOfVert;
    }
    //Для всех последующих операторов используется площадь полигона
    bool operator>(Polygon& polygon) const { return (this->area()) > polygon.area(); }
    bool operator<(Polygon& polygon) const { return (this->area()) < polygon.area(); }
    bool operator<=(Polygon& polygon) const { return (this->area()) <= polygon.area(); }
    bool operator>=(Polygon& polygon) const { return (this->area()) >= polygon.area(); }
    bool operator==(Polygon& polygon) const {
        if (numOfVert != polygon.numOfVert) return 0;
        for (long long i = 0; i < numOfVert - 1; ++i) {
            if ((arrOfVert[i].x - polygon.arrOfVert[i].x) != (arrOfVert[i + 1].x - polygon.arrOfVert[i + 1].x)
                || (arrOfVert[i].y - polygon.arrOfVert[i].y != arrOfVert[i + 1].y - polygon.arrOfVert[i + 1].y)) return 0;
        }
        return 1;
    }
};


istream& operator>>(istream& input, Polygon& obj) {//Перегрузка оператора ввода
    input >> obj.numOfVert;//Получаем количество точек
    for (long long i = 0; i < obj.numOfVert; ++i) {//Заполняем массив точками
        Vert new_p;
        input >> new_p.x >> new_p.y;
        obj.arrOfVert.push_back(new_p);
    }
    return input;
}

ostream& operator<<(ostream& output, const Polygon& p) {//Перегрузка оператора вывода
    long long i = 0;//Индекс точки массива точек
    for (; i < p.numOfVert - 1; ++i)
        output << "(" << p.arrOfVert[i].x << ", " << p.arrOfVert[i].y << "), ";//Вывод точек в формате (x, y), одна итерация вынесена для того
    return output << "(" << p.arrOfVert[i].x << ", " << p.arrOfVert[i].y << ")";//чтобы не было лишней запятой в конце
}

int main()
{
    ifstream input("input.txt", ios::binary);
    ofstream output("output.txt", ios::binary);
    char key;//Ключ означает то, какой метод будет использоваться далее
    input >> key;
    Polygon polygon;//Объекты для
    Polygon polygon2;//тестов
    Vert d;//Точка для методов 2, 3, 4

    switch (key) {
    case '1'://printNumVert - количество вершин
        input >> polygon;
        cout << polygon;
        output << polygon.printNumVert();
        break;
    case '2'://addVert - добавление вершины
        input >> polygon;
        long long index;
        input >> index >> d.x >> d.y;
        polygon.addVert(index, d);
        output << polygon;
        break;
    case '3'://deleteVert - удаление вершины
        input >> polygon >> d.x >> d.y;
        polygon.deleteVert(d);
        output << polygon;
        break;
    case '4'://vertInPolygon - принадлежность точки полигону
        input >> polygon >> d.x >> d.y;
        output << polygon.vertInPolygon(d);
        break;
    case '5'://intersection - пересечение полигонов
        input >> polygon >> polygon2;
        output << polygon.intersection(polygon2);
        break;
    case '6'://<
        input >> polygon >> polygon2;
        output << ((polygon < polygon2) ? polygon : polygon2);
        break;
    case '7'://>
        input >> polygon >> polygon2;
        output << ((polygon > polygon2) ? polygon : polygon2);
        break;
    case '8'://<=
        input >> polygon >> polygon2;
        output << ((polygon > polygon2) ? polygon : polygon2);
        break;
    case '9'://>=
        input >> polygon >> polygon2;
        output << ((polygon >= polygon2) ? polygon : polygon2);
        break;
    case '0'://==
        input >> polygon >> polygon2;
        output << ((polygon == polygon2) ? "Equal" : "Different");
        break;
    }
    input.close();
    input.close();
    return 0;
}
