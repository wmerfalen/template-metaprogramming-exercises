/**
 * Exercise 2-1: 
 * =============
 * Write a ternary metafunction replace_type<c,x,y> that replaces all instances of x within c with y
 * Use cases: 
 * typedef replace_type<void*,void,int>::type v1; // int*
 * typedef replace_type<
 * 	int const *[10],
 * 	int const,
 * 	long>::type t2; //long* [10]
 * typedef replace_type<
 * 	char& (*)(char&),
 * 	char&,
 * 	long&>::type t3; //long& (*)(long&)
 * Author: William Merfalen [github@bnull.net]
 */
#include <iostream>
#include <type_traits>

template <typename T,typename N, typename F>
struct replace_type_impl{ };
template <typename T,typename F,bool t_is_array,bool t_is_function,bool t_base_is_pointer>
struct array_or_func{};
template <typename T,typename F>
struct array_or_func<T,F,true,false,true>{
	using type = F*[std::extent<T>::value];
};
template <typename T,typename F>
struct array_or_func<T,F,true,false,false>{
	using type = F[std::extent<T>::value];
};
template <typename T,typename F>
struct array_or_func<T,F,false,false,true>{
	using type = F*;
};
template <typename T,typename F>
struct array_or_func<T,F,false,true,true>{
	using type = F(*)(F);
};
template <typename T,typename F>
struct array_or_func<T,F,false,true,false>{
	using type = F(*)(F);
};
template <typename T,bool is_function>
struct r_is_function{};
template <typename T>
struct r_is_function<T,true>{
	using type = T (*) (T);
};
template <typename T>
struct r_is_function<T,false>{
	using type = T*;
};
template <typename T,typename N, typename F>
struct replace_type_impl<T*,N,F>{
	using type = typename r_is_function<F,std::is_function<T>::value>::type;
};
template <typename T,typename N, typename F>
struct replace_type_impl<T,N const,F>{
	using type = typename array_or_func<
		T,F,
		std::is_array<T>::value,
		std::is_function<T>::value,
		std::is_pointer<typename std::remove_extent<T>::type>::value
	>::type;
};
template <typename T,typename N, typename F>
struct replace_type {
	typedef typename replace_type_impl<T,N,F>::type type;
};

long foo;
long& test_long(long&){ return foo;}
int main(int argc,char** argv){
	constexpr bool is_same = std::is_same<typename replace_type<void*,void,int>::type,int*>::value;
	std::cout << "[test-case 0] replace_type<void*,void,int> +  int* ";
	std::cout << (is_same ? "[ same ]" : "[ different ]") << "\n";
	
	typedef typename replace_type<int const*[10],int const,long>::type array_t;
	constexpr bool is_same1 = std::extent<array_t>::value == 10 
		&& std::is_pointer<typename std::remove_extent<array_t>::type>::value;
	std::cout << "[test-case 1] replace_type<int const*[10],int const,long> +  long *[10] ";
	std::cout << (is_same1 ? "[ same ]" : "[ different ]") << "\n";

	typedef typename replace_type<char& (*)(char&),char&,long&>::type func_t;
	func_t f = test_long;
	return 0;
}
