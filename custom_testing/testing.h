#include <vector>
#include <cstdlib>
#include <iostream>
#include <assert.h>


namespace testing {

class Testable;

std::vector<Testable*> test_cases;




class Testable {
  public:
    Testable() { test_cases.push_back(this); }
    virtual ~Testable() = default;
    bool RunTest() { Test(); return !failed; }
  protected:
    
    virtual void Test() = 0;
    bool failed = false;

    bool check(bool condition, 
               std::string expr, 
               std::string filename, 
               std::string funcname, 
               int line) {
        if (!condition){
            failed = true;
            std::cerr << "Assert failed! " 
              << expr << " in " 
              << filename << ":" 
              << line << " " << funcname << "\n";
       }
       return condition;
   }
};

}

#define TEST(TestCase) \
class TestCase : public ::testing::Testable { \
private: \
  void Test() override; \
}; \
namespace testing##TestCase { \
::TestCase test; \
} \
void TestCase::Test()

#define ASSERT(x) if (!testing::Testable::check(x, #x, __FILE__, __FUNCTION__, __LINE__)) return;

#define RUN_ALL_TESTS \
{ \
  int failed = 0; \
  const int test_cnt = ::testing::test_cases.size(); \
  for (auto t : ::testing::test_cases) \
    if (!t->RunTest()) failed++;  \
  \
  std::cerr << "test passed: " << test_cnt - failed << "/" << test_cnt << std::endl; \
  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE; \
}
