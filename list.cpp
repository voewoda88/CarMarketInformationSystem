#include "list.h"
#include "exception.h"

template <class T>
List<T>::List()
{
  // Создать пустой список
  begin = end = nullptr;
  count = 0;
}



template <class T>
List<T>::List(const List& obj)
{
  // Сделать копию из списка
  Copy(obj);
}



//конструктор копирования
template <class T>
void List<T>::Copy(const List<T>& obj)
{
  // 1. Очистить список (освободить память)
  Clear();

  // 2. Цикл копирования this <= obj
  Element<T>* t = obj.begin;

  while (t != nullptr)
  {
    AddEnd(t->data);
    t = t->next;
  }
}



// Очистка списка
template <class T>
void List<T>::Clear()
{
  // Нужно count раз удалить первый элемент списка
  int n = count; // сделать копию из count - важно!
  for (int i = 0; i < n; i++)
    Del(0);
}



template <class T>
void List<T>::Del(int index)
{
  try
  {
      // 1. Проверка, есть ли элементы в списке
      if (count == 0)
        throw EmptyListException("List is empty");

      // 2. Игнор, если позиция указана неправильно
      if (!CorrectIndex(index))
        throw IndexException("Incorrect index");

      // 3. Перейти к удаляемому элементу
      Element<T>* item = Move(index);

      // 4. Получить предыдущий элемент
      Element<T>* itemPrev = item->prev;

      // 5. Получить следующий элемент
      Element<T>* itemNext = item->next;

      // 6. Проверка, удаляется ли не первый элемент списка
      if ((count > 1) && (itemPrev != nullptr))
        itemPrev->next = itemNext; // обойти элемент item

      // 7. Проверка, удаляется ли не последний элемент списка
      if ((itemNext != nullptr) && (count > 1))
        itemNext->prev = itemPrev;

      // 8. Если удаляется первый элемент
      if (index == 0)
        begin = itemNext;

      // 9. Если удаляется последний элемент
      if (index == count - 1)
        end = itemPrev;

      // 10. Удалить элемент item
      delete item;

      // 11. Уменьшить общее количество элементов
      count--;
  }
  catch(EmptyListException ex)
  {
      qDebug() << "Error message: " << ex.what();
      qDebug() << "Error code: " << ex.GetErrorCode();
  }
  catch(IndexException ex)
  {
      qDebug() << "Error message: " << ex.what();
      qDebug() << "Error code: " << ex.GetErrorCode();
  }
}



template <class T>
Element<T>* List<T>::Move(int index)
{
  // 1. Установить указатель на начало списка
  Element<T>* t = begin;

  // 2. Перемотать в позицию index
  for (int i = 0; i < index; i++)
    t = t->next;

  // 3. Вернуть указатель
  return t;
}



template <class T>
bool List<T>::CorrectIndex(int index)
{
  return (index >= 0) && (index < count);
}



template <class T>
void List<T>::AddEnd(T _data)
{
  try
  {
    // 1. Создать новый элемент с данными _data
    Element<T>* t = new Element<T>;
    if(!t)
        throw MemoryException("Error of memory");
    t->next = nullptr; // следующего элемента нет
    t->prev = end; // установить предыдущий элемент
    t->data = _data; // записать данные

    // 2. Заполнить поле next пока что последнего элемента
    if (end != nullptr)
      end->next = t;

    // 3. Проверка, есть ли в списке элементы
    if (count == 0)
    {
      // если элементов нет,
      // то это одновременно и начало и конец списка
      begin = end = t;
    }
    else
    {
      // если элементы в списке есть, то это конец списка
      end = t;
    }

    // 3. Увеличить общее количество элементов
    count++;
  }
  catch (MemoryException ex)
  {
    qDebug() << "Error message: " << ex.what();
    qDebug() << "Error code: " << ex.GetErrorCode();
  }
}



template <class T>
void List<T>::AddBegin(T _data)
{
  try
  {
    // 1. Создать новый элемент (новую ячейку памяти)
    // и заполнить его данными
    Element<T>* t = new Element<T>;
    if(!t)
        throw MemoryException("Error of memory");
    t->data = _data; // данные
    t->prev = nullptr; // предыдущего элемента нет

    // следующий элемент указывает на предыдущий первый
    t->next = begin;

    // 2. Есть ли элементы в списке?
    if (count > 0)
    {
      // если есть, то перенаправить предыдущее начало списка
      begin->prev = t;
      begin = t;
    }
    else
    {
      // если элементов нет, то начало и конец есть тем самым элементом
      begin = end = t;
    }

    // 3. Увеличить общее количество элементов
    count++;
  }
  catch (MemoryException ex)
  {
    qDebug() << "Error message: " << ex.what();
    qDebug() << "Error code: " << ex.GetErrorCode();
  }
}



template <class T>
void List<T>::Insert(T _data, int index)
{
  // 1. Проверка, корректна ли позиция
  if (!CorrectIndex(index))
    return;

  // 2. Проверка, вставка ли в конец списка (по указателю end)
  if (index == count)
  {
    // Добавить данные по указателю end
    AddEnd(_data);
    return;
  }

  // 3. Проверка, вставка ли в начало списка (перед begin)
  if (index == 0)
  {
    AddBegin(_data);
    return;
  }

  try
  {
    // 4. Получить элемент перед позицией вставки
    Element<T>* itemPrev = Move(index - 1);

    // 5. Получить элемент в позиции вставки
    Element<T>* item = Move(index);

    // 6. Создать новый элемент и вставить его в список
    Element<T>* t = new Element<T>;
    if(!t)
        throw MemoryException("Error of memory");
    t->data = _data;
    t->next = item;
    t->prev = itemPrev;
    itemPrev->next = t;
    item->prev = t;

    // 7. Увеличить количество элементов
    count++;
  }
  catch (MemoryException ex)
  {
    qDebug() << "Error message: " << ex.what();
    qDebug() << "Error code: " << ex.GetErrorCode();
  }
}


template <class T>
void List<T>::Reverse()
{
  List<T> L;
  Element<T>* t = begin;

  // цикл формирования списка,
  // элемент добавляется в начало списка
  while (t != nullptr)
  {
    L.AddBegin(t->data);
    t = t->next;
  }
  *this = L;
}

template <class T>
int List<T>::Count()
{
  return count;
}



template <class T>
void List<T>::Print()
{
  Element<T>* t = begin;
  for (int i = 0; i < count; i++)
  {
    qDebug() << t->data << " ";
    t = t->next;
  }
}



template <class T>
bool List<T>::isEmpty()
{
    if(begin == nullptr && end == nullptr)
        return true;
    return false;
}



template <class T>
List<T>& List<T>::operator=(const List& obj)
{
  Copy(obj);
  return *this;
}

template <class T>
T List<T>::GetElement(int index)
{
  try
  {
        // Проверка, корректен ли индекс,
      // если индекс не корректен, сгенерировать исключение
      if (!CorrectIndex(index))
        throw IndexException("Incorrect index");

      // Если индекс корректен, то вернуть элемент
      Element<T>* t = Move(index);
      return t->data;
  }
  catch(IndexException ex)
  {
      qDebug() << "Error message: " << ex.what();
      qDebug() << "Error code: " << ex.GetErrorCode();
  }
}

template <class T>
void List<T>::SetElement(T _data, int index)
{
  try
  {
    // Проверка, корректна ли позиция
      if (!CorrectIndex(index))
        throw IndexException("Incorrect index");

      // Получить элемент по позиции и изменить его значение
      Element<T>* t = Move(index);
      t->data = _data;
  }
  catch(IndexException ex)
  {
      qDebug() << "Error message: " << ex.what();
      qDebug() << "Error code: " << ex.GetErrorCode();
  }
}



template <class T>
List<T>& List<T>::operator+(const List<T>& obj)
{
  // 1. Получить доступ к списку obj
  Element<T>* t = obj.begin;

  // 2. Добавить к временному списку элементы t
  while (t != nullptr)
  {
    AddEnd(t->data);
    t = t->next;
  }

  // 3. Вернуть объединенный список
  return *this;
}



template <class T>
bool List<T>::operator==(const List<T>& obj)
{
  // 1. Сначала сравнить размеры списков
  if (count != obj.count)
    return false;

  // 2. Если размеры одинаковы, то сравнить поэлементно
  Element<T>* t1 = begin;
  Element<T>* t2 = obj.begin;

  while (t1 != nullptr)
  {
    // Как только найдено хотя бы одно несовпадение, то выход с кодом false
    if (t1->data != t2->data)
      return false;

    t1 = t1->next;
    t2 = t2->next;
  }

  return true;
}



template <class T>
bool List<T>::operator!=(const List<T>& obj)
{
  // Использовать оператор сравнения ==
  return !(*this == obj);
}



template <class T>
bool List<T>::operator>=(const List<T>& obj)
{
  // 1. Сравнить количество элементов
  if (count > obj.count)
    return true;

  // 2. Сравнить по содержанию
  if (*this == obj)
    return true;

  return false;
}



template <class T>
bool List<T>::operator<=(const List<T>& obj)
{
  // 1. Сравнение по количеству элементов в списке
  if (count < obj.count)
    return true;

  // 2. Сравнение по содержанию
  if (*this == obj)
    return true;

  return false;
}



template <class T>
bool List<T>::operator>(const List<T>& obj)
{
  if (count > obj.count)
    return true;
  return false;
}



template <class T>
bool List<T>::operator<(const List<T>& obj)
{
  if (count < obj.count)
    return true;
  return false;
}



template <class T>
T List<T>::operator[](int index)
{
  Element<T>* t = Move(index);
  return t->data;
}

template <class T>
List<T>::~List()
{
  Clear(); // очистить список
}
