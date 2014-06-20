#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mk_lua_multipart_to_table(char *boundary,
                               char *data)
{printf("\n%s\n", data);
  char *value, *key, *filename;
  char *start = data, *end = 0, *crlf = 0;
  unsigned long int vlen = 0;
  unsigned int len = 0;
  len = strlen(boundary);
  int t;
  start = strstr(data, boundary); /* start points to the first
                                     boundary */
  int i = 0;
  while(start) {
    //    printf("\niter no: %d",i++);
    //    printf("\n### start: %s####\n", start);
    end = strstr((char *) (start + 1), boundary);
    /* find the next boundary and store it in end*/
    if (end == NULL) break;            /* if no boundary, we have parsed
                                          form data */
    crlf = strstr((char *) start, "\r\n\r\n");
    if (!crlf) break;           /* there's no data */
    key = (char *) calloc(256,1);
    filename = (char *) calloc(256,1);
    vlen = end - crlf - 8;
    value = (char *) calloc(vlen+1,1);
    memcpy(value, crlf + 4, vlen);
    sscanf(start + len + 2,
           "Content-Disposition: form-data; name=\"%255[^\"]\"; filename=\"%255[^\"]\"",
           key, filename);
    printf("\n%s : %s \n", key, value);


    free(value);
    free(key);
    free(filename);
    start = end;
    //    printf("\n### end: %s####\n", end);    
    
  }
}

int main()
{
  char *boundary="----------0xKhTmLbOuNdArY";
  char *form ="------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"hgsid\"\r\n"
    "\r\n"
    "63932244\r\n"
    "------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"org\"\r\n"
    "\r\n"
    "Human\r\n"
    "------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"db\"\r\n"
    "\r\n"
    "hg17\r\n"
    "------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"type\"\r\n"
    "\r\n"
    "BLAT's guess\r\n"
    "------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"sort\"\r\n"
    "\r\n"
    "query,score\r\n"
    "------------0xKhTmLbOuNdArY\r\n"
    "Content-Disposition: form-data; name=\"output\"\r\n"
    "\r\n"
    "hyperlink\r\n"
    "------------0xKhTmLbOuNdArY\r\n";

  mk_lua_multipart_to_table(boundary, form);
  return 0;
}
