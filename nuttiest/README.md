# Nuttiest 

The nuttiest way to write unit tests in C++.

## Description
Nuttiest (an anagram for "unit test") is lightweight C++ framework for writing unit tests with simple comparisons. 
The syntax is inspired by Rust's syntax for unit testing. I made this for myself, but anyone may use it as he or she sees fit. Unit tests will run sequentially and are not suited to run in parallel at this time. 


## How to Integrate into a Project
- Must be using at least `C++11`.
- Add `#include "nuttiest.hpp"` to your unit tests file.  
- Add `using namespace nuttiest;`  (optional, but recommended)
- By default, `nuttiest` will output to `std::cout`.   
You can change this by modifying the `STREAM` definition at the top of `nuttiest.hpp`.  
- By default, `nuttiest` will print colored output using escape characters.
You can disable this by commenting out the `COLOR_OUTPUT` definition at the top of `nuttiest.hpp`.

## Quick Reference

### Example Syntax
```C++
#include "nuttiest.hpp"
#include <vector>

using namespace std;
using namespace nuttiest;

int main() {
    section("strings") {
        let x = "Hello world!";
        let y = "Hey there...";

        unit_test("greater than") {
            assert_gt(x, y)
        }
    }

    section("raw bytes") {
        let chars = vector<char>    { 'A', 'B', 'C', 'D' };
        let ints  = vector<uint8_t> {  65,  66,  67,  68 };

        unit_test("bytes are equal") {
            mem_eq(&chars[0], &ints[0], 4)
        }
    }

    section("exceptions") {
        let vec = vector<int> { 1, 2, 3, 4, 5 };

        // This test will only pass if an exception is thrown.
        // Computing, but ignoring other assertions or explicit pass/fails.
        unit_test("expect an exception") must_throw({
            assert_eq(1, 2);
            pass_test(); // Will not count
            fail_test("This will not count, either.");
            vec.at(8675309); // Will throw for Jenny.
        })

        // This test will act as normal, but will catch exceptions.
        unit_test("fail on an exception") may_throw({
            vec.at(8675309); // Will throw for Jenny.
            pass_test(); // Will never make it because of throw.
        })
    }

    return summary();
}
```

### Output

![Alt text](screenshots/example-output.png?raw=true "Output")

## API
---
**Description:** Prints a new section divider for a logical grouping of tests.  
```C++
section(const string& section_name)
```  

  
---
**Description:** Prints a summary of all passed and failed tests up to that point. 
```C++
summary()
```  
 
  
---
**Description:** Sets the current test name.
```C++
unit_test(const string& test_name)
``` 


  
---
**Description:** Enables exception handling. Test will fail if it throws.
```C++
may_throw({statements for test})
```  
**Syntax:**
```C++
unit_test("name of test") may_throw({
    assert_eq(class1, class2) // may throw exception.
})
```

  
---
**Description:** This test passes only if it throws an exception.
```C++
must_throw({statements for test})
```  
**Syntax:**
```C++
unit_test("name of test") must_throw({
    assert_eq(class1, class2) // This will be evaluated, but have no effect on the test result.
    throw(runtime_error("This test will pass"));
})
```
  
  
---
**Description:** Explicitly passes a test.
```C++
pass_test()
```  
  
  
---
**Description:** Explicitly fails a test. 
```C++
fail_test(const string& reason)
```
  
  
---
**Description:** Comparisons for any types. (Assumes proper operators overloaded)
```C++
assert_eq(const L& lhs, const R& rhs); // lhs == rhs
assert_lt(const L& lhs, const R& rhs); // lhs <  rhs
assert_gt(const L& lhs, const R& rhs); // lhs >  rhs
assert_ne(const L& lhs, const R& rhs); // lhs != rhs
assert_le(const L& lhs, const R& rhs); // lhs <= rhs
assert_ge(const L& lhs, const R& rhs); // lhs >= rhs
```
  
  
---
**Description:** Comparisons for raw memory. 
```C++
mem_eq(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs == rhs
mem_lt(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs <  rhs
mem_gt(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs >  rhs
mem_ne(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs != rhs
mem_le(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs <= rhs
mem_ge(void const * const lhs, void const * const rhs, const size_t& num_bytes); // lhs >= rhs
```
