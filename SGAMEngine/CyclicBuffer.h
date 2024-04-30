#pragma once
#include <vector>
#include <iostream>

namespace sgam
{
    template <typename T>
	class CyclicBuffer final
	{
	public:
        explicit CyclicBuffer(uint32_t size)
            : m_Size{ size }
        {
            m_Buffer.resize(size);
        }

        void Push(const T& item);
        T Pop();

        bool IsEmpty() const { return m_IsEmpty; }

	private:
        std::vector<T> m_Buffer{};

        uint32_t m_Size{};
        uint32_t m_Head{};
        uint32_t m_Tail{};

        bool m_IsEmpty{ true };
	};

    template<typename T>
    void CyclicBuffer<T>::Push(const T& item)
    {
        if (m_Head == m_Tail && !m_IsEmpty)
        {
            std::cout << "Failed to push item to full buffer!\n";
            return;
        }

        m_Buffer.at(m_Tail) = item;
        m_Tail = (m_Tail + 1) % m_Size;
        m_IsEmpty = false;
    }

    template<typename T>
    T CyclicBuffer<T>::Pop()
    {
        if (m_IsEmpty)
        {
            throw std::out_of_range("Buffer is empty!");
        }

        T item{ m_Buffer.at(m_Head) };
        m_Head = (m_Head + 1) % m_Size;
        if (m_Tail == m_Head) m_IsEmpty = true;
        return item;
    }
}
