#include <stdio.h>

#ifdef __cplusplus
namespace MCAL
{
    namespace DIO
    {
#endif
        int x = 5;
        void hello()
        {
            printf("Hello From C/C++ application\n");
        }

#ifdef __cplusplus
    } // namespace DIO
    
} // namespace MCAL
#endif

#ifdef __cplusplus
using namespace MCAL::DIO;
#endif

int main()
{
    printf("x : %d\n", x);
    hello();
    
    return 0;
}
