// Generated from D:/CompilationPrinciples/grammer/src/PL0.g4 by ANTLR 4.13.1
package Pl0;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class PL0Lexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		PROGRAM=1, BEGIN=2, END=3, CONST=4, VAR=5, WHILE=6, DO=7, IF=8, THEN=9, 
		ELSE=10, IDENTIFIER=11, INTEGER=12, PLUS=13, MINUS=14, MULTIPLY=15, DIVIDE=16, 
		ASSIGN=17, EQUAL=18, NOTEQUAL=19, LESS=20, LESSEQUAL=21, GREATER=22, GREATEREQUAL=23, 
		LPAREN=24, RPAREN=25, SEMICOLON=26, COMMA=27, WS=28;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"PROGRAM", "BEGIN", "END", "CONST", "VAR", "WHILE", "DO", "IF", "THEN", 
			"ELSE", "IDENTIFIER", "INTEGER", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", 
			"ASSIGN", "EQUAL", "NOTEQUAL", "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", 
			"LPAREN", "RPAREN", "SEMICOLON", "COMMA", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'PROGRAM'", "'BEGIN'", "'END'", "'CONST'", "'VAR'", "'WHILE'", 
			"'DO'", "'IF'", "'THEN'", "'ELSE'", null, null, "'+'", "'-'", "'*'", 
			"'/'", "':='", "'='", "'<>'", "'<'", "'<='", "'>'", "'>='", "'('", "')'", 
			"';'", "','"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "PROGRAM", "BEGIN", "END", "CONST", "VAR", "WHILE", "DO", "IF", 
			"THEN", "ELSE", "IDENTIFIER", "INTEGER", "PLUS", "MINUS", "MULTIPLY", 
			"DIVIDE", "ASSIGN", "EQUAL", "NOTEQUAL", "LESS", "LESSEQUAL", "GREATER", 
			"GREATEREQUAL", "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public PL0Lexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "PL0.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u001c\u00a5\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0002\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014"+
		"\u0002\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017"+
		"\u0002\u0018\u0007\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a"+
		"\u0002\u001b\u0007\u001b\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\n\u0001\n\u0005\nn\b\n\n\n\f\nq\t\n\u0001\u000b\u0001"+
		"\u000b\u0001\u000b\u0005\u000bv\b\u000b\n\u000b\f\u000by\t\u000b\u0003"+
		"\u000b{\b\u000b\u0001\f\u0001\f\u0001\r\u0001\r\u0001\u000e\u0001\u000e"+
		"\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011"+
		"\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018"+
		"\u0001\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001b\u0004\u001b"+
		"\u00a0\b\u001b\u000b\u001b\f\u001b\u00a1\u0001\u001b\u0001\u001b\u0000"+
		"\u0000\u001c\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004\t\u0005\u000b"+
		"\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017\f\u0019\r\u001b"+
		"\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'\u0014)\u0015+\u0016"+
		"-\u0017/\u00181\u00193\u001a5\u001b7\u001c\u0001\u0000\u0005\u0002\u0000"+
		"AZaz\u0003\u000009AZaz\u0001\u000019\u0001\u000009\u0003\u0000\t\n\r\r"+
		"  \u00a8\u0000\u0001\u0001\u0000\u0000\u0000\u0000\u0003\u0001\u0000\u0000"+
		"\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000\u0007\u0001\u0000\u0000"+
		"\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b\u0001\u0000\u0000\u0000"+
		"\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001\u0000\u0000\u0000\u0000"+
		"\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001\u0000\u0000\u0000\u0000"+
		"\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001\u0000\u0000\u0000\u0000"+
		"\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001\u0000\u0000\u0000\u0000"+
		"\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001\u0000\u0000\u0000\u0000"+
		"!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000\u0000\u0000\u0000%\u0001"+
		"\u0000\u0000\u0000\u0000\'\u0001\u0000\u0000\u0000\u0000)\u0001\u0000"+
		"\u0000\u0000\u0000+\u0001\u0000\u0000\u0000\u0000-\u0001\u0000\u0000\u0000"+
		"\u0000/\u0001\u0000\u0000\u0000\u00001\u0001\u0000\u0000\u0000\u00003"+
		"\u0001\u0000\u0000\u0000\u00005\u0001\u0000\u0000\u0000\u00007\u0001\u0000"+
		"\u0000\u0000\u00019\u0001\u0000\u0000\u0000\u0003A\u0001\u0000\u0000\u0000"+
		"\u0005G\u0001\u0000\u0000\u0000\u0007K\u0001\u0000\u0000\u0000\tQ\u0001"+
		"\u0000\u0000\u0000\u000bU\u0001\u0000\u0000\u0000\r[\u0001\u0000\u0000"+
		"\u0000\u000f^\u0001\u0000\u0000\u0000\u0011a\u0001\u0000\u0000\u0000\u0013"+
		"f\u0001\u0000\u0000\u0000\u0015k\u0001\u0000\u0000\u0000\u0017z\u0001"+
		"\u0000\u0000\u0000\u0019|\u0001\u0000\u0000\u0000\u001b~\u0001\u0000\u0000"+
		"\u0000\u001d\u0080\u0001\u0000\u0000\u0000\u001f\u0082\u0001\u0000\u0000"+
		"\u0000!\u0084\u0001\u0000\u0000\u0000#\u0087\u0001\u0000\u0000\u0000%"+
		"\u0089\u0001\u0000\u0000\u0000\'\u008c\u0001\u0000\u0000\u0000)\u008e"+
		"\u0001\u0000\u0000\u0000+\u0091\u0001\u0000\u0000\u0000-\u0093\u0001\u0000"+
		"\u0000\u0000/\u0096\u0001\u0000\u0000\u00001\u0098\u0001\u0000\u0000\u0000"+
		"3\u009a\u0001\u0000\u0000\u00005\u009c\u0001\u0000\u0000\u00007\u009f"+
		"\u0001\u0000\u0000\u00009:\u0005P\u0000\u0000:;\u0005R\u0000\u0000;<\u0005"+
		"O\u0000\u0000<=\u0005G\u0000\u0000=>\u0005R\u0000\u0000>?\u0005A\u0000"+
		"\u0000?@\u0005M\u0000\u0000@\u0002\u0001\u0000\u0000\u0000AB\u0005B\u0000"+
		"\u0000BC\u0005E\u0000\u0000CD\u0005G\u0000\u0000DE\u0005I\u0000\u0000"+
		"EF\u0005N\u0000\u0000F\u0004\u0001\u0000\u0000\u0000GH\u0005E\u0000\u0000"+
		"HI\u0005N\u0000\u0000IJ\u0005D\u0000\u0000J\u0006\u0001\u0000\u0000\u0000"+
		"KL\u0005C\u0000\u0000LM\u0005O\u0000\u0000MN\u0005N\u0000\u0000NO\u0005"+
		"S\u0000\u0000OP\u0005T\u0000\u0000P\b\u0001\u0000\u0000\u0000QR\u0005"+
		"V\u0000\u0000RS\u0005A\u0000\u0000ST\u0005R\u0000\u0000T\n\u0001\u0000"+
		"\u0000\u0000UV\u0005W\u0000\u0000VW\u0005H\u0000\u0000WX\u0005I\u0000"+
		"\u0000XY\u0005L\u0000\u0000YZ\u0005E\u0000\u0000Z\f\u0001\u0000\u0000"+
		"\u0000[\\\u0005D\u0000\u0000\\]\u0005O\u0000\u0000]\u000e\u0001\u0000"+
		"\u0000\u0000^_\u0005I\u0000\u0000_`\u0005F\u0000\u0000`\u0010\u0001\u0000"+
		"\u0000\u0000ab\u0005T\u0000\u0000bc\u0005H\u0000\u0000cd\u0005E\u0000"+
		"\u0000de\u0005N\u0000\u0000e\u0012\u0001\u0000\u0000\u0000fg\u0005E\u0000"+
		"\u0000gh\u0005L\u0000\u0000hi\u0005S\u0000\u0000ij\u0005E\u0000\u0000"+
		"j\u0014\u0001\u0000\u0000\u0000ko\u0007\u0000\u0000\u0000ln\u0007\u0001"+
		"\u0000\u0000ml\u0001\u0000\u0000\u0000nq\u0001\u0000\u0000\u0000om\u0001"+
		"\u0000\u0000\u0000op\u0001\u0000\u0000\u0000p\u0016\u0001\u0000\u0000"+
		"\u0000qo\u0001\u0000\u0000\u0000r{\u00050\u0000\u0000sw\u0007\u0002\u0000"+
		"\u0000tv\u0007\u0003\u0000\u0000ut\u0001\u0000\u0000\u0000vy\u0001\u0000"+
		"\u0000\u0000wu\u0001\u0000\u0000\u0000wx\u0001\u0000\u0000\u0000x{\u0001"+
		"\u0000\u0000\u0000yw\u0001\u0000\u0000\u0000zr\u0001\u0000\u0000\u0000"+
		"zs\u0001\u0000\u0000\u0000{\u0018\u0001\u0000\u0000\u0000|}\u0005+\u0000"+
		"\u0000}\u001a\u0001\u0000\u0000\u0000~\u007f\u0005-\u0000\u0000\u007f"+
		"\u001c\u0001\u0000\u0000\u0000\u0080\u0081\u0005*\u0000\u0000\u0081\u001e"+
		"\u0001\u0000\u0000\u0000\u0082\u0083\u0005/\u0000\u0000\u0083 \u0001\u0000"+
		"\u0000\u0000\u0084\u0085\u0005:\u0000\u0000\u0085\u0086\u0005=\u0000\u0000"+
		"\u0086\"\u0001\u0000\u0000\u0000\u0087\u0088\u0005=\u0000\u0000\u0088"+
		"$\u0001\u0000\u0000\u0000\u0089\u008a\u0005<\u0000\u0000\u008a\u008b\u0005"+
		">\u0000\u0000\u008b&\u0001\u0000\u0000\u0000\u008c\u008d\u0005<\u0000"+
		"\u0000\u008d(\u0001\u0000\u0000\u0000\u008e\u008f\u0005<\u0000\u0000\u008f"+
		"\u0090\u0005=\u0000\u0000\u0090*\u0001\u0000\u0000\u0000\u0091\u0092\u0005"+
		">\u0000\u0000\u0092,\u0001\u0000\u0000\u0000\u0093\u0094\u0005>\u0000"+
		"\u0000\u0094\u0095\u0005=\u0000\u0000\u0095.\u0001\u0000\u0000\u0000\u0096"+
		"\u0097\u0005(\u0000\u0000\u00970\u0001\u0000\u0000\u0000\u0098\u0099\u0005"+
		")\u0000\u0000\u00992\u0001\u0000\u0000\u0000\u009a\u009b\u0005;\u0000"+
		"\u0000\u009b4\u0001\u0000\u0000\u0000\u009c\u009d\u0005,\u0000\u0000\u009d"+
		"6\u0001\u0000\u0000\u0000\u009e\u00a0\u0007\u0004\u0000\u0000\u009f\u009e"+
		"\u0001\u0000\u0000\u0000\u00a0\u00a1\u0001\u0000\u0000\u0000\u00a1\u009f"+
		"\u0001\u0000\u0000\u0000\u00a1\u00a2\u0001\u0000\u0000\u0000\u00a2\u00a3"+
		"\u0001\u0000\u0000\u0000\u00a3\u00a4\u0006\u001b\u0000\u0000\u00a48\u0001"+
		"\u0000\u0000\u0000\u0005\u0000owz\u00a1\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}