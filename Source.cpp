#include <iostream>
#include <string_view>
#include <vector>
#include <optional>
#include"Stack.h"

Stack<int>::type_t& enter_number(int condition);

int main()
{
    setlocale(LC_ALL, "Russian");
    Stack<int> m_stck{1,2,3};
    Stack<int>::Iterator iterator;
    iterator = m_stck.Begin();

    m_stck.print_stack();

    int menu{-1};
    constexpr std::string_view str_menu[]{
        "0-Выход",
        "1-Просмотреть стек",
        "2-Значение верхнего элемента",
        "3-Добавить элемент",
        "4-Найти элемент",
        "5-Удалить текеущий элемент",
        "6-Случайное заполнение",
        "7-Считать из файла",
        "8-Запись в файл",
        "9-Очистить стек",
        "10-Вывод меню"
    };
 
    auto print_menu = [&]() constexpr {
        for (auto&& element : str_menu) {
            std::cout << element << std::endl;

        }
    };
    
    print_menu();

    while (menu) {
        std::cout << "Введите состояние: "; std::cin >> menu; 
        switch (menu)
        {

        case 1:
            m_stck.print_stack();
        break;
        case 2:
        {
            auto temp = m_stck.top();
            if (!temp) std::cout << "Стек пуст" << std::endl;
        }
        break;
        case 3:
        {
            try {
                auto number = enter_number(3);
                m_stck.push(number);
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка ввода" << std::endl;
            }
        }
        break;
        case 4:
        {
            try {
                auto number = enter_number(4);
                std::cout <<"Позиция числа в стеке: " << m_stck.findValue(number);
               // temp==-1? std::cout << "Число не найдено" : std::cout << temp<<std::endl;
            }
            catch (const std::exception& e) {
               // std::cout << "Ошибка ввода"<<std::endl;
                std::cout <<e.what() << std::endl;
            }
        }
        break;
        case 5:
        {
            try {
                m_stck.pop();
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 6:
        {
            int ld{}, rd{}, count{};
            std::cout << "Введите диапазон и количество чисел :";
            std::cin >> ld >> rd >> count;
            m_stck.fill_rnumb(count, ld, rd);
        }
        break;
        case 7:
        {
            m_stck.read_fr_file("m_txt.txt");           
        }
        break;
        case 8:
        {
            m_stck.write_to_file("m_txt.txt");
        }
        break;
        case 9:
        {
            m_stck.clear();
        }
        break;
        case 10:
        {
            print_menu();
        }
        break;

        case 0:
            break;

        default:
            std::cout << "Ошибка"<<std::endl;
        }

    }
   
}

template<typename T>
inline void Stack<T>::print_stack() const noexcept
{
    /*
    pointNode* head = this->head.get();
    if (!head) std::cout << "стек пуст";
    else
        while (head) {
            std::cout << head->data << " ";
            head = head->next.get();

        }
        std::cout << std::endl;
    */
    
    //Stack<T>::Iterator iterator = this->Begin();



}

Stack<int>::type_t& enter_number (int condition) {
    condition==4? std::cout << "Введите элемент для нахождения:": std::cout << "Введите число:";
    Stack<int>::type_t number;
    std::cin >> number;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //std::cout << "Ошибка ввода " << std::endl;
        throw std::exception("Ошибка ввода ");
    }
    else {
        return number;
    }
}
