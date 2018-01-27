
.PHONY: build
build: main.c markchars.h
	clang -o detect-combine-chars -O -Wall main.c

# @see https://www.slideshare.net/reflectresults/macos-86746675
markchars.h:
	@curl -sSLf 'http://www.unicode.org/Public/5.2.0/ucd/PropList.txt' \
	| grep -E 'Mn|Mc|Me' \
	| sed -E 's/^/0x/;s/\.\./&0x/' \
	| awk -F'.' \
		'$$3==""{print $$0+0} $$3!=""{for(a=$$1;a<=$$3;a++)print a+0}' \
	| sort -n \
	| awk 'BEGIN{printf "#define MARK_CHARS "} {printf("0x%08x,",$$0)}' \
	> markchars.h

.PHONY: clean
clean:
	rm -f detect-combine-chars markchars.h
