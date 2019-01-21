grammar verilogPreproc;

/* Process #define statements in a C file using fuzzy parsing.
*/

//@lexer::members {
//  int parentesis_nesting = 0;
//}

file
    :   .*? ( preprocess_directive .*? )*
    ;

preprocess_directive 
    : define
    | undef
    | conditional
    | include
    | token_id
    ;

define
    :   DEFINE macro_id LP NEW_LINE* ID NEW_LINE* ('=' default_text) ? ( ',' NEW_LINE* ID NEW_LINE* ('=' default_text)? )* RP replacement 
    |   DEFINE macro_id replacement
    |   DEFINE macro_id
    ;

replacement
    :   ~'\n'+ '\n'+
    ;

default_text
    : ~(',' | ')')+
    ;

undef 
    : UNDEF ID ;

conditional
    : ifdef_directive
    | ifndef_directive
    ;

ifdef_directive 
    : IFDEF ID ifdef_group_of_lines 
      ( ELSIF ID elsif_group_of_lines )* 
      ( ELSE else_group_of_lines )? ENDIF ;


ifndef_directive 
    : IFNDEF ID ifndef_group_of_lines 
      ( ELSIF ID elsif_group_of_lines )* 
      ( ELSE else_group_of_lines )? ENDIF ;

ifdef_group_of_lines
    : group_of_lines
    ;

ifndef_group_of_lines
    : group_of_lines
    ;

elsif_group_of_lines
    : group_of_lines
    ;
else_group_of_lines
    : group_of_lines
    ;

group_of_lines
    : .*? ( preprocess_directive .*? )*
    ;

token_id
    //: <assoc=right> BACKTICK macro_toreplace NEW_LINE* LP NEW_LINE* value? NEW_LINE* ( ',' NEW_LINE* value? NEW_LINE* )* RP  //{System.out.println(">>> to replace : " + $macro_toreplace.text);}
    : BACKTICK macro_toreplace NEW_LINE* LP NEW_LINE* value? NEW_LINE* ( ',' NEW_LINE* value? NEW_LINE* )* RP  //{System.out.println(">>> to replace : " + $macro_toreplace.text);}
    | BACKTICK macro_toreplace  //{ System.out.println(">>> to replace : " + $macro_toreplace.text);}
    ;

value
    : token_id 
    | (ID|OTHER|StringLiteral)+
    | LP value* RP
    | '"' value* '"'
    | '{' value* '}'
    | '[' value* ']'
    ;

include
    : INCLUDE StringLiteral
    ;

INCLUDE
    : '`include'
    ;

DEFINE
    : '`define'
    ;

IFNDEF
    : '`ifndef'
    ;

UNDEF
    : '`undef'
    ;

IFDEF
    : '`ifdef'
    ;


ELSIF
    : '`elsif'
    ;

ELSE
    : '`else'
    ;

ENDIF
    :'`endif'
    ;

LP 
    : '(' {
//  if (parentesis_nesting > 0) {
//    setType(OTHER);
//  }
//  parentesis_nesting++;
}
    ;
    
RP
    : ')' {
//  parentesis_nesting--;
//  if (parentesis_nesting > 0) {
//    setType(OTHER);
//  }
}
    ;

IGNORED_DIRECTIVE
    : BACKTICK Ignored_directive
    ;

BACKTICK
    : '`'
    ;

fragment Ignored_directive
    : 'begin_keywords' | 'celldefine' | 'default_nettype' 
    | 'end_keywords' | 'endcelldefine' | 'line' 
    | 'nounconnected_drive' | 'pragma' | 'resetall'
    | 'timescale' | 'unconnected_drive'
    ;
 
macro_id
    : ID
    ;

macro_toreplace
    : ID
    ;

ID  :   ( ID_FIRST (ID_FIRST | DIGIT)* ) ;

fragment DIGIT    : [0-9] ;
fragment ID_FIRST : LETTER | '_' ;
fragment LETTER   : [a-zA-Z] ;

/* from
http://media.pragprog.com/titles/tpantlr2/code/reference/FuzzyJava.g4 */

CharacterLiteral
    :   '\'' ( EscapeSequence | ~('\''|'\\') ) '\''
    ;

StringLiteral
    :  '"' ( EscapeSequence | ~('\\'|'"') )* '"'
    |  '<' ( EscapeSequence | ~('\\'|'>') )* '>'
    ;

fragment
EscapeSequence
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\')
    |   UnicodeEscape
    |   OctalEscape
    ;

fragment
OctalEscape
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UnicodeEscape
    :   '\\' 'u' HexDigit HexDigit HexDigit HexDigit
    ;

fragment
HexDigit : ('0'..'9'|'a'..'f'|'A'..'F') ;

COMMENT
    :   '/*' .*? '*/'    -> channel(HIDDEN) // match anything between /* and */
    ;

LINE_ESCAPE
    :  '\\' '\r'? '\n' -> channel(4)
    ;

LINE_COMMENT
    : '//' ~[\r\n]* '\r'? -> channel(5) 
    ;


WS  :   [ \r\t\u000C]+ -> channel(HIDDEN)
     ;



NEW_LINE 
    : '\n'
    ;

OTHER 
    : . //-> channel(HIDDEN)
    ; 
