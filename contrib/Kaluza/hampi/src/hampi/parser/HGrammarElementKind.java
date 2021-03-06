package hampi.parser;

/**
 * Different kinds of grammar entities.
 */
public enum HGrammarElementKind{
  PROGRAM,
  BEXPR_CONTAINS,
  BEXPR_IN,
  CFG_CHAR_RANGE,
  CFG_NONTERMINAL,
  CFG_OPTION,
  CFG_STAR,
  CFG_PLUS,
  CFG_TERMINAL,
  EXPR_CONCAT,
  EXPR_CONST,
  EXPR_VAR,
  REG_FIX,
  REG_CONST,
  REG_STAR,
  REG_RANGE,
  REG_OR,
  REG_CONCAT,
  REG_VAR,
  STMT_CFG,
  STMT_ASSERT,
  STMT_REGDECL,
  STMT_VALDECL,
  STMT_VARDECL,
}
