#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <cmath>
#include <map>


using namespace std;


bool isOperator (char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/*Define each operator of his rank  */
int opRank(char c){
    if(c == '^'){
        return 3;
    }else if(c == '*' || c == '/'){
        return 2;
    }else if( c == '+' || c == '-'){
        return 1;
    }
    /*if we put to stack the scope '(' */
    return 0;
}

/*Calculate the result of the simple operations */
void calculate(stack<double> & numbers, char op){
    double res = numbers.top(); // if we have only one number in the scope
    if(numbers.size () > 1){
        double rNum = numbers.top();
        numbers.pop();
        double lNum = numbers.top();
        numbers.pop();
        res = op == '+' ? lNum + rNum :
                          op == '-' ? lNum - rNum :
                                      op == '*' ? lNum * rNum :
                                                  op == '^' ? pow (lNum, rNum):
                                                              lNum/rNum;
    }
    numbers.push (res);
}

/*Calculate the result of the trygonometric function */
void calculate(stack<double> & numbers, string func){
    double res;
    double number = numbers.top();
    numbers.pop();
    if(func == "sqrt"){
        res = sqrt(number);
    }else if(func == "sin"){
        res = sin(number);
    }else if(func == "cos"){
        res = cos(number);
    }else if(func == "ln"){
        res = log(number);
    }else if(func == "abs"){
        res = fabs (number);
    }else if(func == "tan"){
        res = tan (number);
    }else if(func == "lg"){
        res = log10 (number);
    }else if(func == "lb"){
        res = log2 (number);
    }else{
        cout << "Invalid function." << endl;
    }
    numbers.push (res);
}

void parseString(string & input, stack<char> & operators, stack<double> & operands){

    map<char,double> variables; // used for save variables and their values
    stack<string> function; // used for trigonometric and others functions
    //string result = ""; // used for display reverse polish notation
    string strNumber = ""; // used for save number bigger then 9

    for(unsigned int i = 0; i < input.length (); i++){
        if(input[i] == '-' && ((isdigit (input[i + 1]) && input[i - 1] == '(' ) || (i == 0 && isdigit(input[i+1])) )){
            strNumber = "-1";
            operands.push (atof(strNumber.c_str ()));
            operators.push ('*');
            strNumber.clear ();
            //result = result + "-1" + ' ';
        }else if(isdigit (input[i]) || input[i] == '.'){
            if(i+1 == input.length () || isOperator (input[i + 1]) || input[i + 1] == '(' || input[i + 1] == ')'){
                //result = result + input[i] + ' ';
                strNumber = strNumber + input[i];
                operands.push (atof(strNumber.c_str ()));
                strNumber.clear ();
            }else{
                //result = result + input[i];
                strNumber = strNumber + input[i];
            }
        }else if(input[i] == '('){
            operators.push (input[i]);
        }else if(input[i] == ')'){
            while(operators.top() != '('){
                //result = result + operators.top() + ' ';
                calculate(operands, operators.top());
                operators.pop();
            }
            operators.pop();
            if(function.size ()>0){
                calculate(operands, function.top());
                function.pop();
            }
        }else if(isOperator (input[i])){
            while(!operators.empty () && (opRank (operators.top ()) >= opRank(input[i]))){
                //result = result + operators.top() + ' ';
                calculate(operands, operators.top());
                operators.pop();
            }
            operators.push (input[i]);
        }else if(isalpha (input[i])){
            if(isOperator (input[i+1]) || input[i+1] == ')'){
                if(variables.count (input[i])){
                    //result = result + input[i] + ' ';
                    operands.push(variables.find (input[i])->second);
                }else{
                    //result = result + input[i] + ' ';
                    double value;
                    cout << "Enter value of " << input[i] << " :";
                    cin >> value;
                    variables.insert(make_pair(input[i], value));
                    operands.push (value);
                }
            }else if(input[i+1] == '('){
                strNumber = strNumber + input[i];
                function.push (strNumber);
                strNumber.clear();
            }else{
                strNumber = strNumber + input[i];
            }
        }
    }

    /*Check the last operators in the stack */
    if(operators.size () > 0){
        for(unsigned int i = 0; i < operators.size ()-1; i++){
            //result = result + operators.top() + ' ';
            calculate(operands, operators.top());
            operators.pop();
        }
        //result = result + operators.top();
        calculate(operands, operators.top());
        operators.pop (); // delete last operator
    }

    //cout << result << endl;
    cout << operands.top() << endl;

    operands.pop(); // delete last operands
}

int main()
{
    stack<char> operators;
    stack<double> numbers;
    string input;
    while(true){
        cout << "Enter simple formula: ";
        getline(cin, input);
        if(input.empty ()) break;
        parseString(input, operators, numbers);
    }
    return 0;
}
