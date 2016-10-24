#include <stdio.h>
#include <string.h>
#include "../include/aqua/aqua.h"
#include <criterion/criterion.h>
#include <signal.h>

Test(a_string, cstr2s) {
    a_string s = a_cstr2s("hello");

    cr_assert(strcmp(s->data, "hello") == 0, "a_string is hello");
    cr_assert(s->len == 5, "length is 5");
    a_sdestroy(s);
}

Test(a_string_builder, sbldaddchar) {
    a_string_builder b;
    a_string s;
    char *cstr;

    b = a_sbldcreate();
    a_sbldaddchar(b, 'a');
    s = a_sbld2s(b);
    cstr = a_s2cstr(s);

    cr_assert(strcmp(cstr, "a") == 0, "check we can add a char to a_string builder");
    free(cstr);
}

Test(a_string_builder, sbldadds) {
    a_string_builder b;
    a_string s;
    a_string s2;
    char *cstr;

    b = a_sbldcreate();
    s = a_cstr2s("abc");
    a_sbldadds(b, s);
    s2 = a_sbld2s(b);
    cstr = a_s2cstr(s2);

    cr_assert(strcmp(cstr, "abc") == 0, "check we can add a a_string to a_string builder");
    free(cstr);    
}

Test(a_string_builder, sblddestroy)
{
    a_string_builder b;

    b = a_sbldcreate();
    a_sbldaddchar(b, 'x');
    a_sblddestroy(b);
}

Test(a_getline, test)
{
    FILE *fp;
    int has_term;
    a_string s;

    fp = fopen("../LICENSE", "r");

    cr_assert(fp, "should be able to open file");

    s = a_getline(fp, &has_term);
    cr_assert(has_term, "should have line termination character");
    cr_assert(strcmp(s->data, "GNU LESSER GENERAL PUBLIC LICENSE\n") == 0, "should get the first line");
    a_sdestroy(s);
}

Test(url_encode, test)
{
    char *str = "name=one&value=1&comment=what's up doc?";
    char *str2 = url_encode(str);
    char *str3;
    str3 = url_decode(str2);
    cr_assert(strcmp(str, str3) == 0, "check that decode matches original a_string");
    free(str2);
    free(str3);
}

Test(a_sbldaddmem, test)
{
    char *str = "hello";
    char *str2 = "my world";
    a_string_builder b = a_sbldcreate();
    a_string out;

    a_sbldaddcstr(b, str);
    a_sbldaddchar(b, ' ');
    a_sbldaddmem(b, &str2[3], 5);
    out = a_sbld2s(b);
    cr_assert(strcmp(out->data, "hello world") == 0, "check buffer added to a_string builder");
    a_sdestroy(out);
}

Test(nextPiece, 1)
{
    int pos = 0;
    a_string s, s1, s2, s3, s4, s5;

    s = a_cstr2s("one|two||four|");
    s1 = a_nextPiece(s, '|', &pos);
    s2 = a_nextPiece(s, '|', &pos);
    s3 = a_nextPiece(s, '|', &pos);
    s4 = a_nextPiece(s, '|', &pos);
    s5 = a_nextPiece(s, '|', &pos);

    cr_assert(strcmp(s1->data, "one") == 0, "check first piece is correct");
    cr_assert(strcmp(s2->data, "two") == 0, "check second piece is correct");
    cr_assert(strcmp(s3->data, "") == 0, "check third piece is correct");
    cr_assert(strcmp(s4->data, "four") == 0, "check fourth piece is correct");
    cr_assert(strcmp(s5->data, "") == 0, "check fifth piece is correct");
    cr_assert(pos == -1, "check that position is -1");

    a_sdestroy(s);
    a_sdestroy(s1);
    a_sdestroy(s2);
    a_sdestroy(s3);
    a_sdestroy(s4);
    a_sdestroy(s5);
}

Test(a_nextPiece, 2)
{
    int pos = 0;
    a_string s, s1, s2, s3;

    s = a_cstr2s("one|two|three");
    s1 = a_nextPiece(s, '|', &pos);
    s2 = a_nextPiece(s, '|', &pos);
    s3 = a_nextPiece(s, '|', &pos);

    cr_assert(strcmp(s1->data, "one") == 0, "check first piece is correct");
    cr_assert(strcmp(s2->data, "two") == 0, "check second piece is correct");
    cr_assert(strcmp(s3->data, "three") == 0, "check third piece is correct");
    cr_assert(pos == -1, "check that pos is -1");

    a_sdestroy(s);
    a_sdestroy(s1);
    a_sdestroy(s2);
    a_sdestroy(s3);
}

Test(a_hash_table, 1)
{
    a_string key = a_cstr2s("name");
    a_string value = a_cstr2s("han");
    a_string value2;
    a_hash_table table = a_htCreate(100);

    a_htSet(table, key, value);
    value2 = a_htGet(table, key);
    cr_assert(value2 == value, "Can set and get an item from hash table.");
    a_htDestroy(table);
}

Test(a_decodeForm, 1)
{
    a_string form = a_cstr2s("name=han%20solo&place=the%20galaxy");
    a_hash_table table = a_decodeForm(form);
    a_string name_key = a_cstr2s("name");
    a_string place_key = a_cstr2s("place");
    a_string name = a_htGet(table, name_key);
    a_string place = a_htGet(table, place_key);

    cr_assert(strcmp(name->data, "han solo") == 0, "Check name is solo");
    cr_assert(strcmp(place->data, "the galaxy") == 0, "Check place is galaxy");

    a_sdestroy(name_key);
    a_sdestroy(place_key);
    a_sdestroy(form);
    a_htDestroy(table);
}

Test(a_sqlformat, 1)
{
    a_string query = a_cstr2s("insert into user values (?, ?);");
    a_string error;
    a_string query2;
    a_string email = a_cstr2s("luke's@star");
    a_string password = a_cstr2s("the \"force\"");

    query2 = a_sqlformat(query, &error, email, password);
    cr_assert(strcmp(query2->data, "insert into user values ('luke''s@star', 'the \"force\"');") == 0, "check query format");
    a_sdestroy(query);
    a_sdestroy(query2);
    a_sdestroy(email);
    a_sdestroy(password);
}

Test(a_itoa, 1)
{
    a_string s;

    s = a_itoa(22);
    cr_assert(strcmp(s->data, "22") == 0, "check 22");
    a_sdestroy(s);

    s = a_itoa(-22);
    cr_assert(strcmp(s->data, "-22") == 0, "check -22");
    a_sdestroy(s);

    s = a_itoa(0);
    cr_assert(strcmp(s->data, "0") == 0, "check 0");
    a_sdestroy(s);

    s = a_itoa(100);
    cr_assert(strcmp(s->data, "100") == 0, "check 100");
    a_sdestroy(s);

    s = a_itoa(-100);
    cr_assert(strcmp(s->data, "-100") == 0, "check 100");
    a_sdestroy(s);

    s = a_itoa(1);
    cr_assert(strcmp(s->data, "1") == 0, "check 1");
    a_sdestroy(s);

    s = a_itoa(-1);
    cr_assert(strcmp(s->data, "-1") == 0, "check -1");
    a_sdestroy(s);
}

Test(a_GetTime, 1)
{
    a_string s = a_GetTime();
    printf("%s\n", s->data);
}