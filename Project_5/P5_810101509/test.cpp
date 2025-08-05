#include <iostream>
#include <vector>
#include <string>

using namespace std;
class test{
private:
    int num = 9;
public:
    void changeNum();
    int getNum(){return num;}
};
void test::changeNum(){
    num =18;
}
int main (){
    test Test;
    Test.changeNum();
    cout<<Test.getNum();
}