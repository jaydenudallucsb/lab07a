#include <iostream>
#include <sstream>
#include "WordCount.h" 
#include "tddFuncs.h"
using namespace std;

// Test addAllWords
void testAddAllWords() {
    WordCount wc;
    wc.addAllWords("Sentence is a sentence");

    assertEquals("2", std::to_string(wc.getWordCount("sentence")),
                 "Check count for 'sentence'", __LINE__);
    assertEquals("1", std::to_string(wc.getWordCount("is")),
                 "Check count for 'is'", __LINE__);
    assertEquals("1", std::to_string(wc.getWordCount("a")),
                 "Check count for 'a'", __LINE__);
    assertTrue(wc.getWordCount("nonexistent") == 0,
               "Check nonexistent word count", __LINE__);
}

// Test dumpWordsSortedByWord
void testDumpWordsSortedByWord() {
    WordCount wc;
    wc.addAllWords("Sentence is a sentence");
    std::ostringstream out;
    wc.dumpWordsSortedByWord(out);

    std::string expected = "sentence,2\nis,1\na,1\n";
    assertEquals(expected.c_str(), out.str().c_str(),
                 "Check words sorted by word in descending order", __LINE__);
}

// Test dumpWordsSortedByOccurence
void testDumpWordsSortedByOccurence() {
    WordCount wc;
    wc.addAllWords("Sentence is a fun fun sentence");
    std::ostringstream out;
    wc.dumpWordsSortedByOccurence(out);

    std::string expected = "a,1\nis,1\nfun,2\nsentence,2\n";
    assertEquals(expected.c_str(), out.str().c_str(),
                 "Check words sorted by occurrence (ascending)", __LINE__);
}

// Test makeValidWord
void testMakeValidWord() {
    WordCount wc;
    assertEquals("word", wc.makeValidWord("word"),
                 "Check valid word without punctuation", __LINE__);
    assertEquals("it's", wc.makeValidWord("It's"),
                 "Check valid word with apostrophe", __LINE__);
    assertEquals("co-operate", wc.makeValidWord("Co-operate"),
                 "Check valid hyphenated word", __LINE__);
    assertEquals("", wc.makeValidWord("1234"),
                 "Check invalid word with numbers", __LINE__);
    assertEquals("test", wc.makeValidWord("@Test!"),
                 "Check valid word with special characters", __LINE__);
}

// Test incrWordCount
void testIncrWordCount() {
    WordCount wc;
    wc.incrWordCount("word");
    assertEquals("1", std::to_string(wc.getWordCount("word")),
                 "Increment count for 'word' (initially 0)", __LINE__);
    wc.incrWordCount("word");
    assertEquals("2", std::to_string(wc.getWordCount("word")),
                 "Increment count for 'word' again", __LINE__);
}

// Test decrWordCount
void testDecrWordCount() {
    WordCount wc;
    wc.incrWordCount("word");
    wc.incrWordCount("word");
    assertEquals("1", std::to_string(wc.decrWordCount("word")),
                 "Decrement count for 'word'", __LINE__);
    assertEquals("0", std::to_string(wc.decrWordCount("word")),
                 "Decrement count for 'word' to 0 (removes word)", __LINE__);
    assertEquals("-1", std::to_string(wc.decrWordCount("word")),
                 "Decrement count for non-existent word", __LINE__);
}

// Test getNumUniqueWords
void testGetNumUniqueWords() {
    WordCount wc;
    wc.addAllWords("This is a test");
    assertEquals("4", std::to_string(wc.getNumUniqueWords()),
                 "Check unique word count", __LINE__);
    wc.addAllWords("This is a test again");
    assertEquals("5", std::to_string(wc.getNumUniqueWords()),
                 "Check unique word count after adding a new word", __LINE__);
}

// Test getTotalWords
void testGetTotalWords() {
    WordCount wc;
    wc.addAllWords("Sentence is a fun fun sentence");
    assertEquals("6", std::to_string(wc.getTotalWords()),
                 "Check total word count", __LINE__);
}

int main() {
    cout << "Running tests...\n";

    testAddAllWords();
    testDumpWordsSortedByWord();
    testDumpWordsSortedByOccurence();
    testMakeValidWord();
    testIncrWordCount();
    testDecrWordCount();
    testGetNumUniqueWords();
    testGetTotalWords();

    cout << "All tests completed.\n";
    return 0;
}
