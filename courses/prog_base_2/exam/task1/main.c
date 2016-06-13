#include <windows.h>
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka_pbc.h>
#include <cmocka.h>

#include "test.h"

// unit-test function

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


static void Get__Words__CountWithCharacter(void **text){
	text_t *tx = text_new();
	text_add(tx,"124fg", 0);
	assert_int_equal(text_word_count(tx), 0);
	text_remove(&tx);
}

static void Get__Words__CountWithPoint(void **text){
	text_t *tx = text_new();
	text_add(tx,"35.5", 0);
	assert_int_equal(text_word_count(tx), 1);
	text_remove(&tx);
}

static void Get__Words__CountFiveNumbers(void **text){
	text_t *tx = text_new();
	text_add(tx,"3 2 3 4 5", 0);
	assert_int_equal(text_word_count(tx), 5);
	text_remove(&tx);
}

static void Get__Words__CountWithSomeExtraCharacter(void **text){
	text_t *tx = text_new();
	text_add(tx,"124 5345fds", 0);
	assert_int_equal(text_word_count(tx), 1);
	text_remove(&tx);
}

int main(void) {
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
    cmocka_unit_test(Get__Words__CountWithCharacter),
    cmocka_unit_test(Get__Words__CountWithPoint),
    cmocka_unit_test(Get__Words__CountFiveNumbers),
    cmocka_unit_test(Get__Words__CountWithSomeExtraCharacter),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
