#include <iostream>
#include "nuttiest/nuttiest.hpp"
#include "cipherClasses.h"

using namespace std;
using namespace nuttiest;

int main() {

  vigenereCipher cipher1("FISH");
  vigenereCipher cipher2(cipher1);
  cout << cipher2.encrypt("BLACKMAGIC") << endl;
  cout << cipher2.decrypt("GTSJPUSNNK") << endl;

  cout << "====================" << endl;

  caeserCipher cipher3(1);
  caeserCipher cipher4(cipher3);
  cout << cipher4.encrypt("BLACKMAGIC") << endl;
  cout << cipher4.decrypt("CMBDLNBHJD") << endl;


  //section("test") {
  //  unit_test("testCase") {
  //    assert_eq(true, false);
  //  }
  //}

  //summary();

}
