#include <iostream>
#include <string>
using namespace std;


///======== ADD-ONS ===========

long long itc_len(string str){
    long long res = 0;
    int i = 0;
    while (str[i] != '\0'){
        i++;
    }
    return i;
}


/// to-power function
long long ipow(int number, int pow){
    long long res = 1;
    for(int i = 0; i < pow;i++){
        res *= number;
    }
    return res;
}



/// slice function
string itc_slice_str(string str, int start, int endd){
    string res ="";
    if ( endd >= itc_len(str)){
        endd = itc_len(str) - 1;
    }
    if(start > endd){
        return str;
    }else if(start == (itc_len(str) - 1)){
        res += str[itc_len(str) - 1];
        return res;
    }else{
        for ( long long i = start; i <= endd; i++){
        res += str[i];
    }
    return res;
    }

    return "-1";
}





/// whole part to binary converter
string to_bin(long long number){

    string res = "";

    for (int i = 0; number > 0; i++){
            if ( number % 2 == 1){
                res = "1" + res;
            }
        else{
            res = "0" + res;
        }
        number = number / 2;
    }
    return res;

}

///dec to binary converter

string dec_bin_f(long long num, long long len_dec){
    string res ="";
    for ( int i = 0; i < 26; i++){
        num = (num*2);
        if ( num /   ipow(10, len_dec) == 1){
            res = res +"1";
        }else{
            res = res + "0";
        }
        num = num %   ipow(10, len_dec);
    }
    return res;

}



/// ====== MAIN ======
int main()
{
    /// get the number
    string str;
    cout << "Enter the number" << endl;
    cin >> str;

    //cout <<"Your Number: " <<  str << endl;
    if (str == "inf" || str == "INF"){
        cout << "01111111100000000000000000000000";
    }else if ( str == "-inf" || str == "-INF"){
        cout << "11111111100000000000000000000000";
    } else if ( str == "0"){
        cout << "00000000000000000000000000000000";
    }else if (str == "-0"){
        cout << "10000000000000000000000000000000";
    }else{


    ///set the first bit - sign
    string sign = "0";
    if  (str[0] == '-'){
        str = itc_slice_str(str, 1, itc_len(str));
        sign = "1";
    }
    if ( str[0] == "+"){
        str = itc_slice_str(str, 1, itc_len(str));
        sign = "0";
    }
    //cout  << "sign:  " << sign << endl;



    /// set the numbers
    long long whole = 0, dec = 0, i =0;
    string whole_str, dec_str;
    int ch = 0;





    /// divide into two parts
    for (i = 0; str[i] != '\0'; i++){
        if ( str[i] == '.' || str[i] == ','){
            whole_str = itc_slice_str(str, 0, i-1);
            dec_str = itc_slice_str(str, i+1, itc_len(str));
        }
    }
    //cout << "Whole_str:  " << whole_str<< endl;
    //cout << "Dec_str:   " << dec_str << endl;




    /// convert whole to number

    //cout << endl;
    //cout << endl;
    //cout << "CONVERTING WHOLE TO NUMBER: START" << endl;

    for(i = 0 ; i < itc_len(whole_str); i++){

            ch = whole_str[i];
            //cout << "Char taken:  " << ch << endl;
            ch -= 48;
            //cout << "Convert to num:   " << ch << endl;
            whole = whole*10 + ch;
            //cout << "WHOLE: " << whole << endl;
            //cout << endl;
    }

    //cout << "CONVERTING WHOLE TO NUMBER: END" << endl;
    //cout << endl;
    //cout << endl;

    /// convert dec to number
    ///(lost zeros will be kept in track by len_dec)
    long long len_dec = itc_len(dec_str);

    //cout << "LEN DEC:  " << len_dec << endl;
    for  ( i = 0; i < len_dec; i++){
        ch = dec_str[i];
        ch -= 48;
        dec  = dec*10 + ch;
    }
    //cout << "DEC:   " << dec << endl;
    //cout << endl;
    /// convert parts to binary

    string whole_bin, dec_bin;
    whole_bin = to_bin(whole);
    //cout << "WHOLE TO BINARY:  " << whole_bin << endl;

    /// convert dec to binary
    dec_bin = dec_bin_f(dec, len_dec);
    //cout << "DEC TO BINARY:  " << dec_bin << endl;
    //cout << endl;
    //cout << endl;
    //cout << "Whole bin:" << endl;
    //cout << whole_bin <<endl;
    //cout << endl;
    //cout << "Dec bin:" << endl;
    //cout << dec_bin << endl;
    //cout << endl;


    /// ===== CREATE MANTISSA AND COUNT EXPONENT ==========
    string mantissa = "";
    long long whole_len = itc_len(whole_bin);
    long long exponent  = 0;
    if ( whole == 0 || whole_bin == "0"){
            long long i = 0;
        while ( dec_bin[i] != '1'){
            exponent++;
            i++;
        }
        //cout << "EXPONENT:  " << exponent << endl;
        mantissa  = itc_slice_str(dec_bin, exponent, itc_len(dec_bin));
        //cout << "MANTISSA:  " << mantissa << endl;
        exponent = 127 - exponent;
    }
    else if(whole_bin == "1"){
        mantissa = dec_bin;
        exponent = 127;
    }
    else{

        mantissa = itc_slice_str(whole_bin, 1, itc_len(whole_str)+1) + dec_bin;
        //cout << "MANTISSA:  " << mantissa << endl;

        exponent = whole_len - 1;
        //cout << "EXPONENT:  " << exponent << endl;
        exponent = 127 + exponent;
    }

    mantissa = itc_slice_str(mantissa, 0, 22);
    long long len_mantissa = itc_len(mantissa);
    if ( len_mantissa < 23){
       for ( i = 0; itc_len(mantissa) != 23 ;i++){
        mantissa += "0";
    }
    }
    //cout << "MANTISSA FULL:  " << mantissa << endl;
    string exp = to_bin(exponent);
    exp = itc_slice_str(exp, 0, itc_len(exp));
    if ( itc_len(exp) < 8){
        for ( int i = 0; itc_len(exp) < 8; i++)
            exp = "0" + exp;
    }
    //cout << "EXPONENT IN BIN:  " << exp << endl << endl;
    //cout << "RESULT" << endl;
    string fin = sign + exp + mantissa;
    cout << fin << endl;


    }
    return 0;
}

