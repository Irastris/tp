#include "JSystem/JMath/JMATrigonometric.h"

namespace JMath {
    template<typename T>
    struct TAngleConstant_;

    inline f64 getConst2() {
        return 9.765625E-4;
    }

    TSinCosTable<13, f32> sincosTable_ ATTRIBUTE_ALIGN(32);

    TAtanTable<1024, f32> atanTable_ ATTRIBUTE_ALIGN(32);

    TAsinAcosTable<1024, f32> asinAcosTable_ ATTRIBUTE_ALIGN(32);
}
