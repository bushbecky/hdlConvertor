lexer grammar sv2017Lexer;

@lexer::header {
#include <hdlConvertor/language.h>
}
@lexer::members {
    hdlConvertor::Language language_version;
}
KW_DOLAR_ERROR: '$error';
KW_DOLAR_FATAL: '$fatal';
KW_DOLAR_FULLSKEW: '$fullskew';
KW_DOLAR_HOLD: '$hold';
KW_DOLAR_INFO: '$info';
KW_DOLAR_NOCHANGE: '$nochange';
KW_DOLAR_PERIOD: '$period';
KW_DOLAR_RECOVERY: '$recovery';
KW_DOLAR_RECREM: '$recrem';
KW_DOLAR_REMOVAL: '$removal';
KW_DOLAR_ROOT: '$root';
KW_DOLAR_SETUP: '$setup';
KW_DOLAR_SETUPHOLD: '$setuphold';
KW_DOLAR_SKEW: '$skew';
KW_DOLAR_TIMESKEW: '$timeskew';
KW_DOLAR_UNIT: '$unit';
KW_DOLAR_WARNING: '$warning';
KW_DOLAR_WIDTH: '$width';
KW_1STEP: '1step';
KW_PATHPULSEDOLAR_: 'PATHPULSE$';
KW_ACCEPT_ON:
 'accept_on' {language_version >= hdlConvertor::Language::SV2009}?;
KW_ALIAS:
 'alias' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ALWAYS: 'always';
KW_ALWAYS_COMB:
 'always_comb' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ALWAYS_FF:
 'always_ff' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ALWAYS_LATCH:
 'always_latch' {language_version >= hdlConvertor::Language::SV2005}?;
KW_AND: 'and';
KW_ASSERT:
 'assert' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ASSIGN: 'assign';
KW_ASSUME:
 'assume' {language_version >= hdlConvertor::Language::SV2005}?;
KW_AUTOMATIC:
 'automatic' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_BEFORE:
 'before' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BEGIN: 'begin';
KW_BIND:
 'bind' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BINS:
 'bins' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BINSOF:
 'binsof' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BIT:
 'bit' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BREAK:
 'break' {language_version >= hdlConvertor::Language::SV2005}?;
KW_BUF: 'buf';
KW_BUFIF0: 'bufif0';
KW_BUFIF1: 'bufif1';
KW_BYTE:
 'byte' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CASE: 'case';
KW_CASEX: 'casex';
KW_CASEZ: 'casez';
KW_CELL:
 'cell' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_CHANDLE:
 'chandle' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CHECKER:
 'checker' {language_version >= hdlConvertor::Language::SV2009}?;
KW_CLASS:
 'class' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CLOCKING:
 'clocking' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CMOS: 'cmos';
KW_CONFIG:
 'config' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_CONST:
 'const' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CONSTRAINT:
 'constraint' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CONTEXT:
 'context' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CONTINUE:
 'continue' {language_version >= hdlConvertor::Language::SV2005}?;
KW_COVER:
 'cover' {language_version >= hdlConvertor::Language::SV2005}?;
KW_COVERGROUP:
 'covergroup' {language_version >= hdlConvertor::Language::SV2005}?;
KW_COVERPOINT:
 'coverpoint' {language_version >= hdlConvertor::Language::SV2005}?;
KW_CROSS:
 'cross' {language_version >= hdlConvertor::Language::SV2005}?;
KW_DEASSIGN: 'deassign';
KW_DEFAULT: 'default';
KW_DEFPARAM: 'defparam';
KW_DESIGN:
 'design' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_DISABLE: 'disable';
KW_DIST:
 'dist' {language_version >= hdlConvertor::Language::SV2005}?;
KW_DO:
 'do' {language_version >= hdlConvertor::Language::SV2005}?;
KW_EDGE: 'edge';
KW_ELSE: 'else';
KW_END: 'end';
KW_ENDCASE: 'endcase';
KW_ENDCHECKER:
 'endchecker' {language_version >= hdlConvertor::Language::SV2009}?;
KW_ENDCLASS:
 'endclass' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDCLOCKING:
 'endclocking' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDCONFIG:
 'endconfig' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_ENDFUNCTION: 'endfunction';
KW_ENDGENERATE:
 'endgenerate' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_ENDGROUP:
 'endgroup' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDINTERFACE:
 'endinterface' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDMODULE: 'endmodule';
KW_ENDPACKAGE:
 'endpackage' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDPRIMITIVE: 'endprimitive';
KW_ENDPROGRAM:
 'endprogram' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDPROPERTY:
 'endproperty' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDSEQUENCE:
 'endsequence' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ENDSPECIFY: 'endspecify';
KW_ENDTASK: 'endtask';
KW_ENUM:
 'enum' {language_version >= hdlConvertor::Language::SV2005}?;
KW_EVENT: 'event';
KW_EVENTUALLY:
 'eventually' {language_version >= hdlConvertor::Language::SV2009}?;
KW_EXPECT:
 'expect' {language_version >= hdlConvertor::Language::SV2005}?;
KW_EXPORT:
 'export' {language_version >= hdlConvertor::Language::SV2005}?;
KW_EXTENDS:
 'extends' {language_version >= hdlConvertor::Language::SV2005}?;
KW_EXTERN:
 'extern' {language_version >= hdlConvertor::Language::SV2005}?;
KW_FINAL:
 'final' {language_version >= hdlConvertor::Language::SV2005}?;
KW_FIRST_MATCH:
 'first_match' {language_version >= hdlConvertor::Language::SV2005}?;
KW_FOR: 'for';
KW_FORCE: 'force';
KW_FOREACH:
 'foreach' {language_version >= hdlConvertor::Language::SV2005}?;
KW_FOREVER: 'forever';
KW_FORK: 'fork';
KW_FORKJOIN:
 'forkjoin' {language_version >= hdlConvertor::Language::SV2005}?;
KW_FUNCTION: 'function';
KW_GENERATE:
 'generate' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_GENVAR:
 'genvar' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_GLOBAL:
 'global' {language_version >= hdlConvertor::Language::SV2009}?;
KW_HIGHZ0: 'highz0';
KW_HIGHZ1: 'highz1';
KW_IF: 'if';
KW_IFF:
 'iff' {language_version >= hdlConvertor::Language::SV2005}?;
KW_IFNONE: 'ifnone';
KW_IGNORE_BINS:
 'ignore_bins' {language_version >= hdlConvertor::Language::SV2005}?;
KW_ILLEGAL_BINS:
 'illegal_bins' {language_version >= hdlConvertor::Language::SV2005}?;
KW_IMPLEMENTS:
 'implements' {language_version >= hdlConvertor::Language::SV2012}?;
KW_IMPLIES:
 'implies' {language_version >= hdlConvertor::Language::SV2009}?;
KW_IMPORT:
 'import' {language_version >= hdlConvertor::Language::SV2005}?;
KW_INITIAL: 'initial';
KW_INOUT: 'inout';
KW_INPUT: 'input';
KW_INSIDE:
 'inside' {language_version >= hdlConvertor::Language::SV2005}?;
KW_INSTANCE:
 'instance' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_INT:
 'int' {language_version >= hdlConvertor::Language::SV2005}?;
KW_INTEGER: 'integer';
KW_INTERCONNECT:
 'interconnect' {language_version >= hdlConvertor::Language::SV2012}?;
KW_INTERFACE:
 'interface' {language_version >= hdlConvertor::Language::SV2005}?;
KW_INTERSECT:
 'intersect' {language_version >= hdlConvertor::Language::SV2005}?;
KW_JOIN: 'join';
KW_JOIN_ANY:
 'join_any' {language_version >= hdlConvertor::Language::SV2005}?;
KW_JOIN_NONE:
 'join_none' {language_version >= hdlConvertor::Language::SV2005}?;
KW_LARGE: 'large';
KW_LET:
 'let' {language_version >= hdlConvertor::Language::SV2009}?;
KW_LIBLIST:
 'liblist' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_LOCAL:
 'local' {language_version >= hdlConvertor::Language::SV2005}?;
KW_LOCALPARAM:
 'localparam' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_LOGIC:
 'logic' {language_version >= hdlConvertor::Language::SV2005}?;
KW_LONGINT:
 'longint' {language_version >= hdlConvertor::Language::SV2005}?;
KW_MACROMODULE: 'macromodule';
KW_MATCHES:
 'matches' {language_version >= hdlConvertor::Language::SV2005}?;
KW_MEDIUM: 'medium';
KW_MODPORT:
 'modport' {language_version >= hdlConvertor::Language::SV2005}?;
KW_MODULE: 'module';
KW_NAND: 'nand';
KW_NEGEDGE: 'negedge';
KW_NETTYPE:
 'nettype' {language_version >= hdlConvertor::Language::SV2012}?;
KW_NEW:
 'new' {language_version >= hdlConvertor::Language::SV2005}?;
KW_NEXTTIME:
 'nexttime' {language_version >= hdlConvertor::Language::SV2009}?;
KW_NMOS: 'nmos';
KW_NOR: 'nor';
KW_NOSHOWCANCELLED:
 'noshowcancelled' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_NOT: 'not';
KW_NOTIF0: 'notif0';
KW_NOTIF1: 'notif1';
KW_NULL:
 'null' {language_version >= hdlConvertor::Language::SV2005}?;
KW_OPTION: 'option';
KW_OR: 'or';
KW_OUTPUT: 'output';
KW_PACKAGE:
 'package' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PACKED:
 'packed' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PARAMETER: 'parameter';
KW_PMOS: 'pmos';
KW_POSEDGE: 'posedge';
KW_PRIMITIVE: 'primitive';
KW_PRIORITY:
 'priority' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PROGRAM:
 'program' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PROPERTY:
 'property' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PROTECTED:
 'protected' {language_version >= hdlConvertor::Language::SV2005}?;
KW_PULL0: 'pull0';
KW_PULL1: 'pull1';
KW_PULLDOWN: 'pulldown';
KW_PULLUP: 'pullup';
KW_PULSESTYLE_ONDETECT:
 'pulsestyle_ondetect' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_PULSESTYLE_ONEVENT:
 'pulsestyle_onevent' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_PURE:
 'pure' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RAND:
 'rand' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RANDC:
 'randc' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RANDCASE:
 'randcase' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RANDOMIZE: 'randomize';
KW_RANDSEQUENCE:
 'randsequence' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RCMOS: 'rcmos';
KW_REAL: 'real';
KW_REALTIME: 'realtime';
KW_REF:
 'ref' {language_version >= hdlConvertor::Language::SV2005}?;
KW_REG: 'reg';
KW_REJECT_ON:
 'reject_on' {language_version >= hdlConvertor::Language::SV2009}?;
KW_RELEASE: 'release';
KW_REPEAT: 'repeat';
KW_RESTRICT:
 'restrict' {language_version >= hdlConvertor::Language::SV2009}?;
KW_RETURN:
 'return' {language_version >= hdlConvertor::Language::SV2005}?;
KW_RNMOS: 'rnmos';
KW_RPMOS: 'rpmos';
KW_RTRAN: 'rtran';
KW_RTRANIF0: 'rtranif0';
KW_RTRANIF1: 'rtranif1';
KW_S_ALWAYS:
 's_always' {language_version >= hdlConvertor::Language::SV2009}?;
KW_S_EVENTUALLY:
 's_eventually' {language_version >= hdlConvertor::Language::SV2009}?;
KW_S_NEXTTIME:
 's_nexttime' {language_version >= hdlConvertor::Language::SV2009}?;
KW_S_UNTIL:
 's_until' {language_version >= hdlConvertor::Language::SV2009}?;
KW_S_UNTIL_WITH:
 's_until_with' {language_version >= hdlConvertor::Language::SV2009}?;
KW_SAMPLE: 'sample';
KW_SCALARED: 'scalared';
KW_SEQUENCE:
 'sequence' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SHORTINT:
 'shortint' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SHORTREAL:
 'shortreal' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SHOWCANCELLED:
 'showcancelled' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_SIGNED:
 'signed' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_SMALL: 'small';
KW_SOFT:
 'soft' {language_version >= hdlConvertor::Language::SV2012}?;
KW_SOLVE:
 'solve' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SPECIFY: 'specify';
KW_SPECPARAM: 'specparam';
KW_STATIC:
 'static' {language_version >= hdlConvertor::Language::SV2005}?;
KW_STD: 'std';
KW_STRING:
 'string' {language_version >= hdlConvertor::Language::SV2005}?;
KW_STRONG:
 'strong' {language_version >= hdlConvertor::Language::SV2009}?;
KW_STRONG0: 'strong0';
KW_STRONG1: 'strong1';
KW_STRUCT:
 'struct' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SUPER:
 'super' {language_version >= hdlConvertor::Language::SV2005}?;
KW_SUPPLY0: 'supply0';
KW_SUPPLY1: 'supply1';
KW_SYNC_ACCEPT_ON:
 'sync_accept_on' {language_version >= hdlConvertor::Language::SV2009}?;
KW_SYNC_REJECT_ON:
 'sync_reject_on' {language_version >= hdlConvertor::Language::SV2009}?;
KW_TABLE: 'table' -> pushMode(TABLE_MODE);
KW_TAGGED:
 'tagged' {language_version >= hdlConvertor::Language::SV2005}?;
KW_TASK: 'task';
KW_THIS:
 'this' {language_version >= hdlConvertor::Language::SV2005}?;
KW_THROUGHOUT:
 'throughout' {language_version >= hdlConvertor::Language::SV2005}?;
KW_TIME: 'time';
KW_TIMEPRECISION:
 'timeprecision' {language_version >= hdlConvertor::Language::SV2005}?;
KW_TIMEUNIT:
 'timeunit' {language_version >= hdlConvertor::Language::SV2005}?;
KW_TRAN: 'tran';
KW_TRANIF0: 'tranif0';
KW_TRANIF1: 'tranif1';
KW_TRI: 'tri';
KW_TRI0: 'tri0';
KW_TRI1: 'tri1';
KW_TRIAND: 'triand';
KW_TRIOR: 'trior';
KW_TRIREG: 'trireg';
KW_TYPE:
 'type' {language_version >= hdlConvertor::Language::SV2005}?;
KW_TYPE_OPTION: 'type_option';
KW_TYPEDEF:
 'typedef' {language_version >= hdlConvertor::Language::SV2005}?;
KW_UNION:
 'union' {language_version >= hdlConvertor::Language::SV2005}?;
KW_UNIQUE:
 'unique' {language_version >= hdlConvertor::Language::SV2005}?;
KW_UNIQUE0:
 'unique0' {language_version >= hdlConvertor::Language::SV2009}?;
KW_UNSIGNED:
 'unsigned' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_UNTIL:
 'until' {language_version >= hdlConvertor::Language::SV2009}?;
KW_UNTIL_WITH:
 'until_with' {language_version >= hdlConvertor::Language::SV2009}?;
KW_UNTYPED:
 'untyped' {language_version >= hdlConvertor::Language::SV2009}?;
KW_USE:
 'use' {language_version >= hdlConvertor::Language::VERILOG2001}?;
KW_UWIRE:
 'uwire' {language_version >= hdlConvertor::Language::VERILOG2005}?;
KW_VAR:
 'var' {language_version >= hdlConvertor::Language::SV2005}?;
KW_VECTORED: 'vectored';
KW_VIRTUAL:
 'virtual' {language_version >= hdlConvertor::Language::SV2005}?;
KW_VOID:
 'void' {language_version >= hdlConvertor::Language::SV2005}?;
KW_WAIT: 'wait';
KW_WAIT_ORDER:
 'wait_order' {language_version >= hdlConvertor::Language::SV2005}?;
KW_WAND: 'wand';
KW_WEAK:
 'weak' {language_version >= hdlConvertor::Language::SV2009}?;
KW_WEAK0: 'weak0';
KW_WEAK1: 'weak1';
KW_WHILE: 'while';
KW_WILDCARD:
 'wildcard' {language_version >= hdlConvertor::Language::SV2005}?;
KW_WIRE: 'wire';
KW_WITH:
 'with' {language_version >= hdlConvertor::Language::SV2005}?;
KW_WITHIN:
 'within' {language_version >= hdlConvertor::Language::SV2005}?;
KW_WOR: 'wor';
KW_XNOR: 'xnor';
KW_XOR: 'xor';
EDGE_CONTROL_SPECIFIER:
 'edge' LSQUARE_BR EDGE_DESCRIPTOR ( COMMA EDGE_DESCRIPTOR )* RSQUARE_BR;
TIME_LITERAL:
 ( UNSIGNED_NUMBER 
  | FIXED_POINT_NUMBER 
  ) TIME_UNIT;
DECIMAL_NUMBER_WITH_BASE:
 ( SIZE )? DECIMAL_BASE UNSIGNED_NUMBER;
DECIMAL_INVALID_NUMBER_WITH_BASE:
 ( SIZE )? DECIMAL_BASE X_DIGIT ( UNDERSCORE )*;
DECIMAL_TRISTATE_NUMBER_WITH_BASE:
 ( SIZE )? DECIMAL_BASE Z_DIGIT ( UNDERSCORE )*;
BINARY_NUMBER:
 ( SIZE )? BINARY_BASE BINARY_VALUE;
OCTAL_NUMBER:
 ( SIZE )? OCTAL_BASE OCTAL_VALUE;
HEX_NUMBER:
 ( SIZE )? HEX_BASE HEX_VALUE;
REAL_NUMBER_WITH_EXP:
 UNSIGNED_NUMBER ( DOT UNSIGNED_NUMBER )? EXP ( SIGN )? UNSIGNED_NUMBER;
FIXED_POINT_NUMBER:
 UNSIGNED_NUMBER DOT UNSIGNED_NUMBER;
UNSIGNED_NUMBER:
 DECIMAL_DIGIT ( UNDERSCORE 
                  | DECIMAL_DIGIT 
                  )*;
UNBASED_UNSIZED_LITERAL:
 APOSTROPHE Z_OR_X 
  | '\'0' 
  | '\'1' 
 ;
STRING_LITERAL:
 DBLQUOTE ( ANY_ASCII_CHARACTERS )* DBLQUOTE;
C_IDENTIFIER:
 [a-zA-Z_] ( [a-zA-Z0-9_] )*;
ESCAPED_IDENTIFIER:
 BACKSLASH ( ANY_PRINTABLE_ASCII_CHARACTER_EXCEPT_WHITE_SPACE )* WHITE_SPACE;
SIMPLE_IDENTIFIER:
 [a-zA-Z_] ( [a-zA-Z0-9_$] )*;
SYSTEM_TF_IDENTIFIER:
 DOLAR [a-zA-Z0-9_$] ( [a-zA-Z0-9_$] )*;
SEMI: ';';
LPAREN: '(';
RPAREN: ')';
LSQUARE_BR: '[';
RSQUARE_BR: ']';
LBRACE: '{';
RBRACE: '}';
APOSTROPHE: '\'';
SHIFT_LEFT: '<<';
SHIFT_RIGHT: '>>';
ARITH_SHIFT_LEFT: '<<<';
ARITH_SHIFT_RIGHT: '>>>';
DOLAR: '$';
UNDERSCORE: '_';
MOD: '%';
NOT: '!';
NEG: '~';
NAND: '~&';
NOR: '~|';
XOR: '^';
NXOR: '~^';
XORN: '^~';
COMMA: ',';
DOT: '.';
QUESTIONMARK: '?';
COLON: ':';
DOUBLE_COLON: '::';
EQ: '==';
NEQ: '!=';
CASE_EQ: '===';
CASE_NEQ: '!==';
WILDCARD_EQ: '==?';
WILDCARD_NEQ: '!=?';
ASSIGN: '=';
LT: '<';
GT: '>';
GE: '>=';
LE: '<=';
PLUS_EQ: '+=';
MINUS_EQ: '-=';
MUL_EQ: '*=';
DIV_EQ: '/=';
MOD_EQ: '%=';
AND_EQ: '&=';
OR_EQ: '|=';
XOR_EQ: '^=';
SHIFT_LEFT_EQ: '<<=';
SHIFT_RIGHT_EQ: '>>=';
ARITH_SHIFT_LEFT_EQ: '<<<=';
ARITH_SHIFT_RIGHT_EQ: '>>>=';
PLUS: '+';
MINUS: '-';
AMPERSAND: '&';
LOG_AND: '&&';
BAR: '|';
LOG_OR: '||';
BACKSLASH: '\\';
MUL: '*';
DIV: '/';
DOUBLESTAR: '**';
BI_DIR_ARROW: '<->';
ARROW: '->';
DOUBLE_RIGHT_ARROW: '->>';
INCR: '++';
DECR: '--';
DIST_WEIGHT_ASSIGN: ':=';
DIST_WEIGHT_ASSIGN_DIV: ':/';
OVERLAPPING_IMPL: '|->';
NONOVERLAPPING_IMPL: '|=>';
IMPLIES: '=>';
PATH_FULL: '*>';
HASH_MINUS_HASH: '#-#';
HASH_EQ_HASH: '#=#';
AT: '@';
DOUBLE_AT: '@@';
HASH: '#';
DOUBLE_HASH: '##';
TRIPLE_AND: '&&&';
ONE_LINE_COMMENT:
 '//' .*? ( '\r' )? '\n' -> channel(HIDDEN);
BLOCK_COMMENT:
 '/*' .*? '*/' -> channel(HIDDEN);
WHITE_SPACE: [ \t\n\r] + -> channel(HIDDEN);
fragment EDGE_DESCRIPTOR:
 Z_OR_X ZERO_OR_ONE 
  | ZERO_OR_ONE Z_OR_X 
  | '01' 
  | '10' 
 ;
fragment ZERO_OR_ONE: [01];
fragment Z_OR_X: [xXzZ];
fragment TIME_UNIT:
 's' 
  | 'ms' 
  | 'us' 
  | 'ns' 
  | 'ps' 
  | 'fs' 
 ;
fragment SIGN:
 PLUS 
  | MINUS 
 ;
fragment SIZE: NON_ZERO_UNSIGNED_NUMBER;
fragment NON_ZERO_UNSIGNED_NUMBER:
 NON_ZERO_DECIMAL_DIGIT ( UNDERSCORE 
                          | DECIMAL_DIGIT 
                          )*;
fragment EXP: [eE];
fragment BINARY_VALUE:
 BINARY_DIGIT ( UNDERSCORE 
                  | BINARY_DIGIT 
                  )*;
fragment OCTAL_VALUE:
 OCTAL_DIGIT ( UNDERSCORE 
              | OCTAL_DIGIT 
              )*;
fragment HEX_VALUE:
 HEX_DIGIT ( UNDERSCORE 
              | HEX_DIGIT 
              )*;
fragment DECIMAL_BASE:
 APOSTROPHE ( [sS] )? [dD];
fragment BINARY_BASE:
 APOSTROPHE ( [sS] )? [bB];
fragment OCTAL_BASE:
 APOSTROPHE ( [sS] )? [oO];
fragment HEX_BASE:
 APOSTROPHE ( [sS] )? [hH];
fragment NON_ZERO_DECIMAL_DIGIT: [1-9];
fragment DECIMAL_DIGIT: [0-9];
fragment BINARY_DIGIT:
 X_DIGIT 
  | Z_DIGIT 
  | [01] 
 ;
fragment OCTAL_DIGIT:
 X_DIGIT 
  | Z_DIGIT 
  | [0-7] 
 ;
fragment HEX_DIGIT:
 X_DIGIT 
  | Z_DIGIT 
  | [0-9a-fA-F] 
 ;
fragment X_DIGIT: [xX];
fragment Z_DIGIT:
 QUESTIONMARK 
  | [zZ] 
 ;
fragment DBLQUOTE: '"';
fragment ANY_ASCII_CHARACTERS:
 ~["\\\r\n] 
  | '\\\n' 
  | '\\\r\n' 
  | '\\' [nt\\"vfa%] 
  | '\\' [0-9] [0-9]? [0-9]? 
  | '\\' 'x' [0-9A-Fa-f] [0-9A-Fa-f]? 
 ;
fragment ANY_PRINTABLE_ASCII_CHARACTER_EXCEPT_WHITE_SPACE: '\u0021'..'\u007E';

mode TABLE_MODE;
    KW_ENDTABLE: 'endtable' -> popMode;
    LEVEL_SYMBOL:
 QUESTIONMARK 
  | [01xXbB] 
 ;
    EDGE_SYMBOL:
 MUL 
  | [rRfFpPnN] 
 ;
    TABLE_MODE_BLOCK_COMMENT:
 '/*' .*? '*/' -> channel(HIDDEN),type(BLOCK_COMMENT);
    TABLE_MODE_COLON: ':' -> type(COLON);
    TABLE_MODE_LPAREN: '(' -> type(LPAREN);
    TABLE_MODE_MINUS: '-' -> type(MINUS);
    TABLE_MODE_ONE_LINE_COMMENT:
 '//' .*? ( '\r' )? '\n' -> channel(HIDDEN),type(ONE_LINE_COMMENT);
    TABLE_MODE_RPAREN: ')' -> type(RPAREN);
    TABLE_MODE_SEMI: ';' -> type(SEMI);
    TABLE_MODE_WHITE_SPACE: [ \t\n\r] + -> channel(HIDDEN),type(WHITE_SPACE);
