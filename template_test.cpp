#include <vector>
#include <iostream>
#include <boost/foreach.hpp>
#include <borg/util/lazy_instance.hpp>

template<typename Type, int Size>
class array
{
public:
  const Type &
  operator[](unsigned int n) const
  {
    return data[n];
  }
  
  Type &
  operator[](unsigned int n)
  {
    return data[n];
  }
  
  Type data[Size];
  int a;
};

/*template<class ArrayType>
void
print_array(ArrayType arg)
{
  for(int i = 0; i < 4; ++i)
    std::cout << "array[" << i << "]: " << arg[i] << std::endl;
}*/
void
print_array(int arg[])
{
  for(int i = 0; i < 4; ++i)
    std::cout << "array[" << i << "]: " << arg[i] << std::endl;
}

void
print_array(const array<int, 4> &arg)
{
  for(int i = 0; i < 4; ++i)
    std::cout << "array[" << i << "]: " << arg[i] << std::endl;
}

void
print_array(const std::vector<int> &arg)
{
  for(int i = 0; i < 4; ++i)
    std::cout << "array[" << i << "]: " << arg[i] << std::endl;
}

int main()
{
  int old_c_array[4] = { 1, 2, 3, 4 };
  
  array<int, 4> my_array = {{ 1, 2, 3, 4 }, -1};
      
  std::vector<int> my_vector;
  
  borg::lazy_instance< array<int, 4> > lazy_array;

  array<int, 4> &array_ref = lazy_array;

  array_ref[0] = 4;
  array_ref[1] = 3;
  array_ref[2] = 2;
  array_ref[3] = 1;
  
  my_vector.push_back(1);
  my_vector.push_back(2);
  my_vector.push_back(3);
  my_vector.push_back(4);

//  print_array(old_c_array);
  print_array(lazy_array);
//  print_array(my_vector);
}
