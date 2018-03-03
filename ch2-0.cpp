/**
 * Exercise 2-0: 
 * =============
 * Write a unary metafunction add_const_ref<T> that returns T if T is a reference,
 * otherwise have it return T const &.
 * Author: William Merfalen [github@bnull.net]
 */
#include <iostream>
#include <type_traits>

template <typename T,bool is_const_ref>
struct add_const_ref_impl { };

template <typename T>
struct add_const_ref_impl <T,true> {
	typedef T type;
};
template <typename T>
struct add_const_ref_impl <T,false> {
	typedef T const & type;
};
template <typename T>
struct add_const_ref {
	typedef typename add_const_ref_impl<T,std::is_reference<T>::value>::type type;
};

/* Our test data type */
struct A {};
int main(int argc,char** argv){
	constexpr bool is_same = std::is_same<typename add_const_ref<A>::type,A const &>::value;
	std::cout << "[test-case 0] add_const_ref<A> +  A const & ";
	std::cout << (is_same ? "[ same ]" : "[ different ]") << "\n";
	constexpr bool is_same2 = std::is_same<typename add_const_ref<A const &>::type,A const &>::value;
	std::cout << "[test-case 1] add_const_ref<A const &> +  A const & ";
	std::cout << (is_same2 ? "[ same ]" : "[ different ]") << "\n";
	constexpr bool is_same3 = std::is_same<typename add_const_ref<A>::type,A&>::value;
	std::cout << "[test-case 2] add_const_ref<A> +  A & ";
	std::cout << (is_same3 ? "[ same ]" : "[ different ]") << "\n";
	return 0;
}
