public class IntermediateCode {
    public int start; //  开始地址
    public String operate; // 运算符

    public String arg1; // 参数1
    public String arg2;
    public String result; // 结果，地址或者参数

    public int getstart() {
        return start;
    }

    public void setstart(int start) {
        this.start = start;
    }

    public String getoperate() {
        return operate;
    }

    public void setoperate(String operate) {
        this.operate = operate;
    }

    public String getarg1() {
        return arg1;
    }

    public void setarg1(String arg1) {
        this.arg1 = arg1;
    }

    public String getarg2() {
        return arg2;
    }

    public void setarg2(String arg2) {
        this.arg2 = arg2;
    }

    public String getresult() {
        return result;
    }

    public void setresult(String result) {
        this.result = result;
    }



    public IntermediateCode(int start, String operate, String arg1, String arg2, String result) {
        this.start = start;
        this.operate = operate;
        this.arg1 = arg1;
        this.arg2 = arg2;
        this.result = result;
    }
    // 结果格式化
    @Override
    public String toString() {
        // 返回表示该对象内容的字符串，例如：
        return start+"(" + operate + ", " + arg1 + ", " + arg2 + ", " + result + ")";
    }
}
