
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3;

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }
    
    if(multiply(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }
    
    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
}
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
//MATH HELPERS
int find_numerator(int chara, int num, int denom)
{
    if(chara < 0)
    {
        return ((abs(chara) * denom) + num) * -1;
    }
    else
    {
        return (chara * denom) + num;
    }
}
//--
int find_char_length(int char_num)
{
    //finding number of digits in characteristic
    int char_length = 0;
    int temp_char = abs(char_num);
    
    //setting char_lenght = 1 if the characteristic is 0
    if(temp_char == 0)
    {
        char_length = 1;
    }
    else
    {
        while(temp_char > 0)
        {
            char_length++;
            //mod dividing by 10 for each digit
            temp_char = (temp_char / 10);
        }
    }
    
    return char_length;
}
//--
bool is_neg(int char_num, int answer_num, int answer_denom)
{
    //if char_num is negative
    if(char_num < 0)
    {
        return true;
    }
    //special case in divide -- answer should be positive when two negatives are divided
    else if(char_num == 0 && answer_denom < 0 && answer_num < 0)
    {
        return false;
    }
    //if char_num is 0 but the answer is negative (ex. -0.5625)
    else if(char_num == 0 && (answer_num < 0 || answer_denom < 0))
    {
        return true;
    }
    //if char_num is positive
    else
    {
        return false;
    }
}
//--
void fill_result(int char_length, int char_num, int answer_num, int answer_denom, int len, bool neg, char result[])
{
    //fill characteristic
    //if the number is negative
    if(neg)
    {
        //adding space for - sign & getting the abs val of the characteristic & numerator
        char_length++;
        char_num = abs(char_num);
        answer_num = abs(answer_num);
        //also getting the abs val of the denominator for negative division cases
        answer_denom = abs(answer_denom);
        
        //filling result w/ characteristic digits
        for(int i = char_length; i >= 0; i--)
        {
            //placing \0 at end of characteristic
            if(i == char_length)
            {
                result[i] = '\0';
            }
            //adding negative sign at the beginning
            else if (i == 0)
            {
                result[i] = '-';
            }
            //setting result at pos i to each digit
            else
            {
                result[i] = (char_num % 10) + '0';
                char_num = (char_num / 10);
            }
        }
    }
    //if the number is positive
    else
    {
        //filling result w/ characteristic digits
        for(int i = char_length; i >= 0; i--)
        {
            //placing \0 at end of characteristic
            if(i == char_length)
            {
                result[i] = '\0';
            }
            //setting result at pos i to each digit
            else
            {
                result[i] = (char_num % 10) + '0';
                char_num = (char_num / 10);
            }
        }
    }
    
    //fill mantissa
    //only add a decimal & mantissa if the answer is not a whole number
    if(answer_num % answer_denom != 0)
    {
        //filling result w/ mantissa digits starting from char_length
        int remain = (answer_num % answer_denom);
        int dividend = (remain * 10);
        int digit = (dividend / answer_denom);
        for(int i = char_length; i < (len - 1); i++)
        {
            //placing . between characteristic & mantissa
            if(i == char_length)
            {
                result[i] = '.';
            }
            //setting result at pos i to each digit
            else
            {
                result[i] = '0' + digit;
                
                remain = (dividend % answer_denom);
                dividend = (remain * 10);
                digit = (dividend / answer_denom);
            }
        }
    }
    
    //remove trailing zeroes
    for(int i = (len - 2); i > char_length; i--)
    {
        while(result[i] == '0')
        {
            result[i] = '\0';
        }
    }
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //checking for 0 division
    if(d1 == 0 || d2 == 0) {
        return false;
    }
    else
    {
        //converting into two fractions
        int new_num1 = find_numerator(c1, n1, d1);
        int new_num2 = find_numerator(c2, n2, d2);
        
        //multiplying the numerators by the opposite denominator & adding
        int answer_num = (new_num1 * d2) + (new_num2 * d1);
        //multiplying the denominators
        int answer_denom = d1 * d2;
        
        //get the characteristic
        int char_num = (answer_num / answer_denom);
        bool neg = is_neg(char_num, answer_num, answer_denom);
        
        //finding number of digits in characteristic
        int char_length = find_char_length(char_num);
        //returning false if the characteristic exceeds result size
        if(char_length > (len - 1))
        {
            return false;
        }
        
        //filling result w/ characteristic & mantissa
        fill_result(char_length, char_num, answer_num, answer_denom, len, neg, result);
        
        return true;
    }
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //checking for 0 division
    if(d1 == 0 || d2 == 0) {
        return false;
    }
    else
    {
        //converting into two fractions
        int new_num1 = find_numerator(c1, n1, d1);
        int new_num2 = find_numerator(c2, n2, d2);
        
        //multiplying the numerators by the opposite denominator & subtracting
        int answer_num = (new_num1 * d2) - (new_num2 * d1);
        //multiplying the denominators
        int answer_denom = d1 * d2;
        
        //get the characteristic
        int char_num = (answer_num / answer_denom);
        bool neg = is_neg(char_num, answer_num, answer_denom);
        
        //finding number of digits in characteristic
        int char_length = find_char_length(char_num);
        //returning false if the characteristic exceeds result size
        if(char_length > (len - 1))
        {
            return false;
        }
        
        //filling result w/ characteristic & mantissa
        fill_result(char_length, char_num, answer_num, answer_denom, len, neg, result);
        
        return true;
    }
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //checking for 0 division
    if(d1 == 0 || d2 == 0) {
        return false;
    }
    else
    {
        //converting into two fractions
        int new_num1 = find_numerator(c1, n1, d1);
        int new_num2 = find_numerator(c2, n2, d2);
        
        //multiplying the fractions together
        int answer_num = new_num1 * new_num2;
        int answer_denom = d1 * d2;
        
        //get the characteristic
        int char_num = (answer_num / answer_denom);
        bool neg = is_neg(char_num, answer_num, answer_denom);
        
        //finding number of digits in characteristic
        int char_length = find_char_length(char_num);
        //returning false if the characteristic exceeds result size
        if(char_length > (len - 1))
        {
            return false;
        }
        
        //filling result w/ characteristic & mantissa
        fill_result(char_length, char_num, answer_num, answer_denom, len, neg, result);
        
        return true;
    }
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //checking for 0 division
    if(d1 == 0 || d2 == 0) {
        return false;
    }
    else
    {
        //converting into two fractions
        int new_num1 = find_numerator(c1, n1, d1);
        //swapping the numerator & denominator of 2nd fraction
        int new_num2 = d2;
        int new_denom2 = find_numerator(c2, n2, d2);
        
        //multiplying the fractions together
        int answer_num = new_num1 * new_num2;
        int answer_denom = d1 * new_denom2;
        
        //get the characteristic
        int char_num = (answer_num / answer_denom);
        bool neg = is_neg(char_num, answer_num, answer_denom);
        
        //finding number of digits in characteristic
        int char_length = find_char_length(char_num);
        //returning false if the characteristic exceeds result size
        if(char_length > (len - 1))
        {
            return false;
        }
        
        //filling result w/ characteristic & mantissa
        fill_result(char_length, char_num, answer_num, answer_denom, len, neg, result);
        
        return true;
    }
}
