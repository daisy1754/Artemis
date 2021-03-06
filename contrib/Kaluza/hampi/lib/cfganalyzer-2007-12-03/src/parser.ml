type token =
  | Colon
  | Semicolon
  | Quotes
  | Name
  | String of (string)
  | Terminal of (string)
  | EOF

open Parsing;;
# 3 "src/parser.mly"

open Cfg

# 16 "src/parser.ml"
let yytransl_const = [|
  257 (* Colon *);
  258 (* Semicolon *);
  259 (* Quotes *);
  260 (* Name *);
    0 (* EOF *);
    0|]

let yytransl_block = [|
  261 (* String *);
  262 (* Terminal *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\002\000\003\000\004\000\004\000\005\000\006\000\
\006\000\007\000\007\000\008\000\008\000\000\000"

let yylen = "\002\000\
\001\000\002\000\002\000\001\000\001\000\002\000\004\000\001\000\
\000\000\002\000\000\000\001\000\001\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\004\000\001\000\014\000\000\000\000\000\002\000\
\008\000\003\000\000\000\000\000\006\000\000\000\012\000\013\000\
\000\000\000\000\007\000\010\000"

let yydgoto = "\002\000\
\005\000\006\000\007\000\010\000\011\000\012\000\017\000\018\000"

let yysindex = "\255\255\
\002\000\000\000\000\000\000\000\000\000\002\000\001\255\000\000\
\000\000\000\000\001\255\005\255\000\000\254\254\000\000\000\000\
\006\255\254\254\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\008\255\000\000\
\000\000\000\000\001\000\000\000\000\000\009\255\000\000\000\000\
\000\000\009\255\000\000\000\000"

let yygindex = "\000\000\
\004\000\000\000\000\000\252\255\000\000\000\000\250\255\000\000"

let yytablesize = 263
let yytable = "\001\000\
\005\000\004\000\015\000\016\000\009\000\014\000\013\000\019\000\
\009\000\008\000\011\000\020\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\009\000\000\000\000\000\000\000\005\000\003\000"

let yycheck = "\001\000\
\000\000\000\000\005\001\006\001\004\001\001\001\011\000\002\001\
\001\001\006\000\002\001\018\000\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\001\001\255\255\255\255\255\255\005\001\005\001"

let yynames_const = "\
  Colon\000\
  Semicolon\000\
  Quotes\000\
  Name\000\
  EOF\000\
  "

let yynames_block = "\
  String\000\
  Terminal\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    Obj.repr(
# 19 "src/parser.mly"
                                                ( [] )
# 149 "src/parser.ml"
               : Cfg.pureCFG))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'vardecl) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Cfg.pureCFG) in
    Obj.repr(
# 20 "src/parser.mly"
                                                ( _1 :: _2 )
# 157 "src/parser.ml"
               : Cfg.pureCFG))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'nonterminal) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'rules) in
    Obj.repr(
# 24 "src/parser.mly"
                                                ( (_1,_2) )
# 165 "src/parser.ml"
               : 'vardecl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 28 "src/parser.mly"
                                                ( _1 )
# 172 "src/parser.ml"
               : 'nonterminal))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'rule) in
    Obj.repr(
# 32 "src/parser.mly"
                                                ( [ _1 ] )
# 179 "src/parser.ml"
               : 'rules))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'rule) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'rules) in
    Obj.repr(
# 33 "src/parser.mly"
                                                ( _1 :: _2 )
# 187 "src/parser.ml"
               : 'rules))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'rulename) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'symbollist) in
    Obj.repr(
# 37 "src/parser.mly"
                                                ( _3 )
# 195 "src/parser.ml"
               : 'rule))
; (fun __caml_parser_env ->
    Obj.repr(
# 41 "src/parser.mly"
                                                ( () )
# 201 "src/parser.ml"
               : 'rulename))
; (fun __caml_parser_env ->
    Obj.repr(
# 42 "src/parser.mly"
                                                ( () )
# 207 "src/parser.ml"
               : 'rulename))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'symbol) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'symbollist) in
    Obj.repr(
# 46 "src/parser.mly"
                                                ( _1 :: _2 )
# 215 "src/parser.ml"
               : 'symbollist))
; (fun __caml_parser_env ->
    Obj.repr(
# 47 "src/parser.mly"
                                                ( [] )
# 221 "src/parser.ml"
               : 'symbollist))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 51 "src/parser.mly"
                                                ( Nonterminal(_1) )
# 228 "src/parser.ml"
               : 'symbol))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 52 "src/parser.mly"
                                                ( Terminal(_1) )
# 235 "src/parser.ml"
               : 'symbol))
(* Entry cfg *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let cfg (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Cfg.pureCFG)
;;
# 57 "src/parser.mly"




# 265 "src/parser.ml"
