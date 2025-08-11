#include "inc\lwsc_types.h"

char lwsc_isdigit(char c) { return (c >= '0' && c <= '9'); }
char lwsc_isspace(char c) { return (c == ' ' || c == '\t'); }
char lwsc_isseparator(char c) { return (c == '.' || c == ','); }
char lwsc_isparenthesis(char c) { return (c == '(' || c == ')'); }