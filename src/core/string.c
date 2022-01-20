#include "core/string.h"

String *string_init(const char *str)
{
    String *self = memory_allocate(sizeof *self);
    memset(self, 0, sizeof *self);
    self->object_super = object_init("String", STRING);
    assert(self);
    
    self->len = TextLength(str);
    self->str = memory_allocate(str, sizeof *self->str * self->len);
    assert(self->str);
    TextCopy(self->str, str); 

    string_bindfuncs(self);
    return self;
}

void print(const String *str, ...)
{
    printf("%s\n", str->str);
}

/****************************************************************************/
/*                                   Private Functions.                     */
/****************************************************************************/

static void string_bindfuncs(String *const self)
{
    self->to_upper = string_to_upper;
    self->to_lower = string_to_lower;
    self->is_equal = string_is_equal;
    self->starts_with_space = string_starts_with_space;
    self->del = string_del;
}

static bool string_is_equal(const String *self, const String *str)
{
    return TextIsEqual(self->str, str->str);
}

static String *string_to_upper(const String *self)
{
    return TextToUpper(self->str);
}    

static String *string_to_lower(const String *self)
{
    const char *str = TextToLower(self->str);
    return string_init(str);
}

static string_del(String *self)
{
    puts("Deleting string...");
    self->object_super->del(self->object_super);
    memory_release(self->str);
    memory_release(self);
    puts("Deleting string... Done!");
}

static bool string_starts_with_space(const char *_s)
{
    return _s[0] == ' ' ? true : false;
}

static bool string_is_empty(const char *_s)
{
    return TextLength(_s) ? true : false;
}

const char *string_fmt(const char *_s, ...)
{
    va_list args;
    va_start(args, _s);

    const char *buf = NULL;
    int n = vsnprintf(NULL, 0, _s, args);
    
    va_end(args);
    
    if (n >= 0)
    {
        va_start(args, _s);
        buf = memory_allocate((void *)buf, n + 1);
        if (buf)
            vsnprintf(buf, n + 1, _s, args);
        va_end(args);
    }
    
    return buf;
}