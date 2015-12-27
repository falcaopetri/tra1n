/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef LIST_H
#define LIST_H

#include <stdexcept>

namespace rails
{
	template<class T>
	class List{
	private:
		T* array;
		size_t tam;
	public:
	    // From: http://www.developerfusion.com/article/133063/constructors-in-c11/
	    //     e http://en.cppreference.com/w/cpp/utility/initializer_list
		List(std::initializer_list<T> args)
            : List(args.size())
		{
            int i = 0;
            for (auto iter = args.begin(); iter != args.end(); ++iter)
            {
                array[i] = *iter;
                ++i;
            }
        }
		List(size_t tamanho)
		{
            tam = tamanho;
            array = new T[tamanho];
        }
		size_t size() const
		{
            return tam;
        }
		T& operator[](size_t pos) const
        {
            return at(pos);
        }
		T& at(size_t pos) const
		{
            if (0 <= pos && pos < tam)
            {
                return array[pos];
            }
            else
            {
                throw std::out_of_range("wrong access");
            }
        }
	};
}
#endif
