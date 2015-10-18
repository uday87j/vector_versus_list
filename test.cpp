#ifndef VEC_LIST_TEST_H_
#define VEC_LIST_TEST_H_

#include <iostream>
#include <cstdint>
#include <random>
#include <array>
#include <limits>
#include <list>
#include <algorithm>
#include <chrono>
#include <cassert>

using namespace std;

template<typename T>
void print_container(const T& c)  {
    for(auto& v : c)    {
        cout << v << endl;
    }
}

template<typename T, typename INT>
void fill_container(T& c, INT* src, const uint32_t N)  {   //array_view not yet availabe!
    for (auto i = 0; i < N; ++i, ++src)    {
        assert(src != nullptr);
        auto pos    = std::find_if(c.begin(), c.end(), [src](const int i)	{
			return *src > i;
		});
		// We found the right position for the new element
		c.insert(pos, *src);
    }
}

template<typename T>
void empty_container(T& c, const uint32_t N) {
	std::uniform_int_distribution<uint32_t> dist(0, N-1);
	std::random_device rd;
	auto size   = N;
	auto itr    = c.begin();
	typedef std::uniform_int_distribution<uint32_t>::param_type p_t;
    for(auto i = 0; i < N; ++i) {
        itr = c.begin();
        std::advance(itr, dist(rd));
        c.erase(itr);
        --size;
        p_t p(0, size-1);
        dist.param(p);
    }
}

template<typename T, typename INT>
void instrument_random_insert(T& c, INT* src, const uint32_t N, std::ostream& out = std::cout) {

    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

    start = std::chrono::system_clock::now();
	
	fill_container(c, src, N);
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = (end - start);
	out << "\nTime to fill: " << elapsed_seconds.count() << endl;
}

template<typename T>
void instrument_random_erase(T& c, const uint32_t N, std::ostream& out = std::cout)    {

    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;

    start = std::chrono::system_clock::now();
	
	empty_container(c, N);
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = (end - start);
	out << "\nTime to empty: " << elapsed_seconds.count() << endl;
}

template<const std::uint32_t N>
void instrument_vector_list()  {

    std::ofstream ofile("access_time.txt");
    assert(ofile.is_open());

    // Create & fill N element array with random numbers
	std::array<int, N> iarr;
	std::uniform_int_distribution<int> int_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	std::random_device rd;

	for(auto& a : iarr)	{
		a	= int_dist(rd);
	}

	cout << "\n Following containers are instrument in order\
	    \n1. std::vector\
	    \n2. std::vector with reserve()\
	    \n3. std::list\
	    \n4. std::list with allocate()\n";
	cout << "\nN = " << N << "\n";

	std::vector<int> ivec;
	instrument_random_insert(ivec, iarr.data(), N, ofile);
	
    std::vector<int> pa_ivec;
    pa_ivec.reserve(N);
	instrument_random_insert(pa_ivec, iarr.data(), N, ofile);

    std::list<int> ilist;
	instrument_random_insert(ilist, iarr.data(), N, ofile);
	
	std::list<int> pa_ilist;
	pa_ilist.get_allocator().allocate(N);
	instrument_random_insert(pa_ilist, iarr.data(), N, ofile);
	
	instrument_random_erase(ivec, N, ofile);

	instrument_random_erase(pa_ivec, N, ofile);

	instrument_random_erase(ilist, N, ofile);

	instrument_random_erase(pa_ilist, N, ofile);

	ofile.close();

}

int main()	{

	constexpr const std::array<uint32_t, 10> N    = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000};

    instrument_vector_list<N[0]>();
    instrument_vector_list<N[1]>();
    instrument_vector_list<N[2]>();
    instrument_vector_list<N[3]>();
    instrument_vector_list<N[4]>();
    instrument_vector_list<N[5]>();
    instrument_vector_list<N[6]>();
    instrument_vector_list<N[7]>();
    instrument_vector_list<N[8]>();
    instrument_vector_list<N[9]>();

	return 0;
}
#endif
