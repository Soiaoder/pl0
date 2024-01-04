import Pl0.PL0Lexer;
import Pl0.PL0Parser;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Main {
    public static void main(String[] args) {
        String filePath = "D://CompilationPrinciples//grammer//src//test.txt";  // 输入文件路径
        String outputFilePath = "D://CompilationPrinciples//grammer//src//result.txt"; // 结果文件路径
        try {
            String sourceCode = readFromFile(filePath);
            PL0Lexer lexer = new PL0Lexer(CharStreams.fromString(sourceCode));
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            PL0Parser parser = new PL0Parser(tokens);

            // 获取语法树的根节点
            PL0Parser.ProgramContext tree = parser.program();

            // 使用自定义的Visitor遍历语法树，生成中间代码
            MyPL0Visitor visitor = new MyPL0Visitor();
            visitor.visit(tree);

            // 获取生成的中间代码字符串
            ArrayList<IntermediateCode> codeResult = visitor.getCodeResult();
            Collections.sort(codeResult, Comparator.comparingInt(IntermediateCode::getstart)); // 按照开始地址排序
            // 输出到文件
            writeToFile(outputFilePath, codeResult);
            // 结果打印到控制台
            for (IntermediateCode code : codeResult) {
                System.out.println(code.toString());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    // 读取文件
    private static String readFromFile(String filePath) throws IOException {
        Path path = Paths.get(filePath);
        byte[] encoded = Files.readAllBytes(path);
        return new String(encoded, StandardCharsets.UTF_8);
    }
    // 结果写到文件中
    private static void writeToFile(String filePath, ArrayList<IntermediateCode> codeResult) {
        try (PrintWriter writer = new PrintWriter(filePath)) {
            for (IntermediateCode code : codeResult) {
                writer.println(code.toString());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}

