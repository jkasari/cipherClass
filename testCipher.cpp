#include <iostream>
#include "nuttiest/nuttiest.hpp"
#include "cipherClasses.h"

using namespace std;
using namespace nuttiest;

int main() {

  vigenereCipher cipher1("FISH");
  cout << cipher1.encrypt("BLACKMAGIC") << endl;
  cout << cipher1.decrypt("GTSJPUSNNK") << endl;

  cout << "====================" << endl;

  caeserCipher cipher(1);
  cout << cipher.encrypt("BLACKMAGIC") << endl;
  cout << cipher.decrypt("CMBDLNBHJD") << endl;


  //section("test") {
  //  unit_test("testCase") {
  //    assert_eq(true, false);
  //  }
  //}

  //summary();

}
