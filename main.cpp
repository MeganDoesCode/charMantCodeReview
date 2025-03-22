
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
    return (chara * denom) + num;
}
//--
int find_chara_length(int char_num)
{
    //finding number of digits in characteristic
    int char_length = 0;
    int temp_char = char_num;
    while(temp_char > 0)
    {
        char_length++;
        //mod dividing by 10 for each digit
        temp_char = (temp_char / 10);
    }
    
    return char_length;
}
//--
/*void fill_characteristic(int char_length, int char_num, char (&result)[])
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
}*/
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
        
        //finding number of digits in characteristic
        int char_length = find_chara_length(char_num);
        
        if(char_length > (len - 1))
        {
            return false;
        }
        
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
        
        //finding number of digits in characteristic
        int char_length = find_chara_length(char_num);
        
        if(char_length > (len - 1))
        {
            return false;
        }
        return true;
    }
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}
