#include <stlport/algorithm>
#include <stlport/cstring>
#include <stlport/vector>
#include <stlport/iterator>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class CopyTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(CopyTest);
  CPPUNIT_TEST(copy_array);
  CPPUNIT_TEST(copy_vector);
  CPPUNIT_TEST(copy_insert);
  CPPUNIT_TEST(copy_back);
  CPPUNIT_TEST(copy_back_array);
  CPPUNIT_TEST_SUITE_END();

protected:
  void copy_array();
  void copy_vector();
  void copy_insert();
  void copy_back();
  void copy_back_array();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CopyTest);

//
// tests implementation
//
void CopyTest::copy_array()
{
  char string[23] = "A string to be copied.";
  char result[23];
  copy(string, string + 23, result);
  CPPUNIT_ASSERT(!strncmp(string, result, 23));
}

void CopyTest::copy_vector()
{
  vector<int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;

  vector<int> v2(v1.size());
  copy(v1.begin(), v1.end(), v2.begin());

  CPPUNIT_ASSERT( v2 == v1 );
}

void CopyTest::copy_insert() {
  vector<int> v1(10);
  for (int loc = 0; (size_t)loc < v1.size(); ++loc)
    v1[loc] = loc;
  vector<int> v2;
  insert_iterator<vector<int> > i(v2, v2.begin());
  copy(v1.begin(), v1.end(), i);

  CPPUNIT_ASSERT( v2 == v1 );
}

void CopyTest::copy_back()
{
  vector<int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;
  vector<int> v2(v1.size());
  copy_backward(v1.begin(), v1.end(), v2.end());

  CPPUNIT_ASSERT( v2 == v1 );
}

void CopyTest::copy_back_array()
{
  int numbers[5] = { 1, 2, 3, 4, 5 };

  int result[5];
  copy_backward(numbers, numbers + 5, (int*)result + 5);
  CPPUNIT_ASSERT(result[0]==numbers[0]);
  CPPUNIT_ASSERT(result[1]==numbers[1]);
  CPPUNIT_ASSERT(result[2]==numbers[2]);
  CPPUNIT_ASSERT(result[3]==numbers[3]);
  CPPUNIT_ASSERT(result[4]==numbers[4]);
}