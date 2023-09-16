#ifndef LIST_H
#define LIST_H

template <class T>
class Iterator;

template <class T>
struct Element
{
  T data; // данные
  Element<T>* next; // адрес следующего элемента в списке
  Element<T>* prev; // адрес предыдущего элемента в списке
};

template <class T>
class List
{
public:
    List();
    List(const List& obj);
    void Clear();
    void Del(int index);
    void AddEnd(T _data);
    void AddBegin(T _data);
    void Insert(T _data, int index);
    void Reverse();
    int  Count();
    void Print();
    bool isEmpty();
    T GetElement(int index);
    void SetElement(T _data, int index);

    List<T>& operator=(const List& obj);
    List<T>& operator+(const List<T>& obj);
    bool operator==(const List<T>& obj);
    bool operator!=(const List<T>& obj);
    bool operator>=(const List<T>& obj);
    bool operator<=(const List<T>& obj);
    bool operator>(const List<T>& obj);
    bool operator<(const List<T>& obj);
    T operator[](int index);

    ~List();

    friend class Iterator<T>;

private:
    void Copy(const List<T>& obj);
    Element<T>* Move(int index);
    bool CorrectIndex(int index);

private:
  Element<T>* begin; // указатель на первый элемент списка
  Element<T>* end; // указатель на последний элемент списка
  int count; // количество элементов в списке
};

template <class T>
class List;

template <class T>
class Iterator
{
public:
    Iterator(List<T>&);
    ~Iterator() = default;

    bool hasNext();
    bool hasPrevious();
    Iterator<T>& next();
    Iterator<T>& previous();

    Iterator<T>& operator++();
    Iterator<T>& operator++(int);

    Iterator<T>& operator--();
    Iterator<T>& operator--(int);
    Iterator<T>& operator()(List<T>& list);

    T& operator*();

    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
    bool operator>(const Iterator& other);
    bool operator<(const Iterator& other);
    bool operator>=(const Iterator& other);
    bool operator<=(const Iterator& other);


private:
    Element<T>* node;
};

template<class T>
Iterator<T>& Iterator<T>::next()
{
    if (hasNext())
    {
        this->node = this->node->next;
    }
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::previous()
{
    if (hasPrevious())
    {
        this->node = this->node->prev;
    }
    return *this;
}

template<class T>
bool Iterator<T>::hasNext()
{
    if (this->node != nullptr)
        return true;
    return false;
}

template<class T>
bool Iterator<T>::hasPrevious()
{
    if (this->node != nullptr)
        return true;
    return false;
}

template<class T>
Iterator<T>::Iterator(List<T>& list)
{
    node = list.begin;
}

template <class T>
Iterator<T>& Iterator<T>::operator++()
{
    if (hasNext())
    {
        this->node = this->node->next;
    }
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator++(int)
{
    if (hasNext())
    {
        this->node = this->node->next;
    }
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator--()
{
    if (hasPrevious())
    {
        this->node = this->node->prev;
    }
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator--(int)
{
    if (hasPrevious())
    {
        this->node = this->node->prev;
    }
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator()(List<T>& list)
{
    this->node = list.begin;
    return *this;
}

template <class T>
T& Iterator<T>::operator*()
{
    return this->node->data;
}

template <class T>
bool Iterator<T>::operator==(const Iterator& other)
{
    return this->node == other.node;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator& other)
{
    return this->node != other.node;
}

template <class T>
bool Iterator<T>::operator>(const Iterator& other)
{
    return this->node > other.node;
}

template <class T>
bool Iterator<T>::operator<(const Iterator& other)
{
    return this->node < other.node;
}

template <class T>
bool Iterator<T>::operator>=(const Iterator& other)
{
    return this->node > other.node;
}

template <class T>
bool Iterator<T>::operator<=(const Iterator& other)
{
    return this->node < other.node;
}

#endif // LIST_H
