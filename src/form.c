#include <aqua/string_builder.h>
#include <aqua/util.h>
#include <aqua/hash_table.h>

a_hash_table a_decodeForm(a_string s)
{
  int pos = 0;
  a_hash_table table = a_htCreate(20);

  while (pos >= 0) {
    a_string pair;
    pair = a_nextPiece(s, '&', &pos);
    if (pair->len > 0) {
      a_string name;
      a_string value;
      int pos2 = 0;
      name = a_nextPiece(pair, '=', &pos2);
      value = a_nextPiece(pair, '=', &pos2);

      if (name->len > 0 && value) {
        a_string name2 = a_cstr2s(url_decode(name->data));
        a_string value2 = a_cstr2s(url_decode(value->data));
        a_htSet(table, name2, value2);
      }

      a_sdestroy(name);
      a_sdestroy(value);
    }
    a_sdestroy(pair);
  }

  return table;
}