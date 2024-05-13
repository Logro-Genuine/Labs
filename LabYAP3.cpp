//Вариант 24
//Сортировка слиянием (Merge) и Сортировка выбором (Selection). Двусвязный нециклический список

#include <iostream>
#include <fstream>
using namespace std;
//DL - Double Linked
struct DLList {

    struct Node {
        double data; // Данные, хранящиеся в узле
        Node* prev; // Указатель на предыдущий узел
        Node* next; // Указатель на следующий узел
    };

    Node* cur; //Текущий элемент
    Node* head;//Голова списка
    Node* tail;//Хвост списка
    void append(double data);
    DLList() { head = nullptr; tail = nullptr; cur = nullptr; };
};

void DLList::append(double data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = tail;
    newNode->next = nullptr;//"Бросаем мостики"

    if (head == nullptr) {//Если список пустой, вставляем элемент в голову
        head = newNode;
    }
    else {//Вставляем элемент в хвост, хвост сдвигаем
        tail->next = newNode;
    }

    tail = newNode;
}

void my_swap(DLList::Node* node1, DLList::Node* node2)
{
    DLList::Node* prev1 = node1 -> prev;//Предшествующий первому элементу 
    DLList::Node* prev2 = node2 -> prev;//Предшествующий второму элементу 
    DLList::Node* next1 = node1 -> next;//Следующий за первым элементом 
    DLList::Node* next2 = node2 -> next;//Следующий за вторым элементом

    if (node2 == next1)//node1 node2 -> node2 node1
    {
        node2->next = node1;
        node1->next = next2;
        prev1->next = node2;
    }
    else if (node1 == next2)//node2 node1 -> node1 node2
    {
        node1->next = node2;
        node2->next = next1;
        prev2->next = node2;
    }
    else//[..node1...node2..] -> [..node2...node1..]
    {
        prev1->next = node2;
        node2->next = next1;
        prev2->next = node1;
        node1->next = next2;
    }
}

DLList::Node* merge(DLList::Node* part1, DLList::Node* part2) {
    if (part1 == nullptr) {
        return part2;
    }
    if (part2 == nullptr) {
        return part1;
    }
    // Если part1 < part2, объединить part1 и part2 и обновить указатели.
    if (part1->data < part2->data) {
        part1->next = merge(part1->next, part2);
        part1->next->prev = part1;
        part1->prev = nullptr;
        return part1;
    }
    // В противном случае объединить part2 и part1 и обновите указатели.
    else {
        part2->next = merge(part1, part2->next);
        part2->next->prev = part2;
        part2->prev = nullptr;
        return part2;
    }
}

DLList::Node* getMiddle(DLList::Node* head) {
    DLList::Node* end = head;
    DLList::Node* mdl = head;
    //Находим середину, end движется на два узла, чтобы достичь конца, mdl на один, чтобы достичь середины
    while (end->next && end->next->next) {
        end = end->next->next;
        mdl = mdl->next;
    }
    //Отсоединяем середину от остального списка
    DLList::Node* middle = mdl->next;
    mdl->next = nullptr;
    middle->prev = nullptr;
    return middle;
}

void mergeSort(DLList::Node*& head) {
    if (head == nullptr || head->next == nullptr) {// Список пустой или содержит только один элемент, нечего сортировать
        return;
    }

    DLList::Node* middle = getMiddle(head); //Ищем середину списка

    mergeSort(head); //Рекурсивно сортируем превую половину
    mergeSort(middle);//Рекурсивно сортируем вторую половину

    head = merge(head, middle);//Соединяем
}

void selectionSort(DLList* list) {
    if (list -> head == nullptr || list -> head == list ->tail) {// Список пустой или содержит только один элемент, нечего сортировать
        return;
    }
    DLList::Node* current = list -> head;
    while (current != list -> tail) {
        DLList::Node* minNode = current;
        DLList::Node* temp = current->next;
        // Поиск узла с минимальным значением в оставшейся части списка
        while (temp != nullptr) {
            if (temp->data < minNode->data) {
                minNode = temp;
            }
            temp = temp->next;
        }
        // Обмен значениями узлов, если найден новый минимальный узел
        if (minNode != current) {
            my_swap(current, minNode);
        }

        current = current->next;
    }
}

int main()
{
    ifstream input("input.txt", ios::binary);
    ofstream output("output.txt", ios::binary);

    DLList* list = new DLList;
    int v = 0;
    input >> v;

    int size = 0;
    list->cur = list->head;
    while (!input.eof())
    {
        input >> v;
        list->append(v);
        size++;
    }
    v ? mergeSort(list->head) : selectionSort(list);
    list->cur = list->head;
    output << size << ' ';
    while (list->cur)//Запись списка в файл
    {
        output << list->cur->data << ' ';
        //Очищение памяти
        DLList::Node* next;
        next = list->cur->next;
        delete list->cur;
        list->cur = next;
    }
    delete list;
    input.close();
    output.close();
    return 0;
}
