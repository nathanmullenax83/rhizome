all: rhizome

INCL = -Iinclude
LIBD = -Llib
SRC  = include
STD  = -std=c++1z
WARN = -Werror -Wall -Wextra -pedantic
OPTIMIZE = 
CC   = c++ $(WARN) $(STD) $(LIBD) $(INCL) $(OPTIMIZE) -ggdb

# lexer component


build/lex-token.o: $(SRC)/lex/token.cpp $(SRC)/lex/token.hpp
	$(CC) -c $(SRC)/lex/token.cpp -o build/lex-token.o

build/lex-token-queue.o: $(SRC)/lex/token_queue.cpp $(SRC)/lex/token_queue.hpp
	$(CC) -c $(SRC)/lex/token_queue.cpp -o build/lex-token-queue.o

build/lex-char-queue.o: $(SRC)/lex/char_queue.cpp $(SRC)/lex/char_queue.hpp
	$(CC) -c $(SRC)/lex/char_queue.cpp -o build/lex-char-queue.o

build/lex-stream-queue.o: $(SRC)/lex/stream_queue.cpp $(SRC)/lex/stream_queue.hpp $(SRC)/core/i_programmable.hpp
	$(CC) -c $(SRC)/lex/stream_queue.cpp -o build/lex-stream-queue.o

build/lex-lexer.o: $(SRC)/lex/lexer.cpp $(SRC)/lex/lexer.hpp
	$(CC) -c $(SRC)/lex/lexer.cpp -o build/lex-lexer.o

LEXER_OBJECTS = build/lex-lexer.o build/lex-token.o build/lex-char-queue.o build/lex-stream-queue.o build/lex-token-queue.o

lib/liblex.a: $(LEXER_OBJECTS)
	ar scr lib/liblex.a $(LEXER_OBJECTS)

# interprocess communication

build/ipc.o: $(SRC)/ipc/ipc.cpp $(SRC)/ipc/ipc.hpp
	$(CC) -c $(SRC)/ipc/ipc.cpp -lrt -o build/ipc.o

IPC_OBJECTS = build/ipc.o

lib/libipc.a: $(IPC_OBJECTS)
	ar scr lib/libipc.a $(IPC_OBJECTS)

# user interface library
build/ui.o: $(SRC)/ui/ui.cpp $(SRC)/ui/ui.hpp
	$(CC) -c $(SRC)/ui/ui.cpp -o build/ui.o

build/ui-menu.o: $(SRC)/ui/menu.cpp $(SRC)/ui/menu.hpp
	$(CC) -c $(SRC)/ui/menu.cpp -o build/ui-menu.o

build/ui-console.o: $(SRC)/ui/console.cpp $(SRC)/ui/console.hpp
	$(CC) -c $(SRC)/ui/console.cpp -o build/ui-console.o

build/ui-aa-context.o: $(SRC)/ui/aa_context.cpp $(SRC)/ui/aa_context.hpp
	$(CC) -c $(SRC)/ui/aa_context.cpp -laalib1 -o build/ui-aa-context.o

build/ui-screen-region.o: $(SRC)/ui/screen_region.cpp $(SRC)/ui/screen_region.hpp
	$(CC) -c $(SRC)/ui/screen_region.cpp -o build/ui-screen-region.o

UI_OBJECTS = build/ui.o build/ui-menu.o build/ui-console.o build/ui-aa-context.o build/ui-screen-region.o

lib/libui.a: $(UI_OBJECTS)
	ar scr lib/libui.a $(UI_OBJECTS)


# logic
build/logic.o: $(SRC)/logic/logic.cpp $(SRC)/logic/logic.hpp
	$(CC) -c $(SRC)/logic/logic.cpp -o build/logic.o

LOGIC_OBJECTS = build/logic.o

lib/liblogic.a: $(LOGIC_OBJECTS)
	ar scr lib/liblogic.a $(LOGIC_OBJECTS)

# type library

build/types.o: $(SRC)/types/types.cpp $(SRC)/types/types.hpp
	$(CC) -c $(SRC)/types/types.cpp -o build/types.o

build/types-integer.o: $(SRC)/types/integer.cpp $(SRC)/types/integer.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/types/integer.cpp -o build/types-integer.o

build/types-string.o: $(SRC)/types/string.cpp $(SRC)/types/string.hpp
	$(CC) -c $(SRC)/types/string.cpp -o build/types-string.o

build/types-time.o: $(SRC)/types/time.cpp $(SRC)/types/time.hpp
	$(CC) -c $(SRC)/types/time.cpp -o build/types-time.o

build/types-float.o: $(SRC)/types/float.cpp $(SRC)/types/float.hpp
	$(CC) -c $(SRC)/types/float.cpp -o build/types-float.o 

build/types-fraction.o: $(SRC)/types/fraction.cpp $(SRC)/types/fraction.hpp
	$(CC) -c $(SRC)/types/fraction.cpp -o build/types-fraction.o

build/types-uuid.o: $(SRC)/types/uuid.cpp $(SRC)/types/uuid.hpp
	$(CC) -c $(SRC)/types/uuid.cpp -o build/types-uuid.o

build/types-color.o: $(SRC)/types/color.cpp $(SRC)/types/color.hpp
	$(CC) -c $(SRC)/types/color.cpp -o build/types-color.o

build/types-image.o: $(SRC)/types/image.cpp $(SRC)/types/image.hpp
	$(CC) -c $(SRC)/types/image.cpp `libpng-config --ldflags` -lFreeImage -lFreeImagePlus -o build/types-image.o

build/types-tuple.o: $(SRC)/types/tuple.cpp $(SRC)/types/tuple.hpp
	$(CC) -c $(SRC)/types/tuple.cpp -obuild/types-tuple.o

build/types-table.o: $(SRC)/types/table.cpp $(SRC)/types/table.hpp
	$(CC) -c $(SRC)/types/table.cpp -o build/types-table.o

build/types-char.o: $(SRC)/types/char.cpp $(SRC)/types/char.hpp
	$(CC) -c $(SRC)/types/char.cpp -o build/types-char.o

build/types-bool.o: $(SRC)/types/bool.cpp $(SRC)/types/bool.hpp
	$(CC) -c $(SRC)/types/bool.cpp -o build/types-bool.o

build/types-enumeration.o: $(SRC)/types/enumeration.cpp $(SRC)/types/enumeration.hpp
	$(CC) -c $(SRC)/types/enumeration.cpp -o build/types-enumeration.o

build/types-dir.o: $(SRC)/types/dir.cpp $(SRC)/types/dir.hpp
	$(CC) -c $(SRC)/types/dir.cpp -o build/types-dir.o

TYPES_OBJECTS = build/types-string.o build/types-integer.o build/types-time.o build/types.o build/types-float.o build/types-fraction.o build/types-uuid.o build/types-color.o build/types-image.o build/types-tuple.o build/types-table.o build/types-char.o build/types-bool.o build/types-enumeration.o build/types-dir.o

lib/libtypes.a: $(TYPES_OBJECTS)
	ar scr lib/libtypes.a $(TYPES_OBJECTS)


# logging
build/log.o: $(SRC)/log/log.cpp $(SRC)/log/log.hpp lib/libtypes.a lib/libui.a
	$(CC) -c $(SRC)/log/log.cpp -ltypes -lui -o build/log.o

LOG_OBJECTS = build/log.o

lib/liblog.a: $(LOG_OBJECTS)
	ar scr lib/liblog.a $(LOG_OBJECTS)

# pattern library

build/pattern.o: $(SRC)/pattern/pattern.cpp $(SRC)/pattern/pattern.hpp
	$(CC) -c $(SRC)/pattern/pattern.cpp -o build/pattern.o

build/pattern-literal.o: $(SRC)/pattern/literal.cpp $(SRC)/pattern/literal.hpp
	$(CC) -c $(SRC)/pattern/literal.cpp -o build/pattern-literal.o

build/pattern-or.o: $(SRC)/pattern/or.cpp $(SRC)/pattern/or.hpp
	$(CC) -c $(SRC)/pattern/or.cpp -o build/pattern-or.o

build/pattern-cat.o: $(SRC)/pattern/cat.cpp $(SRC)/pattern/cat.hpp
	$(CC) -c $(SRC)/pattern/cat.cpp -o build/pattern-cat.o

build/pattern-star.o: $(SRC)/pattern/star.cpp $(SRC)/pattern/star.hpp
	$(CC) -c $(SRC)/pattern/star.cpp -o build/pattern-star.o

build/pattern-plus.o: $(SRC)/pattern/plus.cpp $(SRC)/pattern/plus.hpp
	$(CC) -c $(SRC)/pattern/plus.cpp -o build/pattern-plus.o

build/pattern-range.o: $(SRC)/pattern/range.cpp $(SRC)/pattern/range.hpp
	$(CC) -c $(SRC)/pattern/range.cpp -o build/pattern-range.o

build/pattern-group.o: $(SRC)/pattern/group.cpp $(SRC)/pattern/group.hpp
	$(CC) -c $(SRC)/pattern/group.cpp -o build/pattern-group.o

build/pattern-beginning.o: $(SRC)/pattern/beginning.cpp $(SRC)/pattern/beginning.hpp
	$(CC) -c $(SRC)/pattern/beginning.cpp -o build/pattern-beginning.o

build/pattern-cclass-union.o: $(SRC)/pattern/cclass_union.cpp $(SRC)/pattern/cclass_union.hpp
	$(CC) -c $(SRC)/pattern/cclass_union.cpp -o build/pattern-cclass-union.o

build/pattern-whitespace.o: $(SRC)/pattern/whitespace.cpp $(SRC)/pattern/whitespace.hpp
	$(CC) -c $(SRC)/pattern/whitespace.cpp -o build/pattern-whitespace.o

build/pattern-alpha.o: $(SRC)/pattern/alpha.cpp $(SRC)/pattern/alpha.hpp
	$(CC) -c $(SRC)/pattern/alpha.cpp -o build/pattern-alpha.o

build/pattern-nongreedy.o: $(SRC)/pattern/nongreedy.cpp $(SRC)/pattern/nongreedy.hpp
	$(CC) -c $(SRC)/pattern/nongreedy.cpp -o build/pattern-nongreedy.o

build/pattern-any.o: $(SRC)/pattern/any.cpp $(SRC)/pattern/any.hpp
	$(CC) -c $(SRC)/pattern/any.cpp -o build/pattern-any.o

build/pattern-digit.o: $(SRC)/pattern/digit.cpp $(SRC)/pattern/digit.hpp
	$(CC) -c $(SRC)/pattern/digit.cpp -o build/pattern-digit.o

build/pattern-hex-digit.o: $(SRC)/pattern/hex_digit.cpp $(SRC)/pattern/hex_digit.hpp
	$(CC) -c $(SRC)/pattern/hex_digit.cpp -o build/pattern-hex-digit.o

build/pattern-n-times.o: $(SRC)/pattern/n_times.cpp $(SRC)/pattern/n_times.hpp
	$(CC) -c $(SRC)/pattern/n_times.cpp -o build/pattern-n-times.o

build/pattern-negated.o: $(SRC)/pattern/negated.cpp $(SRC)/pattern/negated.hpp
	$(CC) -c $(SRC)/pattern/negated.cpp -o build/pattern-negated.o

PATTERN_OBJECTS = build/pattern.o build/pattern-literal.o build/pattern-or.o build/pattern-cat.o build/pattern-star.o build/pattern-plus.o build/pattern-range.o build/pattern-group.o build/pattern-beginning.o build/pattern-cclass-union.o build/pattern-whitespace.o build/pattern-alpha.o build/pattern-nongreedy.o build/pattern-any.o build/pattern-digit.o build/pattern-hex-digit.o build/pattern-n-times.o build/pattern-negated.o

lib/libpattern.a: $(PATTERN_OBJECTS)
	ar scr lib/libpattern.a $(PATTERN_OBJECTS)

# storage between sessions

build/store-store.o: $(SRC)/store/store.cpp $(SRC)/store/store.hpp
	$(CC) -c $(SRC)/store/store.cpp -o build/store-store.o

STORE_OBJECTS = build/store-store.o

lib/libstore.a: $(STORE_OBJECTS)
	ar scr lib/libstore.a $(STORE_OBJECTS)


# HTML
build/html-element.o: $(SRC)/html/element.cpp $(SRC)/html/element.hpp
	$(CC) -c $(SRC)/html/element.cpp -o build/html-element.o
build/html-container.o: $(SRC)/html/container.cpp $(SRC)/html/container.hpp
	$(CC) -c $(SRC)/html/container.cpp -o build/html-container.o
build/html-html.o: $(SRC)/html/html.cpp $(SRC)/html/html.hpp
	$(CC) -c $(SRC)/html/html.cpp -o build/html-html.o
build/html-div.o: $(SRC)/html/div.cpp $(SRC)/html/div.hpp
	$(CC) -c $(SRC)/html/div.cpp -o build/html-div.o
build/html-head.o: $(SRC)/html/head.cpp $(SRC)/html/head.hpp
	$(CC) -c $(SRC)/html/head.cpp -o build/html-head.o
build/html-body.o: $(SRC)/html/body.cpp $(SRC)/html/body.hpp
	$(CC) -c $(SRC)/html/body.cpp -o build/html-body.o
build/html-canvas.o: $(SRC)/html/canvas.cpp $(SRC)/html/canvas.hpp
	$(CC) -c $(SRC)/html/canvas.cpp -o build/html-canvas.o
build/html-h1.o: $(SRC)/html/h1.cpp $(SRC)/html/h1.hpp
	$(CC) -c $(SRC)/html/h1.cpp -o build/html-h1.o
build/html-table.o: $(SRC)/html/table.cpp $(SRC)/html/table.hpp
	$(CC) -c $(SRC)/html/table.cpp -o build/html-table.o
build/html-thead.o: $(SRC)/html/thead.cpp $(SRC)/html/thead.hpp
	$(CC) -c $(SRC)/html/thead.cpp -o build/html-thead.o
build/html-tbody.o: $(SRC)/html/tbody.cpp $(SRC)/html/tbody.hpp
	$(CC) -c $(SRC)/html/tbody.cpp -o build/html-tbody.o
build/html-tr.o: $(SRC)/html/tr.cpp $(SRC)/html/tr.hpp
	$(CC) -c $(SRC)/html/tr.cpp -o build/html-tr.o
build/html-td.o: $(SRC)/html/td.cpp $(SRC)/html/td.hpp
	$(CC) -c $(SRC)/html/td.cpp -o build/html-td.o
build/html-th.o: $(SRC)/html/th.cpp $(SRC)/html/th.hpp
	$(CC) -c $(SRC)/html/th.cpp -o build/html-th.o
build/html-p.o: $(SRC)/html/p.cpp $(SRC)/html/p.hpp
	$(CC) -c $(SRC)/html/p.cpp -o build/html-p.o
build/html-ul.o: $(SRC)/html/ul.cpp $(SRC)/html/ul.hpp
	$(CC) -c $(SRC)/html/ul.cpp -o build/html-ul.o
build/html-li.o: $(SRC)/html/li.cpp $(SRC)/html/li.hpp
	$(CC) -c $(SRC)/html/li.cpp -o build/html-li.o
build/html-title.o: $(SRC)/html/title.cpp $(SRC)/html/title.hpp
	$(CC) -c $(SRC)/html/title.cpp -o build/html-title.o

HTML_OBJECTS = build/html-html.o build/html-div.o build/html-head.o build/html-body.o build/html-canvas.o build/html-h1.o build/html-element.o build/html-table.o build/html-thead.o build/html-tbody.o build/html-container.o build/html-p.o build/html-ul.o build/html-li.o build/html-title.o

lib/libhtml.a: $(HTML_OBJECTS)
	ar scr lib/libhtml.a $(HTML_OBJECTS)

build/net-socket-server.o: $(SRC)/net/socket_server.cpp $(SRC)/net/socket_server.hpp
	$(CC) -c $(SRC)/net/socket_server.cpp -obuild/net-socket-server.o
build/net-http-server.o: $(SRC)/net/http_server.cpp $(SRC)/net/http_server.hpp
	$(CC) -c $(SRC)/net/http_server.cpp -o build/net-http-server.o
build/net-http-request.o: $(SRC)/net/http_request.cpp $(SRC)/net/http_request.hpp
	$(CC) -c $(SRC)/net/http_request.cpp -o build/net-http-request.o
build/net-http-response.o: $(SRC)/net/http_response.cpp $(SRC)/net/http_response.hpp
	$(CC) -c $(SRC)/net/http_response.cpp -o build/net-http-response.o

NET_OBJECTS = build/net-socket-server.o build/net-http-server.o build/net-http-request.o build/net-http-response.o

lib/libnet.a: $(NET_OBJECTS)
	ar cr lib/libnet.a $(NET_OBJECTS)

# parser

build/parse-gramex.o: $(SRC)/parse/gramex.cpp $(SRC)/parse/gramex.hpp
	$(CC) -c $(SRC)/parse/gramex.cpp -o build/parse-gramex.o

build/parse-non-terminal.o: $(SRC)/parse/non_terminal.cpp $(SRC)/parse/non_terminal.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/non_terminal.cpp -o build/parse-non-terminal.o

build/parse-parser.o: $(SRC)/parse/parser.cpp $(SRC)/parse/parser.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/parser.cpp -o build/parse-parser.o

build/parse-ruleset.o: $(SRC)/parse/ruleset.cpp $(SRC)/parse/ruleset.hpp
	$(CC) -c $(SRC)/parse/ruleset.cpp -o build/parse-ruleset.o

build/parse-or.o: $(SRC)/parse/or.cpp $(SRC)/parse/or.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/or.cpp -o build/parse-or.o

build/parse-and.o: $(SRC)/parse/and.cpp $(SRC)/parse/and.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/and.cpp -o build/parse-and.o

build/parse-literal.o: $(SRC)/parse/literal.cpp $(SRC)/parse/literal.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/literal.cpp -o build/parse-literal.o

build/parse-match-type.o: $(SRC)/parse/match_type.cpp $(SRC)/parse/match_type.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/match_type.cpp -o build/parse-match-type.o

build/parse-plus-closure.o: $(SRC)/parse/plus_closure.cpp $(SRC)/parse/plus_closure.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/plus_closure.cpp -o build/parse-plus-closure.o

build/parse-star-closure.o: $(SRC)/parse/star_closure.cpp $(SRC)/parse/star_closure.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/star_closure.cpp -o build/parse-star-closure.o

build/parse-maybe-closure.o: $(SRC)/parse/maybe_closure.cpp $(SRC)/parse/maybe_closure.hpp
	$(CC) -DINSTRUMENTED -c $(SRC)/parse/maybe_closure.cpp -o build/parse-maybe-closure.o

PARSE_OBJECTS = build/parse-gramex.o build/parse-non-terminal.o build/parse-parser.o build/parse-ruleset.o build/parse-or.o build/parse-and.o build/parse-literal.o build/parse-match-type.o build/parse-plus-closure.o build/parse-star-closure.o build/parse-maybe-closure.o

lib/libparse.a: $(PARSE_OBJECTS)
	ar cr lib/libparse.a $(PARSE_OBJECTS)

# abstract syntax tree

lib/libast.a: $(AST_OBJECTS)
	ar cr lib/libast.a $(AST_OBJECTS)

# semantic data types

build/sdt-article.o: $(SRC)/sdt/article.cpp $(SRC)/sdt/article.hpp
	$(CC) -c $(SRC)/sdt/article.cpp -o build/sdt-article.o

build/sdt-paragraph.o: $(SRC)/sdt/paragraph.cpp $(SRC)/sdt/paragraph.hpp
	$(CC) -c $(SRC)/sdt/paragraph.cpp -o build/sdt-paragraph.o

build/sdt-section.o: $(SRC)/sdt/section.cpp $(SRC)/sdt/section.hpp
	$(CC) -c $(SRC)/sdt/section.cpp -o build/sdt-section.o

SDT_OBJECTS = build/sdt-article.o build/sdt-paragraph.o build/sdt-section.o

lib/libsdt.a: $(SDT_OBJECTS)
	ar cr lib/libsdt.a $(SDT_OBJECTS)

# core types
build/core-machine.o: $(SRC)/core/machine.cpp $(SRC)/core/machine.hpp
	$(CC) -c $(SRC)/core/machine.cpp -o build/core-machine.o

build/core-system.o: $(SRC)/core/system.cpp $(SRC)/core/system.hpp
	$(CC) -c $(SRC)/core/system.cpp -o build/core-system.o

CORE_OBJECTS = build/core-system.o build/core-machine.o

lib/libcore.a: $(CORE_OBJECTS)
	ar cr lib/libcore.a $(CORE_OBJECTS)

# demos!

build/patterns-demo.o: demos/patterns_demo.cpp demos/patterns_demo.hpp lib/libpattern.a
	$(CC) -c demos/patterns_demo.cpp -lpattern -o build/patterns-demo.o

build/html-demo.o: demos/html_demo.cpp demos/html_demo.hpp lib/libhtml.a
	$(CC) -c demos/html_demo.cpp -lhtml -o build/html-demo.o

build/http-demo.o: demos/http_demo.cpp demos/http_demo.hpp lib/libnet.a
	$(CC) -c demos/http_demo.cpp -lhtml -lhttm -o build/http-demo.o

build/console-demo.o: demos/console_demo.cpp demos/console_demo.hpp lib/libui.a
	$(CC) -c demos/console_demo.cpp -o build/console-demo.o

build/color-demo.o: demos/color_demo.cpp demos/color_demo.hpp 
	$(CC) -c demos/color_demo.cpp -o build/color-demo.o

build/types-demo.o: demos/types_demo.cpp demos/types_demo.hpp
	$(CC) -c demos/types_demo.cpp -o build/types-demo.o

build/lex-demo.o: demos/lex_demo.cpp demos/lex_demo.hpp
	$(CC) -c demos/lex_demo.cpp -o build/lex-demo.o

build/parse-demo.o: demos/parse_demo.cpp demos/parse_demo.hpp
	$(CC) -c demos/parse_demo.cpp -o build/parse-demo.o

build/genesis-demo.o: demos/genesis_demo.cpp demos/genesis_demo.hpp
	$(CC) -c demos/genesis_demo.cpp -o build/genesis-demo.o

build/sdt-demo.o: demos/sdt_demo.cpp demos/sdt_demo.hpp
	$(CC) -c demos/sdt_demo.cpp -o build/sdt-demo.o

build/store-demo.o: demos/store_demo.cpp demos/store_demo.hpp
	$(CC) -c demos/store_demo.cpp -o build/store-demo.o

build/machine-demo.o: demos/machine_demo.cpp demos/machine_demo.hpp
	$(CC) -c demos/machine_demo.cpp -o build/machine-demo.o

# build archive of demos
DEMOS = build/patterns-demo.o build/html-demo.o build/http-demo.o build/console-demo.o build/color-demo.o build/types-demo.o build/lex-demo.o build/parse-demo.o build/genesis-demo.o build/sdt-demo.o build/store-demo.o build/machine-demo.o
build/librhizome-demos.a: $(DEMOS)
	ar scr build/librhizome-demos.a $(DEMOS)

# build archive of libs
LIB_OBJECTS = $(PATTERN_OBJECTS) $(TYPES_OBJECTS) $(LEXER_OBJECTS) $(LOG_OBJECTS) $(UI_OBJECTS) $(COLOR_OBJECTS) $(HTML_OBJECTS) $(LOGIC_OBJECTS) $(IMAGE_OBJECTS) $(IPC_OBJECTS) $(NET_OBJECTS) $(STORE_OBJECTS) $(PARSE_OBJECTS) $(SDT_OBJECTS) $(CORE_OBJECTS)
lib/librhizome.a: $(LIB_OBJECTS)
	ar scr lib/librhizome.a $(LIB_OBJECTS)



# issue 1

rhizome: $(SRC)/vm/*.tpp main.cpp $(DEMOS) lib/librhizome.a
	$(CC) main.cpp $(DEMOS) -lrhizome -lrt -lgmp -lgmpxx `libpng-config --ldflags` -lfreeimage -lfreeimageplus -orhizome

clean:
	$(RM) ./build/*.o
	$(RM) ./lib/*.a
	$(RM) ./rhizome