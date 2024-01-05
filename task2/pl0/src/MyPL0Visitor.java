import Pl0.PL0BaseVisitor;
import Pl0.PL0Parser;

import java.util.ArrayList;

public class MyPL0Visitor extends PL0BaseVisitor<String> {
    // 创建ArrayList来存储结果
    public ArrayList<IntermediateCode> codeResult = new ArrayList<>();

    private int labelCounter = 99; // 用于生成唯一的标签，地址
    private int number = 0; // 中间存储变量的序号


    @Override
    public String visitWhileStatement(PL0Parser.WhileStatementContext ctx) {
        String expression0 = visitExpression(ctx.condition().expression(0)); // 获得关系表达式的第一个元素
        String operator = ctx.condition().getChild(1).getText();  //  比较符
        String expression1 = visitExpression(ctx.condition().expression(1));// 关系表达式对的参数二
        labelCounter++;// 输入一条结果前，地址+1
        int startLabel = labelCounter; // while的起始地址，之后循环跳回来
        codeResult.add(new IntermediateCode(startLabel,"j"+operator, expression0, expression1, String.valueOf(startLabel+2)));
        labelCounter++; //
        int startLabel2 = labelCounter; // while的跳出循环地址

        visit(ctx.statement()); // 循环体的内容

        labelCounter++;
        // 跳回循环开始的地址，继续下一次循环
        codeResult.add(new IntermediateCode(labelCounter,"j", "-", "-", String.valueOf(startLabel)));
        // 跳出循环的指令
        codeResult.add(new IntermediateCode(startLabel2,"j", "-", "-", String.valueOf(labelCounter+1)));

        return null;
    }

    @Override
    public String visitIfStatement(PL0Parser.IfStatementContext ctx) {
        String expression0 = visitExpression(ctx.condition().expression(0)); // 获得关系表达式的第一个元素
        String operator = ctx.condition().getChild(1).getText();  //  比较符
        String expression1 = visitExpression(ctx.condition().expression(1));// 关系表达式对的参数二
        labelCounter++;// if的关系表达式开始的地址
        int startLabel = labelCounter;
        codeResult.add(new IntermediateCode(startLabel,"j"+operator, expression0, expression1, String.valueOf(startLabel+2)));
        labelCounter++;// 关系表达式不成立
        int startLabel2=labelCounter;
        visit(ctx.statement(0)); // THEN里的内容
        // 关系表达式不成立跳出
        codeResult.add(new IntermediateCode(startLabel2,"j", "-", "-", String.valueOf(labelCounter+1)));

        return null;
    }

    @Override
    public String visitAssignmentStatement(PL0Parser.AssignmentStatementContext ctx) {
        String identifier = ctx.IDENTIFIER().getText();   // 标识符
        String expression0 = visitExpression(ctx.expression());  // 赋值的参数
        labelCounter++;
        codeResult.add(new IntermediateCode(labelCounter,":=", expression0, "-",identifier ));
        return null;
    }

    @Override
    public String visitExpression(PL0Parser.ExpressionContext ctx) {
        int retrusion=0; //表达式的项是否因为负号，全体后移一项
        if (ctx.term().size() == 1) {   // 只有一个项
            if(ctx.getChild(0).getText().equals("-")){  // 项前有负号
                retrusion=1;
                labelCounter++;
                String term0=visitTerm(ctx.term(0));
                number++;  // 存储项变号的操作
                codeResult.add(new IntermediateCode(labelCounter,"uminus", term0, "-","T"+number));
                return "T"+number;  // 返回中间存储变量
            }
            else{
                return visitTerm(ctx.term(0)); //项前没负号
            }
        } else {
            String term0=visitTerm(ctx.term(0)); // 第一个项
            if(ctx.getChild(0).getText().equals("-")){  // 第一个项前有负号
                retrusion=1;
                labelCounter++;
                number++;
                codeResult.add(new IntermediateCode(labelCounter,"uminus", term0, "-","T"+number ));
                term0="T"+number;
            }
            for (int j = 1; j < ctx.term().size(); j++) {
                String term1 = visitTerm(ctx.term(j)); // 后一个项
                String operator=ctx.getChild(2*j-1+retrusion).getText(); // 两个变量中间的操作符
                number++;
                labelCounter++;
                codeResult.add(new IntermediateCode(labelCounter,operator, term0, term1,"T"+number ));
                term0 = "T"+number; // 运算完后，结果变为前一个项
            }
            return "T"+number;
        }
    }

    @Override
    public String visitTerm(PL0Parser.TermContext ctx) {
        if (ctx.factor().size() == 1) {  // 只有一个因子
            if(ctx.factor(0).getChild(1)!=null){  // 因子的子节点多于一个，则为（表达式）
                return visitExpression(ctx.factor(0).expression());
            }
            else{    // 因子为标识符或者无符号整数
                return ctx.factor(0).getChild(0).getText();
            }
        } else {
            String factor0 = null;// 第一个因子
            String factor1 = null; // 第二个因子
            if(ctx.factor(0).getChild(1)!=null){  // 因子的子节点多于一个，则为（表达式）
                factor0=visitExpression(ctx.factor(0).expression());
            }
            else{    // 因子为标识符或者无符号整数
                factor0=ctx.factor(0).getChild(0).getText();
            }
            for (int j = 1; j < ctx.factor().size(); j++) {
                if(ctx.factor(j).getChild(1)!=null){  // 因子的子节点多于一个，则为（表达式）
                    factor1=visitExpression(ctx.factor(j).expression());
                }
                else{    // 因子为标识符或者无符号整数
                    factor1=ctx.factor(j).getChild(0).getText();
                }
                String operator=ctx.getChild(2*j-1).getText();  // 因子间的操作符
                number++;
                labelCounter++;
                codeResult.add(new IntermediateCode(labelCounter,operator, factor0, factor1,"T"+number ));
                factor0 = "T"+number; // 同expression一样
            }
            return "T"+number;
        }
    }

   // 返回结果
    public ArrayList<IntermediateCode> getCodeResult() {
        return codeResult;
    }

}
