#include<iostream>
#include<vector>
using namespace std;
/*
To team:
Because the bigInt is supposed to be dynamically resized, im using vectors to start the project off.
Position 0 in the vector will represent 0, pos.1 will be tens place, and so on and so forth.
*/
//TODO: Figure out constructors, performance, read data in and out of bigInt

class bigInt {
    private:
        //ask if we need to consider negative numbers;
        vector<int> digits;
        //heler methods to access vector
        int size();
        int* at(int index);
    public:
        bigInt();
        bigInt(vector<int> digits); //Maybe allow for constructor with int parameter?
        friend bigInt operator+(bigInt lhs, bigInt rhs);

        //friend bigInt operator-(bigInt lhs, bigInt rhs);
        //friend bigInt operator*(bigInt lhs, bigInt rhs);
        //not sure how he wants us to do division, will ask later
        //friend bigInt operator/(bigInt lhs, bigInt rhs);
        
        //i/o
        friend ostream& operator<< (ostream& os, bigInt num);
        //friend istream& operator>> (istream& is, bigInt num);
        
};


bigInt::bigInt(vector<int> digits) {
    this->digits = digits;
}

bigInt::bigInt() {
}

int bigInt::size() {
    return digits.size();
}

int* bigInt::at(int index) {
    return &digits.at(index);
}

bigInt operator+(bigInt lhs, bigInt rhs) {
    bigInt sum;
    if (lhs.size() > rhs.size()) {
        sum.digits.resize(lhs.size());
    } else {
        sum.digits.resize(rhs.size());
    }
    int carry = 0;
    for (int i = 0; i < lhs.size() && i < rhs.size(); i++) {
        //check if one is bigger than the other in length, then act accordingly
        if (i >= lhs.size()) {
            *sum.at(i) = *rhs.at(i);
            continue;
        } else if (i >= rhs.size()) {
            *sum.at(i) = *lhs.at(i);
            continue;
        }
        int digitSum = *lhs.at(i) + *rhs.at(i) + carry;
        carry = digitSum / 10;
        if (digitSum >= 10) {
            digitSum = digitSum % 10;
        }
        *sum.at(i) = digitSum;
    }
    if (carry != 0) {
        sum.digits.push_back(carry);
    }
    return sum;
}

ostream& operator<< (ostream& os, bigInt num) {
    for (int i = num.size() - 1; i >= 0; i--) {
        os << *num.at(i);
    }
}

//Testing stuff
int main() {
    vector<int> nums(3);
    nums.at(2) = 3;
    nums.at(1) = 2;
    nums.at(0) = 1;
    vector<int> nums2(3);
    nums2.at(2) = 8;
    nums2.at(1) = 2;
    nums2.at(0) = 3;
    bigInt theNum(nums);
    bigInt theNum2(nums2);
    theNum = theNum + theNum2;
    cout<< theNum;
}

