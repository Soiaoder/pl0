// PL0.g4

grammar PL0;

// 词法规则
PROGRAM: 'PROGRAM';
BEGIN: 'BEGIN';
END: 'END';
CONST: 'CONST';
VAR: 'VAR';
WHILE: 'WHILE';
DO: 'DO';
IF: 'IF';
THEN: 'THEN';
ELSE: 'ELSE';
IDENTIFIER: [a-z] [a-z0-9]*;
INTEGER: '0' | [1-9] [0-9]*;
PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';
ASSIGN: ':=';
EQUAL: '=';
NOTEQUAL: '<>';
LESS: '<';
LESSEQUAL: '<=';
GREATER: '>';
GREATEREQUAL: '>=';



LPAREN: '(';
RPAREN: ')';
SEMICOLON: ';';
COMMA: ',';



// 语法规则
program: programHeader subProgram;

programHeader: PROGRAM IDENTIFIER ;

subProgram: (constantDeclaration)? (variableDeclaration)?  statementPart;

constantDeclaration: CONST constantDefinition (COMMA constantDefinition)* SEMICOLON;

constantDefinition: IDENTIFIER ASSIGN INTEGER;

variableDeclaration: VAR identifierList SEMICOLON;

identifierList: IDENTIFIER (COMMA IDENTIFIER)*;

statementPart: compoundStatement | statement;

compoundStatement: BEGIN statement (SEMICOLON statement)* END;

statement: assignmentStatement
         | ifStatement
         | whileStatement
         | compoundStatement
         | emptyStatement;

assignmentStatement: IDENTIFIER ASSIGN expression;

ifStatement: IF condition THEN statement (ELSE statement)?;

whileStatement: WHILE condition DO statement;

condition: expression (EQUAL | NOTEQUAL | LESS | LESSEQUAL | GREATER | GREATEREQUAL) expression;

expression: MINUS? term ( plus term )*;

plus:PLUS | MINUS;

term: factor ( multiply factor )*;

multiply:MULTIPLY | DIVIDE;

factor: IDENTIFIER | INTEGER | LPAREN expression RPAREN;

emptyStatement: ;

// 忽略空白字符
WS: [ \t\r\n]+ -> skip;

