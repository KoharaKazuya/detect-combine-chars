#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markchars.h"

int main()
{
    int detected = 0;
    uint32_t mark_chars[] = { MARK_CHARS };
    int num_of_mark_chars = sizeof(mark_chars) / sizeof(uint32_t);
    char *c, *l;
    uint32_t unicode_codepoint;
    int remain, i, line_no;
    char *line;
    size_t line_len;

    unicode_codepoint = 0;
    remain = 0;
    line_no = 0;
    while ((line = fgetln(stdin, &line_len)) != NULL)
    {
        ++line_no;

        c = line;
        while (c < line + line_len)
        {
            if ((*c & 0x80) == 0)
            {
                unicode_codepoint = *c;
            }
            else if ((*c & 0xE0) == 0xC0)
            {
                unicode_codepoint = *c & 0x1F;
                remain = 1;
            }
            else if ((*c & 0xF0) == 0xE0)
            {
                unicode_codepoint = *c & 0x0F;
                remain = 2;
            }
            else if ((*c & 0xF8) == 0xF0)
            {
                unicode_codepoint = *c & 0x07;
                remain = 3;
            }
            else if ((*c & 0xFC) == 0xF8)
            {
                unicode_codepoint = *c & 0x03;
                remain = 4;
            }
            else if ((*c & 0xFE) == 0xFC)
            {
                unicode_codepoint = *c & 0x01;
                remain = 5;
            }
            else if ((*c & 0xC0) == 0x80)
            {
                unicode_codepoint <<= 6;
                unicode_codepoint |= *c & 0x3F;
                --remain;
            }
            else
            {
                fprintf(stderr, "Invalid UTF-8 sequence\n");
                return 1;
            }

            if (remain <= 0)
            {
                remain = 0;

                for (i=0; i<num_of_mark_chars; ++i)
                {
                    if (unicode_codepoint == mark_chars[i]) {
                        l = calloc(line_len, sizeof(char));
                        strncpy(l, line, line_len-1);
                        printf("L:%d\tU+%x\t%s\n", line_no, unicode_codepoint, l);
                        free(l);
                        detected = 1;
                    }
                }
            }

            ++c;
        }
    }

    return detected;
}
