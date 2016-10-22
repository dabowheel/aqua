#include <aqua/string_builder.h>
#include <aqua/util.h>
#include <aqua/hash_table.h>

a_hash_table a_decodeForm(a_string s)
{
  a_string pair;
  a_string name;
  a_string value;
  char *str;
  char *str2;
  int pos = 0;
  a_hash_table table = a_htCreate(20);

  while (pos >= 0) {
    int pos2 = 0;
    pair = a_nextPiece(s, '&', &pos);
    if (pair->len > 0) {
      name = a_nextPiece(pair, '=', &pos2);
      value = a_nextPiece(pair, '=', &pos2);

      if (name->len > 0 && value) {
        str = a_s2cstr(name);
        str2 = url_decode(str);
        name = a_cstr2s(str2);
        free(str);
        free(str2);

        str = a_s2cstr(value);
        str2 = url_decode(str);
        value = a_cstr2s(str2);
        free(str);
        free(str2);

        a_htSet(table, name, value);
      }
      a_sdestroy(name);
      a_sdestroy(value);
    }
    a_sdestroy(pair);
  }

  return table;
}