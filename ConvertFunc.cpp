#include "ConvertFunc.h"

double calc(const double& num1, const double& num2, const char& op){
    double res;
    switch(op){
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        res = num1 / num2;
        break;
    case '%':
        //may occur error answer!
        if((int)num2 == 0)
            res = std::nanf("1");
        else
            res = (int)num1 % (int)num2;
        break;
    case '^':
        res = pow(num1, num2);
        break;
    case '.': {
        QString integer(QString::asprintf("%d", (int)num1));
        QString fracture(QString::asprintf("%d", (int)num2));
        fracture.remove(0, 1);  //remove the first 0
        QString num;
        num.append(integer);
        num.append('.');
        num.append(fracture);
        res = num.toDouble();
        break;
        }
    default:
        res = 0;
        break;
    }
    return res;
}

void Expression::rebuildStacks(){
    QString tempString = expString;
    opStack.Empty();
    numStack.Empty();
    errorInput.Empty();
    expString.clear();
    inputCons = 0b101011;
    for(int i = 0; i < tempString.length(); i++){
        insert(tempString[i].toLatin1());
    }
}

void Expression::update(int index = -1){
    while(numStack.Size() > 1 && !opStack.IsEmpty() && opMap[opStack.TopElement()] >= index && opStack.TopElement() != '('){
        double num2 = numStack.PopBack();
        double num1 = numStack.PopBack();
        char op = opStack.PopBack();
        double res = calc(num1, num2, op);
        numStack.PushBack(res);

        //count the differences in stacks
        numChange.append('o');
        numChange.append('o');
        opChange.append('o');
        numChange.append(QString::asprintf("i%lf", res));
    }
    //enable fracture
    inputCons |= 0b000010;
}

void Expression::insert(char c){
    //clear last step differences in stacks
    opChange.clear();
    numChange.clear();

    if(c == '#'){
        update();
        return;
    }
    if(!errorInput.IsEmpty())
        //Error stack is not empty, regard as error input.
        errorInput.PushBack(c);
    else if(c == '('){
        if(inputCons & 0b100000){
            opStack.PushBack(c);

            opChange.append(QString::asprintf("i%c", c));

            //allow minus numbers
            inputCons |= 0b000001;
        }
        else
            errorInput.PushBack(c);
    }
    else if(c == ')'){
        if(inputCons & 0b010000){
            update();
            if(opStack.TopElement() == '('){
                opStack.PopBack();

                opChange.append('o');

                //set constraints
                inputCons &= 0b010110;
            }
            else
                errorInput.PushBack(c);
        }
        else
            errorInput.PushBack(c);
    }
    else if(c == '.'){
        if((inputCons & 0b000110) == 0b000110){
            //accept dot
            opStack.PushBack(c);
            numStack.PushBack(1);

            opChange.append(QString::asprintf("i%c", c));
            numChange.append("i1");

            //stop accept dots and operators
            inputCons &= 0b001010;
        }
        else
            errorInput.PushBack(c);
    }
    else if(c >= '0' && c <= '9'){
        if(inputCons & 0b001000){
            if(inputCons & 0b010000 || opStack.TopElement() == '.'){
                //not the first number
                double i = numStack.PopBack();
                i *= 10;
                i += (c - '0');
                numStack.PushBack(i);

                numChange.append(QString::asprintf("oi%lf", i));
            }
            else{
                double i = c - '0';
                numStack.PushBack(i);
                //qDebug() << c - '0' << "\n";
                numChange.append(QString::asprintf("i%lf", i));
            }
            inputCons &= 0b011110;
            inputCons |= 0b010000;
            if(opStack.TopElement() != '.')
                inputCons |= 0b000100;
        }
        else
            errorInput.PushBack(c);
    }
    else if(opMap[c] >= 0){
        if(inputCons & 0b010000){
            //if(opStack.TopElement() == '.'){
            //    double fracture = numStack.PopBack();
            //    double integer = numStack.PopBack();
            //    double res = calc(integer, fracture, opStack.PopBack());
            //    numStack.PushBack(res);
            //}
            update(opMap[c]);
            if(c == '%' && numStack.TopElement() != (int)numStack.TopElement())
                errorInput.PushBack(c);
            else{
                opStack.PushBack(c);

                opChange.append(QString::asprintf("i%c", c));

                //set constraints
                inputCons &= 0b101010;
                inputCons |= 0b101000;
                if(c == '%')
                    inputCons &= 0b111101;
            }
        }
        else{
            if(c == '-' && inputCons & 0b000001){
                //adjust exp string
                if(opStack.TopElement() != '(')
                    expString.append('0');
                //accept minus number
                numStack.PushBack(0);
                opStack.PushBack('-');

                numChange.append("i0");
                opChange.append("i-");

                //stop accepting minus numbers and operators
                inputCons &= 0b101110;
                //allow integers and dots
                inputCons |= 0b101000;
            }
            else
                errorInput.PushBack(c);
        }
    }
    expString.append(c);
}

void Expression::backSpace(){
    opChange.clear();
    numChange.clear();
    expString.chop(1);
    if(!errorInput.IsEmpty())
        errorInput.PopBack();
    else{
        rebuildStacks();
    }
}

QString Expression::expStr(){
    return expString;
}

QString Expression::expToHtml(){
    QString output = expString;
    if(!errorInput.IsEmpty()){
        output.insert(expString.length() - errorInput.Size(), "<span style=\"color:#E56600;\">");
        output.append("</span>");
    }
    return output;
}

QString Expression::resToHtml(){
    QString res;
    if(opStack.IsEmpty() && numStack.Size() == 1 && errorInput.IsEmpty())
        res.append(QString::asprintf("%g", numStack.TopElement()));
    else
        res.append("Syntax Error!");
    return res;
}

void Expression::clr(){
    opStack.Empty();
    numStack.Empty();
    errorInput.Empty();
    expString.clear();
    inputCons = 0b101011;
    numChange.clear();
    opChange.clear();
}

bool Expression::prepare(){
    expString.clear();
    if(opStack.IsEmpty() && numStack.Size() == 1 && errorInput.IsEmpty()){
        expString.append(QString::asprintf("%g", numStack.TopElement()));
        return false;
    }
    else{
        clr();
        return true;
    }
}

QString Expression::numDifStr(){
    return numChange;
}

QString Expression::opDifStr(){
    return opChange;
}

QString Expression::numStackToStr(){
    QString numStr;
    Stack<double> cpy(numStack);
    QVector<double> reverse;
    int n = cpy.Size();
    for(int i = 0; i < n; i++){
        reverse.push_back(cpy.PopBack());
    }
    for(int i = 0; i < n; i++){
        numStr.append(QString::asprintf("i%lf", reverse[n - i - 1]));
    }
    return numStr;
}

QString Expression::opStackToStr(){
    QString opStr;
    Stack<char> cpy(opStack);
    QVector<char> reverse;
    int n = cpy.Size();
    for(int i = 0; i < n; i++){
        reverse.push_back(cpy.PopBack());
    }
    for(int i = 0; i < n; i++){
        opStr.append(QString::asprintf("i%c", reverse[n - i - 1]));
    }
    return opStr;
}
