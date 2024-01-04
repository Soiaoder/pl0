import Pl0.PL0BaseVisitor;
import Pl0.PL0Parser;

import java.util.ArrayList;

public class MyPL0Visitor extends PL0BaseVisitor<Void> {
    // 创建ArrayList来存储结果
    public ArrayList<IntermediateCode> codeResult = new ArrayList<>();

    private int labelCounter = 99; // 用于生成唯一的标签，地址

    @Override
    public Void visitWhileStatement(PL0Parser.WhileStatementContext ctx) {
        String expression0 = ctx.condition().expression(0).getText(); // 获得关系表达式的第一个元素
        String operator = ctx.condition().getChild(1).getText();  //  比较符
        String expression1 = ctx.condition().expression(1).getText();  // 关系表达式对的参数二
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
    public Void visitIfStatement(PL0Parser.IfStatementContext ctx) {
        String expression0 = ctx.condition().expression(0).getText();  // 和while一样，处理关系表达式
        String operator = ctx.condition().getChild(1).getText();
        String expression1 = ctx.condition().expression(1).getText();
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
    public Void visitAssignmentStatement(PL0Parser.AssignmentStatementContext ctx) {
        labelCounter++;

        String identifier = ctx.IDENTIFIER().getText();   // 标识符
        String expression0 = ctx.expression().getChild(0).getText();  // 获取表达式
        if(ctx.expression().getChild(2)!=null){  // x := y+z的情况
            String operator = ctx.expression().getChild(1).getText();
            String expression1 = ctx.expression().getChild(2).getText();
            codeResult.add(new IntermediateCode(labelCounter,operator, expression0, expression1,identifier ));
        }
        else{
            if(ctx.expression().term(0).getChild(2)!=null){ // x := y * z的情况
                String factor0 = ctx.expression().term(0).getChild(0).getText();
                String operator = ctx.expression().term(0).getChild(1).getText();
                String factor1 = ctx.expression().term(0).getChild(2).getText();
                codeResult.add(new IntermediateCode(labelCounter,operator, factor0, factor1,identifier ));
            }
            else{ // x := 1 的情况
                codeResult.add(new IntermediateCode(labelCounter,":=", expression0, "-",identifier ));
            }
        }

        return null;
    }

   // 返回结果
    public ArrayList<IntermediateCode> getCodeResult() {
        return codeResult;
    }

}
