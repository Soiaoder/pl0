// Generated from D:/bianyuan-final/pl0/src/PL0.g4 by ANTLR 4.13.1
package Pl0;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link PL0Parser}.
 */
public interface PL0Listener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link PL0Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(PL0Parser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(PL0Parser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#programHeader}.
	 * @param ctx the parse tree
	 */
	void enterProgramHeader(PL0Parser.ProgramHeaderContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#programHeader}.
	 * @param ctx the parse tree
	 */
	void exitProgramHeader(PL0Parser.ProgramHeaderContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#subProgram}.
	 * @param ctx the parse tree
	 */
	void enterSubProgram(PL0Parser.SubProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#subProgram}.
	 * @param ctx the parse tree
	 */
	void exitSubProgram(PL0Parser.SubProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#constantDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterConstantDeclaration(PL0Parser.ConstantDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#constantDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitConstantDeclaration(PL0Parser.ConstantDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#constantDefinition}.
	 * @param ctx the parse tree
	 */
	void enterConstantDefinition(PL0Parser.ConstantDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#constantDefinition}.
	 * @param ctx the parse tree
	 */
	void exitConstantDefinition(PL0Parser.ConstantDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(PL0Parser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(PL0Parser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#identifierList}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierList(PL0Parser.IdentifierListContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#identifierList}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierList(PL0Parser.IdentifierListContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#statementPart}.
	 * @param ctx the parse tree
	 */
	void enterStatementPart(PL0Parser.StatementPartContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#statementPart}.
	 * @param ctx the parse tree
	 */
	void exitStatementPart(PL0Parser.StatementPartContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatement(PL0Parser.CompoundStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatement(PL0Parser.CompoundStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(PL0Parser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(PL0Parser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentStatement(PL0Parser.AssignmentStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentStatement(PL0Parser.AssignmentStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(PL0Parser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(PL0Parser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(PL0Parser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(PL0Parser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(PL0Parser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(PL0Parser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(PL0Parser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(PL0Parser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#plus}.
	 * @param ctx the parse tree
	 */
	void enterPlus(PL0Parser.PlusContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#plus}.
	 * @param ctx the parse tree
	 */
	void exitPlus(PL0Parser.PlusContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(PL0Parser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(PL0Parser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#multiply}.
	 * @param ctx the parse tree
	 */
	void enterMultiply(PL0Parser.MultiplyContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#multiply}.
	 * @param ctx the parse tree
	 */
	void exitMultiply(PL0Parser.MultiplyContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(PL0Parser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(PL0Parser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(PL0Parser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(PL0Parser.EmptyStatementContext ctx);
}