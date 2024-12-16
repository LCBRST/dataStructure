#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 100
//判断表达式的优先级
int symcmp(char a, char b)
{
	if (b == '(')
		return 1;
	else if ((b == '*' || b == '/') && (a == '+' || a == '-' || a == '('))
		return 1;
	else if ((b == '+' || b == '-') && (a == '('))
		return 1;
	else
		return 0;
}
//计算运算值栈顶两个元素(a栈顶第一个元素，b栈顶第二个元素)
int calculate(char c,int a,int b)
{
	int tmp = 0;
	switch (c)
	{
	    case '+':tmp = b + a; break;
	    case '-':tmp = b - a; break;
	    case '*':tmp = b * a; break;
	    case '/':tmp = b / a; break;
	}
	return tmp;
}

//计算中缀表达式
int calculate_expression(char *str)
{
	int num_stack[MAXSIZE]; //运算值栈
	int num_top = -1; //运算值栈指针
	char sym_stack[MAXSIZE]; //操作符栈
	int sym_top = -1; //操作符栈指针
	int i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]))//判断是否是数字字符
		{
			//将数字字符转换为数值型并入栈
		    int  val = 0;
			while (isdigit(str[i]))
			{
				val = val * 10 + str[i] - '0';
				i++;
			}
			num_stack[++num_top] = val;
		}
		else //符号
		{
			if (str[i] == ')')
			{
				while (sym_stack[sym_top] != '(')
				{
					int ret = calculate(sym_stack[sym_top], num_stack[num_top], num_stack[num_top - 1]); //计算栈顶两个元素
					sym_top--;
					num_top -= 2;
					num_stack[++num_top] = ret;
				}
				sym_top--;
				i++;
			}
			else if (!symcmp(sym_stack[sym_top], str[i]))
			{
				while (sym_top > -1 && (!symcmp(sym_stack[sym_top], str[i])))
				{
					int ret = calculate(sym_stack[sym_top], num_stack[num_top], num_stack[num_top - 1]); //计算栈顶两个元素
					sym_top--;
					num_top -= 2;
					num_stack[++num_top] = ret;
				}
				sym_stack[++sym_top] = str[i];
				i++;
			}
			else
			{
				sym_stack[++sym_top] = str[i];
				i++;
			}
		}
	}
	while (sym_top > -1)
	{
		int ret = calculate(sym_stack[sym_top], num_stack[num_top], num_stack[num_top - 1]); //计算栈顶两个元素
		sym_top--;
		num_top -= 2;
		num_stack[++num_top] = ret;
	}
	return num_stack[0];
}
int main()
{
	char *str = "12+3*(15/(2+7))-2";
	int ret = calculate_expression(str);
	printf("表达式的结果是：%d\n", ret);
	return 0;
}
