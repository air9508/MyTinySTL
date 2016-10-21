#ifndef MYTINYSTL_VECTOR_TEST_H
#define MYTINYSTL_VECTOR_TEST_H

// vector 测试: 测试 vector 的 API 与 push_back 的性能

#include <iomanip>
#include <iostream>
#include <vector>

#include "..\vector.h"
#include "test.h"

using namespace std;

namespace mystl {
	namespace test {
		namespace vector_test {
			
			// vector push_back 的性能测试
			#define VECTOR_PUSH_BACK_TEST(mode, count) do { \
				srand((int)time(0)); \
				clock_t start, end; \
				mode::vector<int> v; \
				char buf[5]; \
				start = clock(); \
				for (size_t i = 0; i < count; ++i) \
					v.push_back(rand()); \
				end = clock(); \
				int n = end - start; \
				sprintf_s(buf, "%d", n); \
				string t = buf; \
				t += "ms    |"; \
				cout << setw(14) << t; \
			} while(0)
			

			void vector_test() {
				cout << "[=========================================================]" << endl;
				cout << "[-------------- Run container test : vector --------------]" << endl;
				cout << "[----------------------- API test ------------------------]" << endl;
				int a[] = { 1,2,3,4,5 };
				mystl::vector<int> v1;
				mystl::vector<int> v2(10);
				mystl::vector<int> v3(10, 1);
				mystl::vector<int> v4(a, a + 5);
				mystl::vector<int> v5(v2);
				mystl::vector<int> v6(std::move(v2));
				mystl::vector<int> v7 = v3;
				mystl::vector<int> v8 = std::move(v3);
				v8.~vector();
				
				FUN_AFTER(v1, v1.assign(10));
				FUN_AFTER(v1, v1.assign(8, 8));
				FUN_AFTER(v1, v1.assign(a, a + 5));
				FUN_AFTER(v1, v1.push_back(6));
				FUN_AFTER(v1, v1.insert(v1.begin()));
				FUN_AFTER(v1, v1.insert(v1.end(), 7));
				FUN_AFTER(v1, v1.insert(v1.begin() + 3, 2, 3));
				FUN_AFTER(v1, v1.insert(v1.begin(), a, a + 5));
				FUN_AFTER(v1, v1.pop_back());
				FUN_AFTER(v1, v1.erase(v1.begin()));
				FUN_AFTER(v1, v1.erase(v1.begin(), v1.begin() + 2));
				FUN_AFTER(v1, v1.reverse());
				FUN_AFTER(v1, v1.swap(v4));
				FUN_VALUE(*v1.begin());
				FUN_VALUE(*(v1.end() - 1));
				FUN_VALUE(*v1.rbegin());
				FUN_VALUE(*(v1.rend() - 1));
				FUN_VALUE(v1.front());
				FUN_VALUE(v1.back());
				FUN_VALUE(v1[0]);
				FUN_VALUE(v1.at(1));
				cout << boolalpha;
				FUN_VALUE(v1.empty());
				cout << noboolalpha;
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.max_size());
				FUN_VALUE(v1.capacity());
				FUN_AFTER(v1, v1.resize(10));
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.capacity());
				FUN_AFTER(v1, v1.resize(6, 6));
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.capacity());
				FUN_AFTER(v1, v1.clear());
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.capacity());
				FUN_AFTER(v1, v1.reserve(5));
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.capacity());
				FUN_AFTER(v1, v1.reserve(20));
				FUN_VALUE(v1.size());
				FUN_VALUE(v1.capacity());
				PASSED;
				cout << "[------------------ Performance Testing ------------------]" << endl;
				cout << "|---------------|-------------|-------------|-------------|" << endl;
				cout << "|   push_back   |   1000000   |  10000000   |  100000000  |" << endl;
				cout << "|      std      |";
				VECTOR_PUSH_BACK_TEST(std, 1000000);
				VECTOR_PUSH_BACK_TEST(std, 10000000);
				VECTOR_PUSH_BACK_TEST(std, 100000000);
				cout << endl << "|     mystl     |";
				VECTOR_PUSH_BACK_TEST(mystl, 1000000);
				VECTOR_PUSH_BACK_TEST(mystl, 10000000);
				VECTOR_PUSH_BACK_TEST(mystl, 100000000);
				cout << endl;
				cout << "|---------------|-------------|-------------|-------------|" << endl;
				PASSED;
				cout << "[-------------- End container test : vector --------------]" << endl;
			}
		}
	}
}
#endif // !MYTINYSTL_VECTOR_TEST_H
