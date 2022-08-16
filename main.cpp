#include <iostream>
#include <math.h>

//#define DEBUG
//#define DEBUG_KEY
//#define D_XOR

using namespace std;

string plain_text;
string key_string;

string state_matrix[4][4];
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

string MULTIPLY_BY_2[16][16] = {
"00", "02", "04", "06", "08", "0A", "0C", "0E", "10", "12", "14", "16", "18", "1A", "1C", "1E",
"20", "22", "24", "26", "28", "2A", "2C", "2E", "30", "32", "34", "36", "38", "3A", "3C", "3E",
"40", "42", "44", "46", "48", "4A", "4C", "4E", "50", "52", "54", "56", "58", "5A", "5C", "5E",
"60", "62", "64", "66", "68", "6A", "6C", "6E", "70", "72", "74", "76", "78", "7A", "7C", "7E",
"80", "82", "84", "86", "88", "8A", "8C", "8E", "90", "92", "94", "96", "98", "9A", "9C", "9E",
"A0", "A2", "A4", "A6", "A8", "AA", "AC", "AE", "B0", "B2", "B4", "B6", "B8", "BA", "BC", "BE",
"C0", "C2", "C4", "C6", "C8", "CA", "CC", "CE", "D0", "D2", "D4", "D6", "D8", "DA", "DC", "DE",
"E0", "E2", "E4", "E6", "E8", "EA", "EC", "EE", "F0", "F2", "F4", "F6", "F8", "FA", "FC", "FE",
"1B", "19", "1F", "1D", "13", "11", "17", "15", "0B", "09", "0F", "0D", "03", "01", "07", "05",
"3B", "39", "3F", "3D", "33", "31", "37", "35", "2B", "29", "2F", "2D", "23", "21", "27", "25",
"5B", "59", "5F", "5D", "53", "51", "57", "55", "4B", "49", "4F", "4D", "43", "41", "47", "45",
"7B", "79", "7F", "7D", "73", "71", "77", "75", "6B", "69", "6F", "6D", "63", "61", "67", "65",
"9B", "99", "9F", "9D", "93", "91", "97", "95", "8B", "89", "8F", "8D", "83", "81", "87", "85",
"BB", "B9", "BF", "BD", "B3", "B1", "B7", "B5", "AB", "A9", "AF", "AD", "A3", "A1", "A7", "A5",
"DB", "D9", "DF", "DD", "D3", "D1", "D7", "D5", "CB", "C9", "CF", "CD", "C3", "C1", "C7", "C5",
"FB", "F9", "FF", "FD", "F3", "F1", "F7", "F5", "EB", "E9", "EF", "ED", "E3", "E1", "E7", "E5"
};

string MULTIPLY_BY_3[16][16] = {
"00", "03", "06", "05", "0C", "0F", "0A", "09", "18", "1B", "1E", "1D", "14", "17", "12", "11",
"30", "33", "36", "35", "3C", "3F", "3A", "39", "28", "2B", "2E", "2D", "24", "27", "22", "21",
"60", "63", "66", "65", "6C", "6F", "6A", "69", "78", "7B", "7E", "7D", "74", "77", "72", "71",
"50", "53", "56", "55", "5C", "5F", "5A", "59", "48", "4B", "4E", "4D", "44", "47", "42", "41",
"C0", "C3", "C6", "C5", "CC", "CF", "CA", "C9", "D8", "DB", "DE", "DD", "D4", "D7", "D2", "D1",
"F0", "F3", "F6", "F5", "FC", "FF", "FA", "F9", "E8", "EB", "EE", "ED", "E4", "E7", "E2", "E1",
"A0", "A3", "A6", "A5", "AC", "AF", "AA", "A9", "B8", "BB", "BE", "BD", "B4", "B7", "B2", "B1",
"90", "93", "96", "95", "9C", "9F", "9A", "99", "88", "8B", "8E", "8D", "84", "87", "82", "81",
"9B", "98", "9D", "9E", "97", "94", "91", "92", "83", "80", "85", "86", "8F", "8C", "89", "8A",
"AB", "A8", "AD", "AE", "A7", "A4", "A1", "A2", "B3", "B0", "B5", "B6", "BF", "BC", "B9", "BA",
"FB", "F8", "FD", "FE", "F7", "F4", "F1", "F2", "E3", "E0", "E5", "E6", "EF", "EC", "E9", "EA",
"CB", "C8", "CD", "CE", "C7", "C4", "C1", "C2", "D3", "D0", "D5", "D6", "DF", "DC", "D9", "DA",
"5B", "58", "5D", "5E", "57", "54", "51", "52", "43", "40", "45", "46", "4F", "4C", "49", "4A",
"6B", "68", "6D", "6E", "67", "64", "61", "62", "73", "70", "75", "76", "7F", "7C", "79", "7A",
"3B", "38", "3D", "3E", "37", "34", "31", "32", "23", "20", "25", "26", "2F", "2C", "29", "2A",
"0B", "08", "0D", "0E", "07", "04", "01", "02", "13", "10", "15", "16", "1F", "1C", "19", "1A"
};


//functions prototypes...............
string X_OR(string s, string t);
string binary_to_hex(int binary_array[8]);
void print_state_matrix();

//########################################             CODE STARTS HERE           ###############################################


void add_round_key(int round)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            state_matrix[i][j] = X_OR(state_matrix[i][j] , key[i][round*4+j]);


        }
    }
    cout<<"State matrix after round key "<< round <<": "<<endl;
    print_state_matrix();
}


void sub_byte()
{
    int row,col;
    string temp;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
             temp = state_matrix[i][j];

             if(temp[0] > '9')
                row = temp[0] - 'A' +10;
            else
                row = temp[0] - '0';

            if(temp[1] > '9')
                col = temp[1] - 'A' + 10;
            else
            {
                col = temp[1] - '0';
            }

                //cout<<"row: "<<row<<" col: "<<col<<endl;

            temp = S_BOX[row][col];

            state_matrix[i][j][0] = temp[0];
            state_matrix[i][j][1] = temp[1];


        }
    }

    cout<<"state matrix after sub_byte: "<<endl;
    print_state_matrix();

}


void shift_rows()
{
    // nothing to do for first row...

    // shift 1 byte left for second row
    string temp = state_matrix[1][0];

    state_matrix[1][0] = state_matrix[1][1];
    state_matrix[1][1] = state_matrix[1][2];
    state_matrix[1][2] = state_matrix[1][3];
    state_matrix[1][3] = temp;


    // shift 2 byte for third row ..... actually just swap (0,2) and (1,3)
    temp = state_matrix[2][0];
    state_matrix[2][0] = state_matrix[2][2];
    state_matrix[2][2] = temp;

    temp = state_matrix[2][1];
    state_matrix[2][1] = state_matrix[2][3];
    state_matrix[2][3] = temp;


    // shift  3 byte for forth row ..... (or just right shift one byte)
    temp = state_matrix[3][3];

    state_matrix[3][3] = state_matrix[3][2];
    state_matrix[3][2] = state_matrix[3][1];
    state_matrix[3][1] = state_matrix[3][0];
    state_matrix[3][0] = temp;






    cout<<"State matrix after shift row: "<<endl;
    print_state_matrix();

}

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

void print_state_matrix()
{
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                cout<<state_matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
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


    //...................................................................... Expansion started...............................................................................................
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






        //w[5,6,7]..............................
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


void generate_state_matrix(){
    int binary_array[8];

    int ascii_value;

    for(int i=0;i<16;i++)
    {

        ascii_value = plain_text[i];
#ifdef DEBUG
        cout<<plain_text[i]<<" -> ";
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


        state_matrix[i%4][i/4] = binary_to_hex(binary_array);

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


        cout<<"Initial state matrix: "<<endl;
        print_state_matrix();


}


string multiply(string str, int mulpilier)
{
    int row,col;
    if(str[0] > '9')
        row = str[0] - 'A' +10;
    else
        row = str[0] - '0';

    if(str[1] > '9')
        col = str[1] - 'A' + 10;
    else
    {
        col = str[1] - '0';
    }

        //cout<<"row: "<<row<<" col: "<<col<<endl;

    if(mulpilier == 2)
        str = MULTIPLY_BY_2[row][col];
    else if(mulpilier == 3)
        str = MULTIPLY_BY_3[row][col];


    return str;
}

void mix_column()
{
    string temp_state_array[4][4] = {"00"};

    for (int i = 0; i < 4; ++i)
    {
        temp_state_array[0][i]=  X_OR(X_OR(multiply(state_matrix[0][i], 2) ,multiply(state_matrix[1][i],3)) , X_OR(state_matrix[2][i],  state_matrix[3][i]));
        temp_state_array[1][i] =  X_OR(X_OR(state_matrix[0][i] ,multiply(state_matrix[1][i],2)) , X_OR(multiply(state_matrix[2][i],3),  state_matrix[3][i]));
        temp_state_array[2][i] =  X_OR(X_OR(state_matrix[0][i] ,state_matrix[1][i]) , X_OR(multiply(state_matrix[2][i],2),  multiply(state_matrix[3][i],3)));
        temp_state_array[3][i] =  X_OR(X_OR(multiply(state_matrix[0][i],3) ,state_matrix[1][i]) , X_OR(state_matrix[2][i],  multiply(state_matrix[3][i],2)));
        //break;
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            state_matrix[i][j] = temp_state_array[i][j];
        }
    }

    cout<<"After mix column: "<<endl;
    print_state_matrix();
}




int main()
{
    plain_text = "Two One Nine Two";
    key_string = "Thats my Kung Fu";

/*
    cin>>plain_text;
    cin>>key_string;
*/

    expand_key();
    generate_state_matrix();


    add_round_key(0);


    //round functions......
    for(int i=1;i<10;i++)
    {
        sub_byte();
        shift_rows();
        mix_column();
        add_round_key(i);
        cout<<"#############################   END OF ROUND "<<i<<"########################"<<endl;
    }

    // 10th round
    sub_byte();
    shift_rows();
    add_round_key(10);



}

