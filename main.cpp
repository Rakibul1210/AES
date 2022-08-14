#include <iostream>
#include <math.h>

//#define DEBUG
//#define DEBUG_KEY
//#define D_XOR

using namespace std;

string plain_text;
string key_string;

string key[4][44];

string ROUND_CONSTANT[10] =  { "01", "02", "04", "08", "10", "20", "40", "80", "1B", "36"};

string S_BOX[16][16] = {
"63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76",
"CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0",
"B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15",
"04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75",
"09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84",
"53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF",
"D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8",
"51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2",
"CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73",
"60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB",
"E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79",
"E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08",
"BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A",
"70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E",
"E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF",
"8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16",
};

string binary_to_hex(int binary_array[8]);

string X_OR(string s, string t)
{
    #ifdef D_XOR
    cout<<"X-OR("<<s<<", "<<t<<")"<< " -> " ;
    #endif // D_XOR
    int s_binary[8];
    int t_binary[8];
    int n;
    //S_binary...................
    if(s[0] > '9')
        n = s[0] - 'A' +10;
    else
        n = s[0] - '0';
    for(int i=3;i>=0;i--)
    {
        s_binary[i] = n%2;
        n = n/2;
    }



    if(s[1] > '9')
        n = s[1] - 'A'+10;
    else
        n = s[1] - '0';

    for(int i=7;i>=4;i--)
    {
        s_binary[i] = n%2;
        n = n/2;
    }


    if(t[0] > '9')
        n = t[0] - 'A'+10;
    else
        n = t[0] - '0';

    for(int i=3;i>=0;i--)
    {
        t_binary[i] = n%2;
        n = n/2;
    }
    if(t[1] > '9')
        n = t[1] - 'A'+10;
    else
        n = t[1] - '0';

    for(int i=7;i>=4;i--)
    {
        t_binary[i] = n%2;
        n = n/2;
    }

    int answer[8];
    for(int i=0;i<8;i++)
    {


        if(s_binary[i] ==  t_binary[i])
            answer[i] = 0;
        else
            answer[i] = 1;
    }


    //............

//    cout<<s<<": ";
//    for(int i=0;i<8;i++)
//        cout<<s_binary[i]<<" ";
//    cout<<endl;
//    cout<<t<<": ";
//    for(int i=0;i<8;i++)
//        cout<<t_binary[i]<<" ";
//    cout<<endl;
//    cout<<"--"<<": ";
//    for(int i=0;i<8;i++)
//        cout<<answer[i]<<" ";
//    cout<<endl;


    string hex = binary_to_hex(answer);
    #ifdef D_XOR
    cout<<hex<<endl;
    #endif // D_XOR
//    cout<<endl;
//    cout<<endl;
//    cout<<endl;



    return hex;


}


string binary_to_hex(int binary_array[8])
{
    string hex = "00";
    int value = 0;
    int pos = 3;
    for(int i=0;i<4;i++)
    {
        value = value + pow(2,pos)*binary_array[i];
        //cout<<"value"<<value<<endl;
        pos--;
    }

    if(value > 9)
        hex[0]  = 'A' + (value-10);
    else
        hex[0] = '0' + value;


    value = 0;
    pos = 3;
    for(int i=4;i<8;i++)
    {
        value = value + pow(2,pos)*binary_array[i];
        //cout<<"value"<<value<<endl;
        pos--;
    }
    if(value > 9)
        hex[1]  = 'A' + (value-10);
    else
        hex[1] = '0' + value;


    //cout<<"hex: "<<hex<<endl;

    return hex;
}

//...............................................G............................................................
void g(string &last_word, int round)
{

        // substitute byte
        string temp = "00";
        temp[0] = last_word[0];
        temp[1] = last_word[1];

        last_word[0] = last_word[2];
        last_word[1] = last_word[3];
        last_word[2] = last_word[4];
        last_word[3] = last_word[5];
        last_word[4] = last_word[6];
        last_word[5] = last_word[7];
        last_word[6] = temp[0];
        last_word[7] = temp[1];

#ifdef DEBUG_KEY
        cout<<"at G:      ";
        for(int i=0;i<8;i++)
        {
            cout<<last_word[i++]<<last_word[i]<<" ";
        }
        cout<<endl;
#endif // DEBUG_KEY


    int row,col;
    for(int i=0;i<8;i = i+2)
    {
        if(last_word[i] > '9')
            row = last_word[i] - 'A' +10;
        else
            row = last_word[i] - '0';
        if(last_word[i+1] > '9')
            col = last_word[i+1] - 'A' +10;
        else
            col = last_word[i+1] - '0';


        temp = S_BOX[row][col];

        last_word[i] = temp[0];
        last_word[i+1] = temp[1];
    }

#ifdef DEBUG_KEY
        cout<<"at G:      ";
        for(int i=0;i<8;i++)
        {
            cout<<last_word[i++]<<last_word[i]<<" ";
        }
        cout<<endl;
#endif // DEBUG_KEY
    temp[0] = last_word[0];
    temp[1] = last_word[1];
    temp = X_OR(temp, ROUND_CONSTANT[round]);
    //temp = X_OR(ROUND_CONSTANT[round], temp);
    last_word[0] = temp[0];
    last_word[1] = temp[1];

}



void expand_key()
{
    int binary_array[8];

    int ascii_value;

    for(int i=0;i<16;i++)
    {

        ascii_value = key_string[i];
#ifdef DEBUG
        cout<<key_string[i]<<" -> ";
        cout<<ascii_value<<" -> ";
#endif // DEBUG
        int index = 7;
        for(int i=0;i<8;i++)
        {
            binary_array[index] = ascii_value%2;
            ascii_value = ascii_value/2;
            index--;
        }
#ifdef DEBUG
        for(int i=0;i<8;i++)
        {
            cout<<binary_array[i]<<" ";
        }
        cout<<" -> " ;

        cout<<binary_to_hex(binary_array)<<endl;
#endif // DEBUG


        key[i%4][i/4] = binary_to_hex(binary_array);

    }

#ifdef DEBUG_KEY
    cout<<"Initial key: "<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<key[i][j]<<" ";
        }
        cout<<endl;

    }
    cout<<endl;
#endif // DEBUG


        cout<<"Initial key: "<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                cout<<key[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;


    // Expansion started.............................................................................
    string last_word = "00000000";
    for(int i=0;i<10;i++)
    {
        last_word[0] = key[0][i*4+3][0];
        last_word[2] = key[1][i*4+3][0];
        last_word[4] = key[2][i*4+3][0];
        last_word[6] = key[3][i*4+3][0];
        last_word[1] = key[0][i*4+3][1];
        last_word[3] = key[1][i*4+3][1];
        last_word[5] = key[2][i*4+3][1];
        last_word[7] = key[3][i*4+3][1];

#ifdef DEBUG_KEY
        cout<<"last_word: ";
        for(int i=0;i<8;i++)
        {
            cout<<last_word[i++]<<last_word[i]<<" ";
        }
        cout<<endl;
#endif // DEBUG_KEY

        g(last_word, i);


#ifdef DEBUG_KEY
        cout<<"after g:   ";
        for(int i=0;i<8;i++)
        {
            cout<<last_word[i++]<<last_word[i]<<" ";
        }
        cout<<endl;
#endif // DEBUG_KEY


        string third_word[4]= {"00", "00", "00","00"};
        third_word[0][0] = last_word[0];
        third_word[0][1] = last_word[1];
        third_word[1][0] = last_word[2];
        third_word[1][1] = last_word[3];
        third_word[2][0] = last_word[4];
        third_word[2][1] = last_word[5];
        third_word[3][0] = last_word[6];
        third_word[3][1] = last_word[7];



         //w[4]............................
        key[0][4*(i+1)] = X_OR(key[0][4*i], third_word[0]);
        key[1][4*(i+1)] = X_OR(key[1][4*i], third_word[1]);
        key[2][4*(i+1)] = X_OR(key[2][4*i], third_word[2]);
        key[3][4*(i+1)] = X_OR(key[3][4*i], third_word[3]);







        cout<<endl;
        for(int j=1;j<4;j++)
        {
            key[0][4*(i+1)+j] = X_OR(key[0][4*(i+1)+(j-1)], key[0][4*i+(j)]);
            key[1][4*(i+1)+j] = X_OR(key[1][4*(i+1)+(j-1)], key[1][4*i+(j)]);
            key[2][4*(i+1)+j] = X_OR(key[2][4*(i+1)+(j-1)], key[2][4*i+(j)]);
            key[3][4*(i+1)+j] = X_OR(key[3][4*(i+1)+(j-1)], key[3][4*i+(j)]);
        }



    }

cout<<"Expanded key: "<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<44;j++)
            {
                if(j && j%4==0)
                    cout<<"  ";
                cout<<key[i][j]<<" ";

            }
            cout<<endl;
        }
        cout<<endl;

}



int main()
{
    plain_text = "Two One Nine One";
    key_string = "Thats my Kung Fu";

    //key_string = "satishcjisboring";  // from youTube tutorial
/*
    cin>>plain_text;
    cin>>key_string;
*/

    expand_key();


}

