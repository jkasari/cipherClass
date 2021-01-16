#ifndef CIPHER_CLASSES_H
#define CIPHER_CLASSES_H
#include <iostream>

class vigenereCipher {

 public:
  /**
   * This deletes the default copy assingment operator given to us by c++.
   */
  //vigenereCipher& operator=(const vigenereCipher&) = delete;
  vigenereCipher& operator=(const vigenereCipher&);
  vigenereCipher(const char*);
  vigenereCipher(const vigenereCipher&);
  ~vigenereCipher();
  /**
   * Encrypts the characters of |str|.
   */
  void encrypt(char* const str);

  /**
   * Creates a copy of |str| and encrypts it.
   * The caller is responsible for deleting the new string.
   */
  char* encrypt(const char* str);

  /**
   * Decrypts the characters of |str|.
   */
  void decrypt(char* const str);

  /**
   * Creates a copy of |str| and decrypts it.
   * The caller is responsible for deleting the new string.
   */
  char* decrypt(const char*);

 private:
  char* key = nullptr;
  static const uint32_t ALPHABET_SIZE = 28;
  static constexpr char ALPHABET[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  void allocate(size_t);
  uint32_t indexOf(const char);
  bool isInAlphabet(const char*);
  char shiftRight(const uint32_t, char);
  char shiftLeft(const uint32_t, char);

};


class caeserCipher {

 public:
  caeserCipher& operator=(const caeserCipher&) = delete;
  caeserCipher(const uint64_t);

  /**
  * Encrypts a string by moving each char to the right using |charShiftRight|.
  */
  void encrypt(char* const);

  /**
   * Creates a copy of |str| and encrypts it.
   * The caller is responsible for deleting the new string.
   */
  char* encrypt(const char*);

  /**
  * Decrypts a string by moving each char to the left using |charShiftLeft|.
  */
  void decrypt(char* const);

  /**
   * Creates a copy of |str| and decrypts it.
   * The caller is responsible for deleting the new string.
   */
  char* decrypt(const char*);

 private:
  uint64_t key;
  static const int32_t ALPHABET_SIZE = 28;
  static constexpr char ALPHABET[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  void allocate();
  /**
  * Takes a char and returns the index + 1 of the matching char in |ALPHABET|.
  * This function returns a 0 if the character is not in |ALPHABET|.
  */
  uint32_t indexOf(const char);
  /**
  * Takes a char and moves it along the |ALPHABET| to the right.
  */
  char shiftRight(char);
  /**
  * Takes a char and moves it along the |ALPHABET| to the left.
  */
  char shiftLeft(char);

};

#endif // CIPHER_CLASSES_H
