#include "LinkedList.h"

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    Node<T>* nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}
template <typename T>
void LinkedList<T>::insert(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = newNode;
    } else {
        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
template <typename T>
void LinkedList<T>::display() const {
    Node<T>* temp = head;
    while (temp) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}
template <typename T>
void LinkedList<T>::deleteIndex(int index) {
    if (index < 0 || !head) return;

    Node<T>* temp = head;

    if (index == 0) {
        head = head->next;
        delete temp;
        return;
    }

    for (int i = 0; temp != nullptr && i < index - 1; i++) {
        temp = temp->next;
    }

    if (!temp || !temp->next) return;

    Node<T>* next = temp->next->next;
    delete temp->next;
    temp->next = next;
}