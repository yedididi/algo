#include <iostream>

using namespace std;

int main() 
{
    int respA;

    for (int a = 1; a <= 10000; a++)
    {
        std::cout << "? A " << a << std::endl;

        // 채점기의 답변을 입력받는다.
        std::cin >> respA;

        if(respA == 1 || (respA == 0 && a == 9999))
        {
            int respB;

            if (a == 9999)
                a = 10000;

            for (int b = 1; b <= 10000; b++)
            {
                std::cout << "? B " << b << std::endl;
        
                // 채점기의 답변을 입력받는다.
                std::cin >> respB;
            
                if (respB == 1 || (respB == 0 && b == 9999))
                {
                    if (b == 9999)
                        b = 10000;
                    std::cout << "! " << a + b << endl;
                    break;
                }
            }
            break;
        }
    }
}