/**
 * Exercise 2-0: 
 * =============
 * Write a unary metafunction add_const_ref<T> that returns T if T is a reference,
 * otherwise have it return T const &.
 * Author: William Merfalen [github@bnull.net]
 */
#include <iostream>
#include <type_traits>

template <typename T>
struct add_const_ref {
	using type = T const &;
};
template <typename T>
struct add_const_ref<T&> {
	using type = T;
};

/* Our test data type */
struct A {};
int main(int argc,char** argv){
	constexpr bool is_same = std::is_same<typename add_const_ref<A&>::type,A>::value;
	std::cout << "[test-case 0] add_const_ref<A&> +  A ";
	std::cout << (is_same ? "[ same ]" : "[ different ]") << "\n";
	constexpr bool is_same1 = std::is_same<typename add_const_ref<A>::type,A const &>::value;
	std::cout << "[test-case 1] add_const_ref<A> +  A const & ";
	std::cout << (is_same1 ? "[ same ]" : "[ different ]") << "\n";
	return 0;
}
