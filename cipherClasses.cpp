#include "cipherClasses.h"


/**
 * Takes a |key| and stores it in the class
 */
vigenereCipher::vigenereCipher(const char* keyToBe) {
  if (!keyToBe) {
    return;
  }
  keySize = strlen(keyToBe);
  allocate(keySize);
  for(int i = 0; i < keySize; ++i) {
    key[i] = indexOf(keyToBe[i] - 1);
  }
}

vigenereCipher::vigenereCipher(const vigenereCipher& other) {
  keySize = other.keySize;
  allocate(keySize);
  for(int i = 0; i < keySize; ++i) {
    key[i] = other.key[i];
  }
}



/**
 * deletes the |key| off of the heap
 */
vigenereCipher::~vigenereCipher() {
  if (key || rawKey) {
    delete[] rawKey;
    rawKey = nullptr;

    delete[] key;
    key = nullptr;
  }
}

/**
 * allocates a new spot on the heap for a vigenereCipher |key|
 */
void vigenereCipher::allocate(size_t length) {
  rawKey = new char[length + 1];
  rawKey[0] = '\0';

  key = new uint32_t[length];
}

/**
 * Takes a char and returns the index + 1 of the matching char in |ALPHABET|.
 * This function returns a 0 if the character is not in |ALPHABET|.
 */
uint32_t vigenereCipher::indexOf(const char c) {
  for (int32_t i = 0; i < ALPHABET_SIZE; ++i) {
    if (c == ALPHABET[i]) {
      return i + 1;
    }
  }
  return 0;
}

/**
 * This function uses |indexOf| to tell if the char is on |ALPHABET|. It takes
 * a string and runs each char through |indexOf| if it gets a zero on any char
 * it returns false.
 */
bool vigenereCipher::isInAlphabet(const char* str) {
  for (int i = 0; i < strlen(str); ++i) {
    if (indexOf(str[i]) == 0) {
      return false;
    }
  }
  return true;
}

/**
 * Takes a char and moves it along the |ALPHABET| to the right.
 * The |key| dictates how much it moves the char's in |str|.
 */

char vigenereCipher::shiftRight(const uint32_t key, char charToShift) {
  char shiftedChar = indexOf(charToShift) + (key % ALPHABET_SIZE);
  if (shiftedChar >= ALPHABET_SIZE) {
    shiftedChar -= (ALPHABET_SIZE - 1);
  }
  return ALPHABET[shiftedChar - 1];}

/**
 * Takes a char and moves it along the |ALPHABET| to the left.
 * The |key| dictates how much it moves the char's in |str|.
 */
char vigenereCipher::shiftLeft(const uint32_t key, char charToShift) {
  char shiftedChar = indexOf(charToShift) - (key % ALPHABET_SIZE);
  if (shiftedChar < 1) {
    shiftedChar += (ALPHABET_SIZE - 1);
  }
  return ALPHABET[shiftedChar - 1];
}

/**
 * cycles through a |key| for the length of |str|. It then shifts
 * each character according to what value is in |key| on that cycle.
 */
void vigenereCipher::encrypt(char* const str, const uint32_t keyIndex) {
  if(*str == '\0') {
    return;
  }
  *str = shiftRight(key[keyIndex % keySize], *str);
  encrypt(str + 1, keyIndex + 1);
}


void vigenereCipher::encrypt(char* const str) {
  if(!str) {
    return;
  }
  uint32_t keyIndex = keySize;
  encrypt(str, keyIndex);
}


/**
 * Finds a new spot on the heap for the new encrypted string the function returns.
 */
char* vigenereCipher::encrypt(const char* str) {
  if(!str) {
    return nullptr;
  }
  char* encrypted = new char[strlen(str) + 1];
  strcpy(encrypted, str);
  encrypt(encrypted);
  return encrypted;
}

/**
 * cycles through a vector of ints |key| for the length of |str|. It then shifts
 * each character according to what value is in |key| on that cycle.
 */
void vigenereCipher::decrypt(char* const str, const uint32_t keyIndex) {
  if(*str == '\0') {
    return;
  }
  *str = shiftLeft(key[keyIndex % keySize], *str);
  decrypt(str + 1, keyIndex + 1);
}

void vigenereCipher::decrypt(char* const str) {
  if(!str) {
    return;
  }
  uint32_t keyIndex = keySize;
  decrypt(str, keyIndex);
}

/**
 * Finds a new spot on the heap for the new encrypted string the function returns.
 */
char* vigenereCipher::decrypt(const char* str) {
  if(!str) {
    return nullptr;
  }
  char* decrypted = new char[strlen(str) + 1];
  strcpy(decrypted, str);
  decrypt(decrypted);
  return decrypted;
}

//=======================================================================================


caeserCipher::caeserCipher(const uint64_t keyToBe) {
  if(!keyToBe) {
    return;
  }
  key = keyToBe;
}


uint32_t caeserCipher::indexOf(const char c) {
  for (int32_t i = 0; i < ALPHABET_SIZE; ++i) {
    if (c == ALPHABET[i]) {
      return i + 1;
    }
  }
  return 0;
}

char caeserCipher::shiftRight(char charToShift) {
  char shiftedChar = indexOf(charToShift) + (key % ALPHABET_SIZE);
  if (shiftedChar >= ALPHABET_SIZE) {
    shiftedChar -= (ALPHABET_SIZE - 1);
  }
  return ALPHABET[shiftedChar - 1];
}

char caeserCipher::shiftLeft(char charToShift) {
  char shiftedChar = indexOf(charToShift) - (key % ALPHABET_SIZE);
  if (shiftedChar < 1) {
    shiftedChar += (ALPHABET_SIZE - 1);
  }
  return ALPHABET[shiftedChar - 1];
}

///**
// * Goes through a string and shifts each char over using |shiftRight|.
// */
void caeserCipher::encrypt(char* const str) {
  if(*str == '\0') {
    return;
  }
  *str = shiftRight(*str);
  encrypt(str + 1);
}

/**
 * Same thing as encrypt, only this makes it's own string on the heap.
 * The caller is responsible for this memory.
 */
char* caeserCipher::encrypt(const char* str) {
  if(!str) {
    return nullptr;
  }
  char* encrypted = new char[strlen(str) + 1];
  strcpy(encrypted, str);
  encrypt(encrypted);
  return encrypted;
}

/**
 * Goes through a string and shifts each char left using |shiftLeft|.
 */
void caeserCipher::decrypt(char* const str) {
  if(*str == '\0') {
    return;
  }
  *str = shiftLeft(*str);
  decrypt(str +1);
}

/**
 * Same thing as decrypt, only this makes it's own string on the heap.
 * The caller is responsible for this memory.
 */
char* caeserCipher::decrypt(const char* str) {
  if(!str) {
    return nullptr;
  }
  char* decrypted = new char[strlen(str) + 1];
  strcpy(decrypted,str);
  decrypt(decrypted);
  return decrypted;
}