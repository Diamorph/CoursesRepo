#include <windows.h>
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka_pbc.h>
#include <cmocka.h>

#include "text.h"

static void create__new__text(void **text){
    text_t * tx = text_new();
    assert_int_equal(text_size(tx),0);
    text_remove(&tx);
}

static void add__Sentence__oneString(void **text){
	text_t * tx = text_new();
	text_add(tx,"Hello", 0);
	assert_int_equal(text_size(tx),1);
	text_remove(&tx);
}


static void add__Sentence__ErrorIndex(void **text){
	text_t * tx = text_new();
	text_add(tx,"Hello", 0);
	assert_int_equal(text_add(tx,"Hello", -423),WRONG_INDEX);
	text_remove(&tx);
}


static void add__Sentence__ThreeStringsAtTheSamePosition(void **text){
	text_t * tx = text_new();
	text_add(tx,"one", 0);
	text_add(tx,"one", 0);
	text_add(tx,"one", 0);
	assert_int_equal(text_size(tx),3);
	text_remove(&tx);
}


static void DelSentenceByIndex__Correct__Index(void **st){
	text_t * tx = text_new();
	text_add(tx,"one", 0);
	assert_int_equal(text_delete(tx, 0),OK);
	text_remove(&tx);
}


static void DelSentenceByIndex__CorrectIndex__CheckSize(void **text){
	text_t * tx = text_new();
	text_add(tx,"one", 0);
	text_delete(tx,0);
	assert_int_equal(text_size(tx),0);
	text_remove(&tx);
}


static void DelSentenceByIndex__ErrorIndex__putsIndexMoreThanSize(void **text){
	text_t * tx = text_new();
	assert_int_equal(text_delete(tx, 3),WRONG_INDEX);
	text_remove(&tx);
}


static void DelSentenceByIndex__ErrorIndex__putsIndexLessThanZero(void **text){
	text_t * tx = text_new();
	assert_int_equal(text_delete(tx, -213),WRONG_INDEX);
	text_remove(&tx);
}


static void Get__Words__Count(void **text){
	text_t *tx = text_new();
	text_add(tx,"Hello World", 0);
	text_add(tx,"three", 0);
	text_add(tx,"four", 0);
	assert_int_equal(text_word_count(tx), 4);
	text_remove(&tx);
}


static void AddSentences__DelSentenceByIndex__returnsWordsCount(void **text){
	text_t *tx = text_new();
	text_add(tx,"Hello World", 0);
	text_add(tx,"three four five", 1);
	text_add(tx,"six", 2);
	text_delete(tx,1);
	assert_int_equal(text_word_count(tx), 3);
	text_remove(&tx);
}


int main(void){
    const struct CMUnitTest tests[] =
    {
    cmocka_unit_test(create__new__text),
    cmocka_unit_test(add__Sentence__oneString),
    cmocka_unit_test(add__Sentence__ErrorIndex),
    cmocka_unit_test(add__Sentence__ThreeStringsAtTheSamePosition),
    cmocka_unit_test(DelSentenceByIndex__Correct__Index),
    cmocka_unit_test(DelSentenceByIndex__CorrectIndex__CheckSize),
    cmocka_unit_test(DelSentenceByIndex__ErrorIndex__putsIndexMoreThanSize),
    cmocka_unit_test(DelSentenceByIndex__ErrorIndex__putsIndexLessThanZero),
    cmocka_unit_test(Get__Words__Count),
    cmocka_unit_test(AddSentences__DelSentenceByIndex__returnsWordsCount),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
