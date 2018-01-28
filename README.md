# detect-combine-chars

A simple CLI command detects any `Mark` character of Unicode.

Detects like...

```console
$ ruby -e 'puts `echo "カレンダー\n濁点\nもんだい" | iconv -t utf-8-mac`.split("\n").grep(/\p{Combining_Mark}/)'
```

This receives standard input stream.
The command exits with non-zero when detects `Mark` characters.

```console
$ echo "カレンダー\n濁点\nもんだい" | iconv -t utf-8-mac | detect-combine-chars  # => non-zero exit and standard error output below
L:1	U+3099	カレンダー
L:3	U+3099	もんだい
```
